#include "renderer.h"
#include <iostream>

using namespace spiralcore;
using namespace std;

void renderer::init(brain &source, brain &target, float ratio) {
    m_source=source;
    m_target=target;
    m_render_time=0;
    m_render_blocks.clear();
    m_ratio = ratio;
}

static int ratio_time = 0;

void renderer::process(u32 nframes, float *buf) {
    // get blocks from source for the current buffer
    u32 tgt_shift = m_target.get_block_size()-m_target.get_overlap();
    u32 tgt_start = m_render_time/(float)tgt_shift;
    u32 tgt_end = (m_render_time+nframes)/(float)tgt_shift;

    m_ratio = sin((ratio_time++)*0.01)*0.5+0.5;
    cerr<<'\r';
    cerr<<m_ratio;

    if (tgt_end>=m_target.get_num_blocks()) {
        m_render_time=0;
        m_render_blocks.clear();
        // next time...
        return;
    }

//    cerr<<"-----------------"<<endl;
//    cerr<<"tgt start:"<<tgt_start<<endl;
//    cerr<<"tgt end:"<<tgt_end<<endl;

    // get indices for current buffer
    for (u32 tgt_index = tgt_start; tgt_index<=tgt_end; tgt_index++) {
        u32 time=tgt_index*tgt_shift;
        u32 src_index = m_source.search(m_target.get_block(tgt_index), m_ratio);
        // put them in the index list
        m_render_blocks.push_back(render_block(src_index,time));
    }

    // render all blocks in list
    for (std::list<render_block>::iterator i=m_render_blocks.begin(); i!=m_render_blocks.end(); ++i) {
        const sample &pcm=m_source.get_block_pcm(i->m_index);
        // get the sample offset into the buffer
        s32 offset = i->m_time-m_render_time;

        // assume midway through block
        u32 block_start = offset;
        u32 buffer_start = 0;
        if (offset<0) {
            block_start=-offset;
            if (block_start>=pcm.get_length()) i->m_finished=true;
        } else { // block is midway through buffer
            block_start=0;
            buffer_start=offset;
        }

//        cerr<<"-----------------"<<endl;
//        cerr<<"block start:"<<block_start<<endl;
//        cerr<<"buffer start:"<<buffer_start<<endl;

        if (!i->m_finished) {
            // mix in
            u32 buffer_pos = buffer_start;
            u32 block_pos = block_start;
            u32 block_end = pcm.get_length();
            while (block_pos<block_end && buffer_pos<nframes) {
                buf[buffer_pos]+=pcm[block_pos]*0.2;
                ++buffer_pos;
                ++block_pos;
            }
        }
    }

    // delete old ones
    std::list<render_block>::iterator i=m_render_blocks.begin();
    std::list<render_block>::iterator ni=m_render_blocks.begin();
    while(i!=m_render_blocks.end()) {
        ni++;
        if (i->m_finished) m_render_blocks.erase(i);
        i=ni;
    }

    m_render_time+=nframes;
}

bool renderer::unit_test() {
    brain source;
    source.load_sound("test_data/up.wav");
    source.init(10,0,0);

    brain target;
    target.load_sound("test_data/up.wav");
    target.init(10,0,0);

    renderer rr(source,target,1);
    float *buf=new float[10];
    rr.process(10,buf);
    assert(rr.m_render_blocks.size()==2);
    rr.process(10,buf);
    assert(rr.m_render_blocks.size()==3);
    rr.process(20,buf);
    assert(rr.m_render_blocks.size()==4);
    rr.process(5,buf);
    assert(rr.m_render_blocks.size()==2);

    target.init(10,5,0);
    rr.process(10,buf);
    assert(rr.m_render_blocks.size()==5);


}
