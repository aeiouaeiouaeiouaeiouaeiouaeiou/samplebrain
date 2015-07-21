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

//    sleep(1);
}

int main(int argc, char *argv[])
{
    unit_test();

    cerr<<"starting"<<endl;
    brain source, target;
//    source.load_sound("../sound/source/shostakovich6.wav");

    source.load_sound("../sound/source/808.wav");
    source.load_sound("../sound/source/joey.wav");
    source.load_sound("../sound/source/pw2.wav");
    source.load_sound("../sound/source/pw3.wav");
    source.load_sound("../sound/source/claps.wav");
    source.load_sound("../sound/source/eagle.wav");

    target.load_sound("../sound/source/apache.wav");
//    source.load_sound("../sound/source/rise.wav");


    //target.load_sound("../sound/source/sb-left.wav");
//    target.load_sound("../sound/source/rise.wav");
    cerr<<"loaded sounds"<<endl;
    cerr<<endl;
    u32 len=3000;
    source.init(len,len-len,window::DODGY);
    target.init(len,len-len/4,window::DODGY);
    cerr<<"ready..."<<endl;
    cerr<<"we have "<<source.get_num_blocks()<<" brain blocks ("<<source.get_num_blocks()*len/44100.0<<" secs)"<<endl<<endl;

    a = new audio_device("samplebrain",44100,4096);

    //target.resynth_listen("shosta-dream-0.5.wav",source,0.5,a);

    renderer rr(source,target);
    rr.set_playing(true);
    rr.get_params()->m_ratio=0.5;

	a->m_client.set_callback(run_audio, &rr);

    //target.resynth("shosta-dream-0.5.wav",source,0.5);

    while (true) sleep(1);

}
