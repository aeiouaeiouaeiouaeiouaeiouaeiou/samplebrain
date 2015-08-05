// Copyright (C) 2015 Dave Griffiths
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

#include "jellyfish/audio.h"

#include "block.h"
#include "brain.h"
#include "renderer.h"

using namespace std;

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

void run_audio(void* c, unsigned int frames) {
    a->left_out.zero();
    renderer *rr = (renderer*)c;
    rr->process(frames,a->left_out.get_non_const_buffer());
    a->right_out=a->left_out;
    a->maybe_record();

//    sleep(1);
}

int main(int argc, char *argv[])
{
//    unit_test();
    u32 len=1000;
    search_params p(0.5,0,0,99,0);

    cerr<<"starting"<<endl;
/*    {
        brain source;
//    source.load_sound("../sound/source/shostakovich6.wav");

//    source.load_sound("../sound/source/808.wav");
//    source.load_sound("../sound/source/joey.wav");
//    source.load_sound("../sound/source/pw2.wav");
//    source.load_sound("../sound/source/pw3.wav");
//    source.load_sound("../sound/source/claps.wav");
//    source.load_sound("../sound/source/eagle.wav");
  // source.load_sound("../sound/source/rise.wav");
//    source.load_sound("../sound/source/totalsine.wav");

//    source.load_sound("../sound/source/sailingbybit.wav");
//    source.load_sound("../sound/source/dreambit.wav");
    source.load_sound("../sound/source/KONG.WAV");
    source.load_sound("../sound/source/BIRD.WAV");
    source.load_sound("../sound/source/CCBEGIN.WAV");
    source.load_sound("../sound/source/cc-end.wav");
    source.load_sound("../sound/source/cc-extra.wav");
    source.load_sound("../sound/source/cc-high.wav");
    source.load_sound("../sound/source/cc-magic.wav");
    source.load_sound("../sound/source/cc-start.wav");
    source.load_sound("../sound/source/cc-warp.wav");

    cerr<<"loaded sounds"<<endl;
    cerr<<endl;
    source.init(len,len-len,window::HANN);

    source.build_synapses_fixed(p);
    source.set_usage_falloff(0.9);

    ofstream of("8bit.brain",ios::binary);
    of||source;
    of.close();
    }
*/

    brain source;
    ifstream ifs("shosta.brain",ios::binary);
    ifs||source;
    ifs.close();

    brain target;
    target.load_sound("../sound/source/apache.wav");
    //target.load_sound("../sound/source/pw2.wav");
    //target.load_sound("../sound/source/sailingbybit.wav");

    target.init(len,len-len/8,window::HANN);

    cerr<<"ready..."<<endl;
    cerr<<"we have "<<source.get_num_blocks()<<" brain blocks ("<<source.get_num_blocks()*len/44100.0<<" secs)"<<endl<<endl;

    a = new audio_device("samplebrain",44100,4096);

    //target.resynth_listen("shosta-dream-0.5.wav",source,0.5,a);

    renderer rr(source,target);
    rr.set_playing(true);
    rr.get_params()->m_ratio=0;
    rr.get_params()->m_usage_importance=0.6;
    source.set_usage_falloff(0.9);
    rr.get_params()->m_num_synapses=40;
    rr.set_slide_error(3400.5);
    rr.set_search_algo(renderer::SYNAPTIC_SLIDE);
    rr.set_target_mix(0.2);
    a->start_recording("debug");
	a->m_client.set_callback(run_audio, &rr);

    //target.resynth("shosta-dream-0.5.wav",source,0.5);

    while (true) sleep(1);

}
