// Copyright (C) 2015 Dave Griffiths
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

#include "jellyfish/fluxa/OSC_server.h"
#include "brain.h"
#include <pthread.h>

#pragma once

namespace spiralcore {

class process_thread {
public:
    process_thread();
    ~process_thread();

    brain m_source, m_target;
    pthread_mutex_t* m_brain_mutex;

    void process();

    void load_source(const std::string &filename);
    void load_target(const std::string &filename);
    void save_source(const std::string &filename);
    void save_target(const std::string &filename);

private:
	OSC_server m_osc;
    u32 m_source_block_size;
    float m_source_overlap;
    u32 m_target_block_size;
    float m_target_overlap;
    window::type m_window_type;
    window::type m_target_window_type;
    pthread_t *m_thread;
};

}
