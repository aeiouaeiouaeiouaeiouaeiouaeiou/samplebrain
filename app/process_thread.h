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

#include "spiralcore/OSC_server.h"
#include "brain.h"
#include "renderer.h"
#include "block_stream.h"
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

#pragma once

namespace spiralcore {

  class process_thread {
  public:
    process_thread(const string &port);
    ~process_thread();

    pthread_mutex_t* m_brain_mutex;

    void register_renderer(renderer *lr, renderer *rr, block_stream *bs) {
      m_left_renderer=lr;
      m_right_renderer=rr;
      m_block_stream=bs;
      m_block_stream->init(m_target_block_size, m_target_overlap, m_target_window_type);
    }

    void process();

    void load_source(const std::string &filename);
    void save_source(const std::string &filename);

    void load_session(const std::string &filename);
    void save_session(const std::string &filename);


    bool ok() { return m_osc.ok(); }

    // only for use in mutex
    brain m_source, m_left_target, m_right_target;

  private:
    void stream_session(std::ios &fs);
      
    OSC_server m_osc;
    u32 m_source_block_size;
    float m_source_overlap;
    u32 m_target_block_size;
    float m_target_overlap;
    window::type m_window_type;
    window::type m_target_window_type;
    bool m_stereo;
    pthread_t *m_thread;

    // only use in mutex obvs...
    renderer *m_left_renderer;
    renderer *m_right_renderer;
    block_stream *m_block_stream;
  };

}
