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
    m_target_time=0;
    m_render_time=0;
    m_n_mix=0;
    m_target_mix=0;
    m_render_blocks.clear();
    m_search_algo=BASIC;
    m_slide_error=1;
    m_target_index=0;
}

static int ratio_time = 0;

void renderer::process(u32 nframes, float *buf) {
    if (!m_playing) return;

    // get new blocks from source for the current buffer
    u32 tgt_shift = m_target.get_block_size()-m_target.get_overlap();
    u32 tgt_end = (m_target_time+nframes)/(float)tgt_shift;

    if (tgt_end>=m_target.get_num_blocks() || m_source.get_num_blocks()==0) {
        m_target_time=0;
        m_render_time=0;
        m_target_index=0;
        m_render_blocks.clear();
        // next time...
        return;
    }


//    cerr<<"-----------------"<<endl;
//    cerr<<"tgt start:"<<m_target_index<<endl;
//    cerr<<"tgt end:"<<tgt_end<<endl;

    // get indices for current buffer
    u32 counter = m_target_index;
    //u32 cur_time = m_render_time;
    while (counter<=tgt_end) {
        u32 time=m_target_index*tgt_shift;
        u32 src_index=0;

        switch (m_search_algo) {
        case BASIC:
            src_index = m_source.search(m_target.get_block(m_target_index), m_search_params);
            break;
        case REV_BASIC:
            src_index = m_source.rev_search(m_target.get_block(m_target_index), m_search_params);
            break;
        case SYNAPTIC:
        case SYNAPTIC_SLIDE:
            src_index = m_source.search_synapses(m_target.get_block(m_target_index), m_search_params);
            break;
        }

        if (m_search_algo==SYNAPTIC_SLIDE) {
            m_render_blocks.push_back(render_block(src_index,m_target_index,time));

            if (m_source.get_current_error()<m_slide_error) {
                m_target_index++;
            }
            else{ cerr<<"skip"<<endl; }
        } else {
            // put them in the index list
            m_render_blocks.push_back(render_block(src_index,m_target_index,time));
            m_target_index++;
        }
        counter++;
    }

    // render all blocks in list
    for (std::list<render_block>::iterator i=m_render_blocks.begin(); i!=m_render_blocks.end(); ++i) {
        const sample &pcm=m_source.get_block(i->m_index).get_pcm();
        const sample &n_pcm=m_source.get_block(i->m_index).get_n_pcm();
        const sample &target_pcm=m_target.get_block(i->m_tgt_index).get_pcm();
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
                // mix with normalised version
                float brain_sample = (pcm[block_pos]*(1-m_n_mix)+
                                      n_pcm[block_pos]*m_n_mix);

                // for mixing with target audio
                float target_sample = target_pcm[block_pos];

                buf[buffer_pos]+=(brain_sample*(1-m_target_mix) +
                                  target_sample*m_target_mix)*0.2*m_volume;
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
    m_target_time+=nframes;
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
    assert(rr.m_render_blocks.size()==2);
    delete[] buf;
    buf=new float[20];
    rr.process(20,buf);
    assert(rr.m_render_blocks.size()==3);
    rr.process(5,buf);
    assert(rr.m_render_blocks.size()==1);

    target.init(10,5,window::RECTANGLE);
    rr.process(10,buf);
    assert(rr.m_render_blocks.size()==5);
    delete[] buf;

}
