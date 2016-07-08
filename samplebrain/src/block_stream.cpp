// Copyright (C) 2015 Foam Kernow
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

#include <iostream>
#include "block_stream.h"

using namespace spiralcore;
using namespace std;

#define BUFFER_SIZE 4096*10
#define MAX_BLOCKS 200

block_stream::block_stream() :
  m_ready(false),
  m_block_index(0),
  m_block_position(0),
  m_buffer_position(0),
  m_buffer(BUFFER_SIZE),
  m_block_index_offset(0)
{
}

block_stream::~block_stream() {}

void block_stream::init(u32 block_size, u32 overlap, window::type t, bool ditchpcm) {
  m_block_size=block_size;
  m_overlap=overlap;
  m_block_index=0;
  m_block_position=0;
  m_buffer_position=0;

  if (m_overlap>=m_block_size) m_overlap=0;
  cerr<<m_block_size<<endl;
  m_window.init(m_block_size);
  m_window.set_current_type(t);

  m_blocks.clear();
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
      m_blocks.push_back(block(0,"input",region,44100,m_window));      
      m_block_position=0;

      if (m_blocks.size()>MAX_BLOCKS) {
	m_blocks.erase(m_blocks.begin());
	m_block_index_offset++;
      }
    }
    
    m_block_position++;
  }
  cerr<<"num blocks: "<<m_blocks.size()<<endl;
}

const block &block_stream::get_block(u32 index) const {
  return m_blocks[(index-m_block_index_offset)%m_blocks.size()];
}
