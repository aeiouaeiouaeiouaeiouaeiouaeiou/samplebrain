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
//#include "pitchshift.h"

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
  m_render_index=0;
  m_stretch=1;
  m_last_tgt_shift=0;
  m_autotune=0;
}

static int ratio_time = 0;

void renderer::reset() {
  m_target_time=0;
  m_render_time=0;
  m_target_index=0;
  m_render_index=0;
  m_render_blocks.clear();
  m_source.jiggle();
}


void renderer::process(u32 nframes, float *buf, const block_stream *bs) {
  // we can get blocks from the preprocessed target brain
  // or the realtime block stream
  const block_source *source = (block_source*)bs;
  if (source==NULL) {
    cerr<<"not using block stream..."<<endl;
    source = &m_target;
  } else {
    if (m_target_index<bs->last_block_index()-10) {
      cerr<<"catch up..."<<endl;
      m_target_index = bs->last_block_index();
    }
    if (m_target_index>bs->last_block_index()) {
      cerr<<"catch down..."<<endl;
      m_target_index = bs->last_block_index();
    }
  }

  if (!m_playing) return;
  if (!find_render_blocks(*source,nframes)) return;

  render(*source,nframes,buf);

  clean_up();

  m_render_time+=nframes;
  //m_target_time+=nframes/(float)m_stretch;
}

// target_time = samples time into target stream
// render_time = position in output stream, updated per process - used for offsets

bool renderer::find_render_blocks(const block_source &target, u32 nframes) {
  // get new blocks from source for the current buffer

  // figure out where are in the target blocks
  u32 tgt_shift = target.get_block_size()-target.get_overlap();
  m_target_index = m_target_time/(float)tgt_shift;
  u32 tgt_end = (m_target_time+nframes)/(float)tgt_shift;
  // render end
  u32 rnd_end = (m_render_time+nframes)/(float)tgt_shift;

  // when stuff has changed, or we have fallen off the end
  // then recompute and abort
  if (tgt_shift!=m_last_tgt_shift ||
      tgt_end>=target.get_num_blocks() ||
      m_source.get_num_blocks()==0) {
    reset();
    m_last_tgt_shift = tgt_shift;
    // next time...
    return false;
  }

  
    cerr<<"-----------------"<<endl;
    cerr<<"tgt start:"<<m_target_index<<endl;
    cerr<<"tgt end:"<<tgt_end<<endl;
    cerr<<":"<<tgt_end-m_target_index<<endl;
    cerr<<"target time "<<m_target_time<<endl;
    cerr<<"target time (index) "<<m_target_index*tgt_shift<<endl;
    cerr<<"real vs index = "<<(s32)m_target_time-(s32)(m_target_index*tgt_shift)<<endl;
    cerr<<"render time "<<m_render_time<<endl;
    cerr<<"render time (index) "<<m_render_index*tgt_shift<<endl;
    cerr<<"real vs index = "<<(s32)m_render_time-(s32)(m_render_index*tgt_shift)<<endl;
    cerr<<m_render_blocks.size()<<endl;
  

  // search phase
  // get indices for current buffer
  u32 counter = m_render_index;
  //u32 cur_time = m_render_time;
  while (counter<=rnd_end) {
    u32 time=m_render_index*tgt_shift;
    u32 src_index=0;

    // which algo are we using today?
    switch (m_search_algo) {
    case BASIC:
      src_index = m_source.search(target.get_block(m_target_index), m_search_params);
      break;
    case REV_BASIC:
      src_index = m_source.rev_search(target.get_block(m_target_index), m_search_params);
      break;
    case SYNAPTIC:
    case SYNAPTIC_SLIDE:
      src_index = m_source.search_synapses(target.get_block(m_target_index), m_search_params);
      break;
    }

    if (m_search_algo==SYNAPTIC_SLIDE) {
      m_render_blocks.push_back(render_block(src_index,m_target_index,time));

      // synaptic slide blocks progression of the target until
      // a good enough source block is found
      if (m_source.get_current_error()<m_slide_error &&
          m_render_index%m_stretch==0) {
        m_target_index++;
        m_target_time+=tgt_shift;
      }
    } else {
      // put them in the index list
      m_render_blocks.push_back(render_block(src_index,m_target_index,time));

      if (m_render_index%m_stretch==0) {
        m_target_index++;
        m_target_time+=tgt_shift;
      }
    }
    counter++;
    m_render_index++;
  }
  return true;
}

void renderer::render(const block_source &target, u32 nframes, float *buf) {
  sample render_pcm(m_source.get_block_size());

  // render phase
  // render all blocks in list
  for (std::list<render_block>::iterator i=m_render_blocks.begin(); i!=m_render_blocks.end(); ++i) {
    // get all the pcm data now
    const sample &pcm=m_source.get_block(i->m_index).get_pcm();
    const sample &n_pcm=m_source.get_block(i->m_index).get_n_pcm();
    const sample &target_pcm=target.get_block(i->m_tgt_index).get_pcm();
    // get the sample offset into the buffer
    s32 offset = i->m_time-m_render_time;

    u32 block_length = pcm.get_length();

    // assume midway through block
    u32 block_start = offset;
    u32 buffer_start = 0;
    if (offset<0) {
      // it was running before this buffer
      block_start=-offset;
      if (block_start>=block_length &&
          i->m_position>=block_length) {
        i->m_finished=true;
      }
    } else { // block is midway through buffer
      block_start=0;
      buffer_start=offset;
    }

    //        cerr<<"-----------------"<<endl;
    //        cerr<<"block start:"<<block_start<<endl;
    //        cerr<<"buffer start:"<<buffer_start<<endl;

    // fade in/out autotune
    //pitch_scale = pitch_scale*m_autotune + 1.0f*(1-m_autotune);

    float pitch_scale = 1;

    if (m_autotune>0) {
      // scale by ratio between target and source
      pitch_scale = target.get_block(i->m_tgt_index).get_freq() /
        m_source.get_block(i->m_index).get_freq();
      // restrict min/max pitch bend
      float max = 1+(m_autotune*m_autotune)*100.0f;
      if (pitch_scale>(max)) pitch_scale=max;
      if (pitch_scale<(1/max)) pitch_scale=1/max;
    }

    // pitchshifting sounded rubbish with such small clips
    //pitchshift::process(pcm,pitch_scale,render_pcm);

    if (!i->m_finished) {
      // mix in
      u32 buffer_pos = buffer_start;
      u32 block_pos = block_start;
      u32 block_end = pcm.get_length();

      while (i->m_position<block_end && buffer_pos<nframes) {

        // mix with normalised version
        float brain_sample = (pcm[i->m_position]*(1-m_n_mix)+
                              n_pcm[i->m_position]*m_n_mix);

        float target_sample = 0;

        // if playback scale is lower than target then we may
        // run off the end of the target block
        if (block_pos<block_length) {
          // for mixing with target audio
          target_sample = target_pcm[block_pos];
        }

        buf[buffer_pos]+=(brain_sample*(1-m_target_mix) +
                          target_sample*m_target_mix)*0.2*m_volume;

        i->m_position+=pitch_scale;

        // repeat fast blocks if we are still playing the source
        if (block_pos<block_length &&
            i->m_position>block_end) {
          i->m_position=0;
        }

        ++buffer_pos;
        ++block_pos;
      }
    }
  }
}

void renderer::clean_up() {
  // cleanup phase
  // delete old render blocks that have finished
  std::list<render_block>::iterator i=m_render_blocks.begin();
  std::list<render_block>::iterator ni=m_render_blocks.begin();
  while(i!=m_render_blocks.end()) {
    ni++;
    if (i->m_finished) m_render_blocks.erase(i);
    i=ni;
  }
}

ios &spiralcore::operator||(ios &s, renderer &r) {
    u32 version=0;
    string id("renderer");
    s||id||version;
    s||r.m_search_params;
    s||r.m_volume||r.m_playing||r.m_target_index||r.m_render_index;
    s||r.m_target_time||r.m_render_time||r.m_stretch;
    s||r.m_n_mix||r.m_target_mix||r.m_autotune;
    s||r.m_search_algo||r.m_slide_error||r.m_last_tgt_shift;
    return s;
}

bool renderer::unit_test() {
  brain source;
  source.load_sound("test_data/up.wav", brain::MIX);
  source.init(10,0,window::RECTANGLE);

  brain target;
  target.load_sound("test_data/up.wav", brain::MIX);
  target.init(10,0,window::RECTANGLE);

  renderer rr(source,target);
  rr.set_playing(true);
  float *buf=new float[400];
  rr.process(10,buf);
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
  rr.process(10,buf);
  rr.process(10,buf);
  rr.process(10,buf);
  assert(rr.m_render_blocks.size()==4);
  delete[] buf;

  return true;
}
