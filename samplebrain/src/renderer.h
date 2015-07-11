#include <list>
#include <jellyfish/fluxa/sample.h>
#include "brain.h"

#ifndef SB_RENDERER
#define SB_RENDERER

namespace spiralcore {

class renderer {
public:
    renderer(brain &source, brain &target) :
    m_source(source),
    m_target(target),
    m_search_params(0,0,100,0,100)
    { init(source,target); }

    void init(brain &source, brain &target);
    void process(u32 nframes, float *buf);

    void set_playing(bool s) { m_playing=s; }
    void set_volume(float s) { m_volume=s; }
    search_params *get_params() { return &m_search_params; }

    static bool unit_test();

private:

    // realtime stuff
    class render_block {
    public:
        render_block(u32 index, u32 time) :
            m_index(index), m_time(time), m_finished(false) {}
        u32 m_index;
        u32 m_time; // in samples
        bool m_finished;
    };

    brain &m_source;
    brain &m_target;

    search_params m_search_params;
    float m_volume;
    bool m_playing;

    std::list<render_block> m_render_blocks;
    u32 m_render_time;
};

}

#endif
