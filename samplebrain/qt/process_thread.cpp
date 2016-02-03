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
#include "status.h"

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
            //cerr<<name<<endl;
            if (name=="/load_sample") {
                pthread_mutex_lock(m_brain_mutex);
                m_source.load_sound(cmd.get_string(0),brain::MIX);
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
                m_source.init(m_source_block_size, m_source_overlap, m_window_type);
                search_params p(1,0,0,100,0);
                m_source.build_synapses_fixed(p);
                m_left_renderer->reset();
                m_right_renderer->reset();
                pthread_mutex_unlock(m_brain_mutex);
            }
            if (name=="/load_target") {
                pthread_mutex_lock(m_brain_mutex);
                m_left_target.clear_sounds();
                m_left_target.load_sound(cmd.get_string(0),brain::LEFT);
                m_right_target.clear_sounds();
                m_right_target.load_sound(cmd.get_string(0),brain::RIGHT);
                pthread_mutex_unlock(m_brain_mutex);
            }
            if (name=="/target_block_size") {
                m_target_block_size = cmd.get_int(0);
            }
            if (name=="/target_overlap") {
                m_target_overlap = m_target_block_size*cmd.get_float(0);
            }
            if (name=="/generate_target") {
                pthread_mutex_lock(m_brain_mutex);
                m_left_target.init(m_target_block_size, m_target_overlap, m_target_window_type);
                m_right_target.init(m_target_block_size, m_target_overlap, m_target_window_type);
                pthread_mutex_unlock(m_brain_mutex);
            }
            if (name=="/window_type") {
                m_window_type=(window::type)cmd.get_int(0);
            }
            if (name=="/target_window_type") {
                m_target_window_type=(window::type)cmd.get_int(0);
            }
            if (name=="/load_brain") {
                load_source(cmd.get_string(0));
            }
            if (name=="/save_brain") {
                save_source(cmd.get_string(0));
            }
            if (name=="/load_session") {
                load_session(cmd.get_string(0));
            }
            if (name=="/save_session") {
                save_session(cmd.get_string(0));
            }
        }
        usleep(500);
    }
}


void process_thread::load_source(const std::string &filename) {
    pthread_mutex_lock(m_brain_mutex);
    m_source.clear();
    ifstream ifs(filename.c_str(),ios::binary);
    ifs||m_source;
    ifs.close();
    pthread_mutex_unlock(m_brain_mutex);
}

void process_thread::save_source(const std::string &filename) {
    pthread_mutex_lock(m_brain_mutex);
    ofstream ofs(filename.c_str(),ios::binary);
    ofs||m_source;
    ofs.close();
    pthread_mutex_unlock(m_brain_mutex);
}

// remember to change GUI side to match in MainWindow.cpp
void process_thread::load_session(const std::string &filename) {
    pthread_mutex_lock(m_brain_mutex);
    m_source.clear();
    m_left_target.clear();
    m_right_target.clear();
    ifstream ifs(filename.c_str(),ios::binary);
    u32 version=0;
    ifs||version;
    ifs||(*m_left_renderer);
    ifs||(*m_right_renderer);
    ifs||m_source_block_size||m_source_overlap;
    ifs||m_target_block_size||m_target_overlap;
    ifs||m_window_type||m_target_window_type;
    ifs||m_source;
    ifs||m_left_target;
    ifs||m_right_target;
    ifs.close();
    pthread_mutex_unlock(m_brain_mutex);
}

void process_thread::save_session(const std::string &filename) {
    pthread_mutex_lock(m_brain_mutex);
    ofstream ofs(filename.c_str(),ios::binary);
    u32 version=0;
    ofs||version;
    ofs||(*m_left_renderer);
    ofs||(*m_right_renderer);
    ofs||m_source_block_size||m_source_overlap;
    ofs||m_target_block_size||m_target_overlap;
    ofs||m_window_type||m_target_window_type;
    ofs||m_source;
    ofs||m_left_target;
    ofs||m_right_target;
    ofs.close();
    pthread_mutex_unlock(m_brain_mutex);
}
