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

#include "jellyfish/audio.h"

#include "brain_block.h"
#include "brain.h"

using namespace std;

void unit_test() {
    cerr<<"testing brain_block"<<endl;
    if (brain_block::unit_test()) cerr<<"passed"<<endl;
    else cerr<<"failed"<<endl;
    cerr<<"testing brain"<<endl;
    if (brain::unit_test()) cerr<<"passed"<<endl;
    else cerr<<"failed"<<endl;
}

int main(int argc, char *argv[])
{
    unit_test();

    cerr<<"starting"<<endl;
    brain source, target;
//    source.load_sound("../sound/source/shostakovich6.wav");
    source.load_sound("../sound/source/amen_brother.wav");
    source.load_sound("../sound/source/808.wav");
    source.load_sound("../sound/source/eagle.wav");
    source.load_sound("../sound/source/claps.wav");
    source.load_sound("../sound/source/dream2.wav");

    target.load_sound("../sound/source/camron.wav");
//    target.load_sound("../sound/source/sb-left.wav");
    cerr<<"loaded sounds"<<endl;

    u32 len=3000;
    source.init(len,len-len/4);
    target.init(len,len-len/4);
    cerr<<"ready..."<<endl;

    audio_device *a = new audio_device("samplebrain",44100,2048);
    //target.resynth_listen("shosta-dream-0.5.wav",source,0.5,a);

    //target.resynth("shosta-dream-0.5.wav",source,0.5);



}
