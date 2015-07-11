#include "jellyfish/fluxa/OSC_server.h"
#include "process_thread.h"
#include "renderer.h"
#include "jellyfish/audio.h"

#pragma once

namespace spiralcore {

class audio_thread {
public:
    audio_thread(process_thread &p);
    void process(sample &s);

    static void run_audio(void* c, unsigned int frames);
    audio_device *m_audio_device;

private:
    void start_audio();

    renderer *m_renderer;
	OSC_server m_osc;
    process_thread &m_process_thread;
    pthread_mutex_t* m_brain_mutex;

};

}
