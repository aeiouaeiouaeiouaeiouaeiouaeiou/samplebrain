#include "realtime_renderer.h"

using namespace spiralcore;

void realtime_renderer::init(const brain &source, const brain &target, float ratio) {
    m_source=source;
    m_target=target;
    m_render_time=0;
    m_render_blocks.clear();
    m_ratio = ratio;
}

void realtime_renderer::process(u32 nframes, float *buf) {
    // get blocks from source for the current buffer
    u32 src_shift = m_source.get_block_size()-m_source.get_overlap();
    u32 tgt_shift = m_target.get_block_size()-m_target.get_overlap();

    u32 tgt_start = m_render_time/m_tgt_shift;
    u32 tgt_end = (m_render_time+nframes)/m_tgt_shift;

    // get indices for current buffer
    for (u32 tgt_index = tgt_start; tgt_index<tgt_end; tgt_index++) {
        u32 time=tgt_index*tgt_shift;
        u32 src_index = m_source.search(m_target.get_block(tgt_index), m_ratio);
        // put them in the index list
        m_render_blocks.push_back(render_block(src_index,time));
    }

    // render all blocks in list
    for (list<render_block>::iterator i=m_render_blocks.begin(); i!=m_render_blocks.end(); ++i) {
        sample &pcm=m_source.get_block_pcm(i->m_index);
        // get the sample offset into the buffer
        s32 offset = i->m_time-m_render_time;

        // assume midway through block
        u32 block_start = offset;
        u32 buffer_start = 0;
        if (block_start<0) {
            block_start=-block_start;
        } else { // block is midway through buffer
            block_start=0;
            buffer_start=offset;
            if (buffer_start>nframes) i->m_finished=true;
        }

        if (!i->m_finished) {
            // mix in
            u32 buffer_pos = buffer_start;
            u32 block_pos = block_start;
            u32 block_end = block_start+pcm.get_length();
            while (block_pos<block_end && buffer_pos<nframes) {
                buf[buffer_pos]+=pcm[block_pos];
                ++buffer_pos;
                ++block_pos;
            }
        }
    }

    // delete old ones
    list<render_block>::iterator i=m_render_blocks.begin();
    list<render_block>::iterator ni=m_render_blocks.begin();
    while(i!=m_render_blocks.end()) {
        ni++;
        if (i->m_finished) m_render_blocks.delete(i);
        i=ni;
    }
}

bool realtime_renderer::unit_test() {
    brain source;
    source.load_sound("test_data/up.wav");
    brain target;
    target.load_sound("test_data/up.wav");

    realtime_renderer rr();
    rr.init(source,target,1);

    float *buf=new float[10];
    rr.process(10,buf);

}
