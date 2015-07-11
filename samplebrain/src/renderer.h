#include <list>
#include <jellyfish/fluxa/sample.h>
#include "brain.h"

#ifndef SB_RENDERER
#define SB_RENDERER

namespace spiralcore {

class renderer {
public:
    renderer(brain &source, brain &target, float ratio) :
    m_source(source), m_target(target)
    { init(source,target,ratio); }

    void init(brain &source, brain &target, float ratio);
    void process(u32 nframes, float *buf);

    void set_ratio(float s) { m_ratio=s; }

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
    float m_ratio;

    std::list<render_block> m_render_blocks;
    u32 m_render_time;
};

}

#endif
