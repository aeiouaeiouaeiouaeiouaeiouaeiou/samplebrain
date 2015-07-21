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

#include "process_thread.h"
#include <iostream>
#include <unistd.h>

using namespace spiralcore;
using namespace std;

static void _process(void *c) {
    process_thread *p=(process_thread*)c;
    p->process();
}

process_thread::process_thread() :
    m_osc("8889"),
    m_source_block_size(3000),
    m_source_overlap(0.75),
    m_target_block_size(3000),
    m_target_overlap(0.75),
    m_window_type(window::DODGY),
    m_target_window_type(window::DODGY)
{
    m_brain_mutex = new pthread_mutex_t;
    pthread_mutex_init(m_brain_mutex,NULL);
    m_osc.run();

    // start the processing thread
    m_thread = new pthread_t;
    pthread_create(m_thread,NULL,(void*(*)(void*))_process,this);
}

process_thread::~process_thread() {
    pthread_cancel(*m_thread);
    delete m_brain_mutex;
}

void process_thread::process() {
    command_ring_buffer::command cmd;

    while(true) {
        while (m_osc.get(cmd)) {
            string name = cmd.m_name;
            cerr<<name<<endl;
            if (name=="/load_sample") {
                pthread_mutex_lock(m_brain_mutex);
                m_source.load_sound(cmd.get_string(0));
                pthread_mutex_unlock(m_brain_mutex);
            }
            if (name=="/delete_sample") {
                pthread_mutex_lock(m_brain_mutex);
                m_source.delete_sound(cmd.get_string(0));
                pthread_mutex_unlock(m_brain_mutex);
            }
            if (name=="/source_block_size") {
                m_source_block_size = cmd.get_int(0);
            }
            if (name=="/source_overlap") {
                m_source_overlap = m_source_block_size*cmd.get_float(0);
            }
            if (name=="/generate_brain") {
                pthread_mutex_lock(m_brain_mutex);
                cerr<<m_window_type<<endl;
                m_source.init(m_source_block_size, m_source_overlap, m_window_type);
                pthread_mutex_unlock(m_brain_mutex);
            }
            if (name=="/load_target") {
                pthread_mutex_lock(m_brain_mutex);
                m_target.clear_sounds();
                m_target.load_sound(cmd.get_string(0));
                pthread_mutex_unlock(m_brain_mutex);
            }
            if (name=="/target_block_size") {
                m_target_block_size = cmd.get_int(0);
            }
            if (name=="/target_overlap") {
                m_target_overlap = m_target_block_size*cmd.get_float(0);
                cerr<<m_target_overlap<<endl;
            }
            if (name=="/generate_target") {
                pthread_mutex_lock(m_brain_mutex);
                cerr<<m_target_window_type<<endl;
                m_target.init(m_target_block_size, m_target_overlap, m_target_window_type);
                pthread_mutex_unlock(m_brain_mutex);
            }
            if (name=="/window_type") {
                m_window_type=(window::type)cmd.get_int(0);
            }
            if (name=="/target_window_type") {
                m_target_window_type=(window::type)cmd.get_int(0);
            }

        }
        usleep(500);
    }
}
