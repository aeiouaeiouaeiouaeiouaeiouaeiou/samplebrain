#include "audio_thread.h"
#include <iostream>

using namespace spiralcore;
using namespace std;

audio_thread::audio_thread(process_thread &p) :
    m_process_thread(p),
    m_brain_mutex(p.m_brain_mutex),
    m_osc("8888")
{
    pthread_mutex_lock(m_brain_mutex);
    m_renderer = new renderer(p.m_source,p.m_target);
    pthread_mutex_unlock(m_brain_mutex);
    m_osc.run();
}

void audio_thread::process(sample &s) {

    command_ring_buffer::command cmd;
	while (m_osc.get(cmd)) {
        string name = cmd.m_name;
		cerr<<name<<endl;
        if (name=="/ratio") {
            m_renderer->get_params()->m_ratio = cmd.get_float(0);
        }
    }


    s.zero();
    if (!pthread_mutex_trylock(m_brain_mutex)) {
        m_renderer->process(s.get_length(),s.get_non_const_buffer());
        pthread_mutex_unlock(m_brain_mutex);
    } else {
        cerr<<"audio no lock..."<<endl;
    }
}
