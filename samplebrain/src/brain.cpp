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

#include <iostream>
#include <sndfile.h>
#include <float.h>
#include <jellyfish/audio.h>
#include "brain.h"

using namespace std;
using namespace spiralcore;

brain::brain()
{
}

// load, chop up and add to brain
// todo: add tags
void brain::load_sound(std::string filename) {
    SF_INFO sfinfo;
    sfinfo.format=0;
    SNDFILE* f=sf_open(filename.c_str(), SFM_READ, &sfinfo);
    if (f!=NULL) {
        sample s(sfinfo.frames);
        sf_readf_float(f, s.get_non_const_buffer(), s.get_length());
        m_samples.push_back(sound(filename,s));
    }
}

void brain::delete_sound(std::string filename) {
    for (std::list<sound>::iterator i=m_samples.begin(); i!=m_samples.end(); ++i) {
        if (i->m_filename==filename) {
            m_samples.erase(i);
            return;
        }
    }
}

// rewrites whole brain
void brain::init(u32 block_size, u32 overlap, window::type t, bool ditchpcm) {
    m_blocks.clear();
    m_block_size = block_size;
    m_overlap = overlap;
    m_window.init(block_size);
    m_window.set_current_type(t);
    for (std::list<sound>::iterator i=m_samples.begin(); i!=m_samples.end(); ++i) {
        chop_and_add(i->m_sample, ditchpcm);
    }
}

void brain::chop_and_add(const sample &s, bool ditchpcm) {
    u32 pos=0;
    if (m_overlap>=m_block_size) m_overlap=0;
    while (pos+m_block_size-1<s.get_length()) {
        cerr<<'\r';
        cerr<<"adding: "<<pos/(float)s.get_length()*100;
        sample region;
        s.get_region(region,pos,pos+m_block_size-1);
        m_blocks.push_back(block("",region,44100,m_window,ditchpcm));
        pos += (m_block_size-m_overlap);
    }
}

const sample &brain::get_block_pcm(u32 index) const {
    return m_blocks[index].get_pcm();
}

const block &brain::get_block(u32 index) const {
    return m_blocks[index];
}

// returns index to block
u32 brain::search(const block &target, const search_params &params) const {
    double closest = FLT_MAX;
    u32 closest_index = 0;
    u32 index = 0;
    for (vector<block>::const_iterator i=m_blocks.begin(); i!=m_blocks.end(); ++i) {
        double diff = target.compare(*i,params);
        if (diff<closest) {
            closest=diff;
            closest_index = index;
        }
        ++index;
    }
    return closest_index;
}

// returns index to block
u32 brain::rev_search(const block &target, const search_params &params) const {
    double furthest = 0;
    u32 furthest_index = 0;
    u32 index = 0;
    for (vector<block>::const_iterator i=m_blocks.begin(); i!=m_blocks.end(); ++i) {
        double diff = target.compare(*i,params);
        if (diff>furthest) {
            furthest=diff;
            furthest_index = index;
        }
        ++index;
    }
    return furthest_index;
}

// take another brain and rebuild this brain from bits of that one
// (presumably this one is made from a single sample)
void brain::resynth(const string &filename, const brain &other, const search_params &params){
    sample out((m_block_size-m_overlap)*m_blocks.size());
    out.zero();
    u32 pos = 0;
    u32 count = 0;
    cerr<<other.m_blocks.size()<<" brain blocks..."<<endl;
    cerr<<endl;
    for (vector<block>::iterator i=m_blocks.begin(); i!=m_blocks.end(); ++i) {
        cerr<<'\r';
        cerr<<"searching: "<<count/float(m_blocks.size())*100;
        u32 index = other.search(*i, params);
        //cerr<<index<<endl;
        out.mul_mix(other.get_block_pcm(index),pos,0.2);

        if (count%1000==0) {
            audio_device::save_sample(filename,out);
        }

        ++count;
        pos += (m_block_size-m_overlap);
    }
    audio_device::save_sample(filename,out);
}


bool brain::unit_test() {
    brain b;
    assert(b.m_samples.size()==0);
    assert(b.m_blocks.size()==0);

    b.load_sound("test_data/100f32.wav");
    b.load_sound("test_data/100i16.wav");
    assert(b.m_samples.size()==2);
    cerr<<"hjelele"<<endl;

    b.init(10, 0, window::RECTANGLE);
    assert(b.m_blocks.size()==20);
    b.init(10, 5, window::RECTANGLE);
    assert(b.m_samples.size()==2);
    assert(b.m_blocks.size()==38);
    b.init(20, 5, window::RECTANGLE);
    assert(b.m_samples.size()==2);
    assert(b.m_blocks.size()==12);


    // replicate brains
    brain b2;
    b2.load_sound("test_data/up.wav");
    brain b3;
    b3.load_sound("test_data/up.wav");

    b2.init(512, 0, window::BLACKMAN);
    b3.init(512, 0, window::BLACKMAN);

    search_params p(1,0,0,100,0,100);

    assert(b3.search(b2.m_blocks[0],p)==0);
    assert(b3.search(b2.m_blocks[9],p)==9);
    assert(b3.search(b2.m_blocks[19],p)==19);
    assert(b3.search(b2.m_blocks[29],p)==29);

//    sample r = b2.resynth(b,1);
//    assert(r.get_length()==200);

    return true;
}
