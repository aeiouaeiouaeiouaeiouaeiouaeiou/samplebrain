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

#include "audio_thread.h"
#include <iostream>

using namespace spiralcore;
using namespace std;

audio_thread::audio_thread(process_thread &p) :
    m_audio_device(NULL),
    m_process_thread(p),
    m_brain_mutex(p.m_brain_mutex),
    m_osc("8888")
{
    start_audio();
    pthread_mutex_lock(m_brain_mutex);
    m_renderer = new renderer(p.m_source,p.m_target);
    pthread_mutex_unlock(m_brain_mutex);
    m_osc.run();
}

static bool state = 1;

audio_thread::~audio_thread() {
    state=0;
    if (m_audio_device!=NULL) delete m_audio_device;
    delete m_renderer;
}

void audio_thread::start_audio() {
    if (m_audio_device!=NULL) delete m_audio_device;
    m_audio_device = new audio_device("samplebrain",44100,2048);
    m_audio_device->m_client.set_callback(run_audio, this);
}

void audio_thread::run_audio(void* c, unsigned int frames) {
    if (state) {
        audio_thread *at = (audio_thread*)c;
        at->m_audio_device->left_out.zero();
        at->process(at->m_audio_device->left_out,
                    at->m_audio_device->right_out);
        at->m_audio_device->maybe_record();
    }
}

void audio_thread::process(sample &s, sample &s2) {

    command_ring_buffer::command cmd;
	while (m_osc.get(cmd)) {
        string name = cmd.m_name;
		//cerr<<name<<endl;
        if (name=="/start") {
            m_renderer->set_playing(true);
        }
        if (name=="/pause") {
            m_renderer->set_playing(false);
        }
        if (name=="/ratio") {
            m_renderer->get_params()->m_ratio = cmd.get_float(0);
        }
        if (name=="/n_ratio") {
            m_renderer->get_params()->m_n_ratio = cmd.get_float(0);
        }
        if (name=="/fft1_start") {
            m_renderer->get_params()->m_fft1_start = cmd.get_int(0);
        }
        if (name=="/fft1_end") {
            m_renderer->get_params()->m_fft1_end = cmd.get_int(0);
        }
        if (name=="/novelty") {
            m_renderer->get_params()->m_usage_importance = cmd.get_float(0);
        }
        if (name=="/restart_audio") {
            start_audio();
        }
        if (name=="/volume") {
            m_renderer->set_volume(cmd.get_float(0)*10);
        }
        if (name=="/search_algo") {
            switch(cmd.get_int(0)) {
            case 0: m_renderer->set_search_algo(renderer::BASIC); break;
            case 1: m_renderer->set_search_algo(renderer::REV_BASIC); break;
            case 2: m_renderer->set_search_algo(renderer::SYNAPTIC); break;
            case 3: m_renderer->set_search_algo(renderer::SYNAPTIC_SLIDE); break;
            }
        }
        if (name=="/n_mix") {
            m_renderer->set_n_mix(cmd.get_float(0));
        }
        if (name=="/target_mix") {
            m_renderer->set_target_mix(cmd.get_float(0));
        }
        if (name=="/record") {
            m_renderer->set_playing(true);
            m_audio_device->start_recording(cmd.get_string(0));
        }
        if (name=="/stop") {
            m_audio_device->stop_recording();
            m_renderer->set_playing(false);
        }
        if (name=="/boredom") {
            m_renderer->get_source().set_usage_falloff(cmd.get_float(0));
        }
        if (name=="/synapses") {
            m_renderer->get_params()->m_num_synapses=cmd.get_int(0);
        }
    }

    s.zero();
    s2.zero();
    if (!pthread_mutex_trylock(m_brain_mutex)) {
        m_renderer->process(s.get_length(),s.get_non_const_buffer());
        pthread_mutex_unlock(m_brain_mutex);
	s2=s;
    } else {
        cerr<<"audio no lock..."<<endl;
    }
}
