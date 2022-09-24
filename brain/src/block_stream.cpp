// Copyright (C) 2022 Then Try This
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include <unistd.h>
#include <iostream>
#include <signal.h>
#include "block_stream.h"

using namespace spiralcore;
using namespace std;

#define BUFFER_SIZE 4096*10
#define MAX_BLOCKS 200
#define NUM_WORKERS 4

block_stream::block_stream() :
  m_ready(false),
  m_block_index(0),
  m_block_position(0),
  m_buffer_position(0),
  m_buffer(BUFFER_SIZE),
  m_block_index_offset(0),
  m_sent_block_index(0)
{
}

block_stream::~block_stream() {}

void block_stream::start() {
  cerr<<"block stream starting up"<<endl;
  for (u32 i=0; i<NUM_WORKERS; ++i) {
    m_workers.push_back(new worker(i,&m_window));
    // ????
#ifndef WIN32
    usleep(1);  
#endif
  }
}

void block_stream::stop() {
  cerr<<"block stream ending"<<endl;

  bool killcount = 0;
  for (auto &w : m_workers) {
    pthread_join(*w->m_thread,NULL);
  }

  usleep(500);
  
  for (u32 i=0; i<NUM_WORKERS; ++i) {
    delete m_workers[i];
  }
  m_workers.clear();
}

void block_stream::init(u32 block_size, u32 overlap, window::type t, bool ditchpcm) {
  m_block_size=block_size;
  m_overlap=overlap;
  m_block_index=20;
  m_block_position=0;
  m_buffer_position=0;

  if (m_overlap>=m_block_size) m_overlap=0;

  m_window.init(m_block_size);
  m_window.set_current_type(t);

  m_blocks.clear();
  sample dummy(block_size);
  for (u32 i=0; i<MAX_BLOCKS; i++) {
    m_blocks.push_back(block(0,"dummy",dummy,44100,m_window));
  }

  m_ready=true;
}

void block_stream::process(const sample &left, const sample &right) {
  if (!m_ready) return; 

  // load the audio into the buffer
  for (u32 i=0; i<left.get_length(); i++) {
    m_buffer[m_buffer_position++]=left[i];
    if (m_buffer_position>m_buffer.get_length()) {
      m_buffer_position=0;
    }
    
    // time to make a new block
    if (m_block_position>m_block_size-m_overlap) {
      sample region;
      // m_buffer_pos-m_block_size can be negative to deal
      // with the buffer wrapping...      
      //cerr<<(s32)(m_buffer_position-m_block_size)<<" to "<<m_buffer_position<<endl;
      m_buffer.get_region(region,(s32)(m_buffer_position-m_block_size),
                          m_buffer_position);

      //cerr<<"starting block "<<m_block_index<<endl;
      scatter_gather(m_block_index,region);
      m_block_index=(m_block_index+1)%MAX_BLOCKS;
      
      //block b(0,"input",region,44100,m_window);
      //m_blocks.push_back(b);      
      
      m_block_position=0;
      
      if (m_blocks.size()>MAX_BLOCKS) {
        m_blocks.erase(m_blocks.begin());
        m_block_index_offset++;
      }
    }
    
    m_block_position++;
  }
}

const block &block_stream::get_block(u32 index) const {
  //cerr<<"returning "<<(index-m_block_index_offset)%m_blocks.size()<<" ("<<m_blocks.size()<<")"<<endl;
  u32 i = (index-m_block_index_offset)%MAX_BLOCKS;
  //if (m_block_index<i) {
  //  cerr<<i<<" ("<<(s32)(m_block_index-(s32)(i))<<")"<<endl;
  //}
  return m_blocks[i];
}

//-----------------------------------------------------------

void *_run_worker(void *p) {
  ((block_stream::worker *)p)->run();
  return NULL;
}

block_stream::worker::worker(u32 id, window *w) :
  m_id(id),
  m_status(READY),
  m_window(w)
{
  m_worker_mutex = new pthread_mutex_t;
  pthread_mutex_init(m_worker_mutex,NULL);
  m_thread = new pthread_t;
  pthread_create(m_thread,NULL,(void*(*)(void*))_run_worker,this);
}

block_stream::worker::~worker() {
  delete m_worker_mutex;
  delete m_thread;
}

void block_stream::worker::run() {
  while (true) {
    pthread_mutex_lock(m_worker_mutex);
    if (m_status==ACTIVATE) {
      cerr<<"starting "<<m_id<<endl;
      m_status=WORKING;
      m_output = new block(0,"input",m_region,44100,*m_window);      
      m_status=FINISHED;
      cerr<<"ending "<<m_id<<endl;
    }

    pthread_mutex_unlock(m_worker_mutex);
#ifndef WIN32
    usleep(5);
#endif
  }
}

void block_stream::scatter_gather(u32 block_index, const sample &region) {
  while(true) {
    for (auto &w : m_workers) {
      if (pthread_mutex_trylock(w->m_worker_mutex)==0) {
        if (w->m_status == worker::FINISHED) {
          //cerr<<"adding finished block "<<w->m_block_index<<endl;
          m_blocks[w->m_block_index]=*w->m_output;      
          w->m_status = worker::READY;
        }

        if (w->m_status == worker::READY) {
          w->m_region = region;
          w->m_status = worker::ACTIVATE;
          w->m_block_index = block_index;
          return;
        }

        pthread_mutex_unlock(w->m_worker_mutex);
      }    
    }
  }
}

