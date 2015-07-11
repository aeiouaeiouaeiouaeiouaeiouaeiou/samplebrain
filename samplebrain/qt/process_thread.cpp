#include "process_thread.h"
#include <iostream>

using namespace spiralcore;
using namespace std;

process_thread::process_thread() :
    m_osc("8889")
{
    m_brain_mutex = new pthread_mutex_t;
    pthread_mutex_init(m_brain_mutex,NULL);
    m_osc.run();

    // start the processing thread
    pthread_t *thread = new pthread_t;
    pthread_create(thread,NULL,(void*(*)(void*))process_thread::process,this);

}

void process_thread::process(void *c) {
    process_thread *p=(process_thread*)c;
    command_ring_buffer::command cmd;

    while(true) {
        while (p->m_osc.get(cmd)) {
            string name = cmd.m_name;
            cerr<<name<<endl;
            if (name=="/init") {
                p->init_brain();
            }
        }
        usleep(500);
    }
}


void process_thread::init_brain() {
    pthread_mutex_lock(m_brain_mutex);

    cerr<<"starting"<<endl;
//    m_source.load_sound("../sound/source/shostakovich6.wav");
    m_source.load_sound("../../sound/source/808.wav");
    m_source.load_sound("../../sound/source/joey.wav");
    m_source.load_sound("../../sound/source/pw2.wav");
    m_source.load_sound("../../sound/source/pw3.wav");
    m_source.load_sound("../../sound/source/claps.wav");
    m_source.load_sound("../../sound/source/eagle.wav");
//    m_source.load_sound("../sound/source/sailingbybit.wav");


    //target.load_sound("../sound/source/sb-left.wav");
    m_target.load_sound("../../sound/source/apache.wav");
    cerr<<"loaded sounds"<<endl;
    cerr<<endl;
    u32 len=3000;
    m_source.init(len,len-len,50);
    m_target.init(len,len-len/8,50);
    cerr<<"ready..."<<endl;
    cerr<<"we have "<<m_source.get_num_blocks()<<" brain blocks ("<<m_source.get_num_blocks()*len/44100.0<<" secs)"<<endl<<endl;

    pthread_mutex_unlock(m_brain_mutex);

    //target.resynth_listen("shosta-dream-0.5.wav",source,0.5,a);


}
