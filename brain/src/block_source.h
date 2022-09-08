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

#include "block.h"

#ifndef BLOCK_SOURCE
#define BLOCK_SOURCE

namespace spiralcore {

// base class for brain or block_stream - a source of audio blocks
class block_source {
 public:
  block_source() {}
  ~block_source() {}

  virtual const block &get_block(u32 index) const=0;

  u32 get_block_size() const { return m_block_size; } 
  u32 get_overlap() const { return m_overlap; }
  virtual u32 get_num_blocks() const=0;

 protected:

  u32 m_block_size;
  u32 m_overlap;
  
};

}

#endif
