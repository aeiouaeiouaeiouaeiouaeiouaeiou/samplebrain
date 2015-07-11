#include "jellyfish/fluxa/OSC_server.h"
#include "process_thread.h"
#include "renderer.h"

#pragma once

namespace spiralcore {

class audio_thread {
public:
    audio_thread(process_thread &p);
    void process(sample &s);

private:

    renderer *m_renderer;
	OSC_server m_osc;
    process_thread &m_process_thread;
    pthread_mutex_t* m_brain_mutex;

};

}
