#include <jellyfish/fluxa/sample.h>
#include <brain.h>

namespace spiralcore {

class realtime_renderer {
public:
    void init(const brain &source, const brain &target);
    void process(u32 nframes, float *buf);

    bool unit_test();

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

    const brain &m_source;
    const brain &m_target;

    list<render_block> m_render_blocks;
    u32 m_render_time;
};

}
