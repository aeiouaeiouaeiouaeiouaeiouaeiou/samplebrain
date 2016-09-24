// Copyright (C) 2016 Foam Kernow
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

#include <vector>
#include "window.h"
#include "block.h"
#include "jellyfish/sample.h"
#include "block_source.h"

#ifndef BLOCK_STREAM
#define BLOCK_STREAM

namespace spiralcore {

  // the block stream takes incoming audio and chops it up into blocks
  // in realtime, for providing them to the renderer (in place of a
  // source brain)
class block_stream : public block_source {
 public:
  block_stream();
  virtual ~block_stream();

  void init(u32 block_size, u32 overlap, window::type t, bool ditchpcm=false);

  // for the moment ignores right channel
  void process(const sample &left, const sample &right);
  virtual const block &get_block(u32 index) const;
  virtual u32 get_num_blocks() const { return UINT_MAX; } 

  u32 last_block_index() const { return m_block_index_offset+m_blocks.size()-1; }

  class worker {
  public:
    worker(u32 id, window *w);

    enum worker_status { READY=0, ACTIVATE, WORKING, FINISHED };

    void run();
    
    u32 m_id;
    worker_status m_status;
    pthread_mutex_t* m_worker_mutex;
    sample m_region;
    block *m_output;
    window *m_window;
    u32 m_block_index;

    pthread_t *m_thread;
  };

 private:

  void scatter_gather(u32 block_index, const sample &region);

  vector<worker*> m_workers;

  bool m_ready;

  u32 m_block_index;
  u32 m_block_position;
  u32 m_buffer_position;
  sample m_buffer;

  window m_window;

  u32 m_block_index_offset;
  vector<block> m_blocks;

  mutable s32 m_sent_block_index;

  block *m_dummy_block;

};

}

#endif
