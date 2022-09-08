// Copyright (C) 2022 Then Try This
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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <float.h>

#include "spiralcore/audio.h"

#include "block.h"
#include "brain.h"
#include "renderer.h"
#include "block_stream.h"
#include <pthread.h>

using namespace std;
using namespace spiralcore;

pthread_mutex_t* m_fuz_mutex;


void unit_test() {
    cerr<<"testing block"<<endl;
    if (block::unit_test()) cerr<<"passed"<<endl;
    else cerr<<"failed"<<endl;
    cerr<<"testing brain"<<endl;
    if (brain::unit_test()) cerr<<"passed"<<endl;
    else cerr<<"failed"<<endl;
    cerr<<"testing renderer"<<endl;
    if (renderer::unit_test()) cerr<<"passed"<<endl;
    else cerr<<"failed"<<endl;
}

audio_device *a = NULL;
block_stream *m_block_stream = NULL;
bool m_mic_mode = true;

void run_audio(void* c, unsigned int frames) {
    a->left_out.zero();
    renderer *rr = (renderer*)c;
    pthread_mutex_lock(m_fuz_mutex);

    block_stream *bs=NULL;

    if (m_mic_mode) {
      m_block_stream->process(a->left_in,a->right_in);      
      bs = m_block_stream;
    }

    rr->process(frames,a->left_out.get_non_const_buffer(),bs);
    
    pthread_mutex_unlock(m_fuz_mutex);
    a->right_out=a->left_out;
    a->maybe_record();

//    sleep(1);
}

const char *fuz_samplefile() {
  switch (rand()%20) {
  case 0: return "../sound/source/KONG.WAV";
  case 1: return "../sound/source/KONG.WAV";
  case 2: return "../sound/source/CCBEGIN.WAV";
  case 3: return "../sound/source/cc-end.wav";
  case 4: return "../sound/source/cc-extra.wav";
  case 5: return "../sound/source/cc-high.wav";
  case 6: return "../sound/source/cc-magic.wav";
  case 7: return "../sound/source/cc-start.wav";
  case 8: return "../sound/source/cc-warp.wav";
//    source.load_sound("../sound/source/shostakovich6.wav");
  case 9: return "../sound/source/808.wav";
  case 10: return "../sound/source/joey.wav";
  case 11: return "../sound/source/pw2.wav";
  case 12: return "../sound/source/pw3.wav";
  case 13: return "../sound/source/claps.wav";
  case 14: return "../sound/source/eagle.wav";
  case 15: return "../sound/source/rise.wav";
  case 16: return "../sound/source/totalsine.wav";
  case 17: return "../sound/source/sailingbybit.wav";
  case 18: return "../sound/source/dreambit.wav";
  case 19: return "../sound/source/apache.wav";
  }
}

float fuz_rr_f(float start, float end) {
  float t=rand()%999999/9999999.0f;
  return t*(end-start)+start;
}

int fuz_rr_i(int start, int end) {
  return (int)fuz_rr_f(start,end);
}

void fuz_new_brain(search_params p) {
  u32 len=fuz_rr_i(500,5000);
  brain source;
  for (int i=0; i<5; i++) {
    cerr<<"loading sound..."<<endl;
    source.load_sound(fuz_samplefile(),brain::MIX);
  }

  cerr<<"loaded sounds"<<endl;
  cerr<<endl;
  source.init(len,len-len,window::HANN);
  source.build_synapses_fixed(p);
  cerr<<"saving brain"<<endl;
  ofstream of("fuz.brain",ios::binary);
  of||source;
  of.close();
}


void fuz() {
    search_params p(0.5,0,0,99,0);

    cerr<<"starting"<<endl;
    //fuz_new_brain(p);
    cerr<<"reloading brain"<<endl;

    brain source;
    ifstream ifs("fuz.brain",ios::binary);
    ifs||source;
    ifs.close();

    brain target;
    target.load_sound(fuz_samplefile(),brain::MIX);
    //    u32 len=fuz_rr_i(500,5000);
    //u32 overlap = len-len/fuz_rr_i(1,16);

    u32 len=5000;
    u32 overlap=len/2;
    target.init(len,overlap,window::HANN);

    m_block_stream = new block_stream();
    m_block_stream->init(len,overlap,window::HANN);

    cerr<<"ready..."<<endl;
    cerr<<"we have "<<source.get_num_blocks()<<" brain blocks ("<<source.get_num_blocks()*len/44100.0<<" secs)"<<endl<<endl;

    a = new audio_device("samplebrain",44100,4096);

    //target.resynth_listen("shosta-dream-0.5.wav",source,0.5,a);

    renderer rr(source,target);
    rr.set_playing(true);
    //    a->start_recording("debug");
    a->m_client.set_callback(run_audio, &rr);
	
    //target.resynth("shosta-dream-0.5.wav",source,0.5);

    u32 counter=0;

    while (true) {
      if (counter>5) {
        pthread_mutex_lock(m_fuz_mutex);

        switch (rand()%10) {
        case 0: {
          fuz_new_brain(*rr.get_params());
          cerr<<"reloading brain"<<endl;
          ifstream ifs("fuz.brain",ios::binary);
          ifs||source;
          ifs.close();
        } break;
        case 1: {
          cerr<<"reloading target"<<endl;
          target.clear();
          target.load_sound(fuz_samplefile(),brain::MIX);
          u32 len=fuz_rr_i(500,5000);
          target.init(len,len-len/fuz_rr_i(1,16),window::HANN);
        } break;
        }

        rr.get_params()->m_ratio=fuz_rr_f(0,1);
        rr.get_params()->m_n_ratio=fuz_rr_f(0,1);
        rr.get_params()->m_fft1_start=fuz_rr_i(0,49);
        rr.get_params()->m_fft1_end=fuz_rr_f(50,100);
        rr.get_params()->m_stickyness=fuz_rr_f(0,1);
        rr.get_params()->m_usage_importance=fuz_rr_f(0,1);
        source.set_usage_falloff(fuz_rr_f(0,1));
        rr.get_params()->m_num_synapses=fuz_rr_i(2,1000);
        rr.set_slide_error(fuz_rr_i(100,10000));

        switch(rand()%3) {
        case 0: rr.set_search_algo(renderer::BASIC); break;
        case 1: rr.set_search_algo(renderer::SYNAPTIC); break;
        case 2: rr.set_search_algo(renderer::SYNAPTIC_SLIDE); break;
        }

        rr.set_target_mix(0.2);
        rr.set_stretch(1);
        counter=0;
        pthread_mutex_unlock(m_fuz_mutex);

      }
      sleep(1);
      counter++;
    }

}

int main(int argc, char *argv[])
{
    m_fuz_mutex = new pthread_mutex_t;
    pthread_mutex_init(m_fuz_mutex,NULL);
    //unit_test();


    fuz();
}
