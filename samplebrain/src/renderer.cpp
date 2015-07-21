// Copyright (C) 2015 Foam Kernow
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include "renderer.h"
#include <iostream>

using namespace spiralcore;
using namespace std;

void renderer::init(brain &source, brain &target) {
    m_volume=1;
    m_playing=false;
    m_source=source;
    m_target=target;
    m_render_time=0;
    m_render_blocks.clear();
}

static int ratio_time = 0;

void renderer::process(u32 nframes, float *buf) {
    if (!m_playing) return;

    // get blocks from source for the current buffer
    u32 tgt_shift = m_target.get_block_size()-m_target.get_overlap();
    u32 tgt_start = m_render_time/(float)tgt_shift;
    u32 tgt_end = (m_render_time+nframes)/(float)tgt_shift;

    if (tgt_end>=m_target.get_num_blocks() || m_source.get_num_blocks()==0) {
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
        u32 src_index = m_source.search(m_target.get_block(tgt_index), m_search_params);
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
                buf[buffer_pos]+=pcm[block_pos]*0.2*m_volume;
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
    source.init(10,0,window::RECTANGLE);

    brain target;
    target.load_sound("test_data/up.wav");
    target.init(10,0,window::RECTANGLE);

    renderer rr(source,target);
    rr.set_playing(true);
    float *buf=new float[10];
    rr.process(10,buf);
    assert(rr.m_render_blocks.size()==2);
    rr.process(10,buf);
    assert(rr.m_render_blocks.size()==3);
    delete[] buf;
    buf=new float[20];
    rr.process(20,buf);
    assert(rr.m_render_blocks.size()==4);
    rr.process(5,buf);
    assert(rr.m_render_blocks.size()==2);

    target.init(10,5,window::RECTANGLE);
    rr.process(10,buf);
    assert(rr.m_render_blocks.size()==5);
    delete[] buf;

}
