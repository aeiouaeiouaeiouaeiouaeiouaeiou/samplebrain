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

    void process();

private:
	OSC_server m_osc;
    u32 m_source_block_size;
    float m_source_overlap;
    u32 m_target_block_size;
    float m_target_overlap;
    float m_env;
};

}
