#include "jellyfish/fluxa/OSC_server.h"
#include "brain.h"
#include <pthread.h>

#pragma once

namespace spiralcore {

class process_thread {
public:
    process_thread();
    void init_brain();

    brain m_source, m_target;
    pthread_mutex_t* m_brain_mutex;

private:
    static void process(void *c);
	OSC_server m_osc;
};

}
