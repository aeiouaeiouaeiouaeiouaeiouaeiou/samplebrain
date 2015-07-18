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

void audio_thread::start_audio() {
    if (m_audio_device!=NULL) delete m_audio_device;
    m_audio_device = new audio_device("samplebrain",44100,2048);
    m_audio_device->m_client.set_callback(run_audio, this);
}

void audio_thread::run_audio(void* c, unsigned int frames) {
    audio_thread *at = (audio_thread*)c;
    at->m_audio_device->left_out.zero();
    at->process(at->m_audio_device->left_out,
		at->m_audio_device->right_out);
}

void audio_thread::process(sample &s, sample &s2) {

    command_ring_buffer::command cmd;
	while (m_osc.get(cmd)) {
        string name = cmd.m_name;
		cerr<<name<<endl;
        if (name=="/start") {
            m_renderer->set_playing(true);
        }
        if (name=="/stop") {
            m_renderer->set_playing(false);
        }
        if (name=="/ratio") {
            m_renderer->get_params()->m_ratio = cmd.get_float(0);
        }
        if (name=="/fft1_start") {
            m_renderer->get_params()->m_fft1_start = cmd.get_int(0);
        }
        if (name=="/fft1_end") {
            m_renderer->get_params()->m_fft1_end = cmd.get_int(0);
        }
        if (name=="/fft2_start") {
            m_renderer->get_params()->m_fft2_start = cmd.get_int(0);
        }
        if (name=="/fft2_end") {
            m_renderer->get_params()->m_fft2_end = cmd.get_int(0);
        }
        if (name=="/restart_audio") {
            start_audio();
        }
        if (name=="/volume") {
            m_renderer->set_volume(cmd.get_float(0)*10);
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
