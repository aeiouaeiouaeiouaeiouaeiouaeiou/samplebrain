#include <iostream>
#include <sndfile.h>
#include "brain.h"

using namespace std;
using namespace spiralcore;

brain::brain()
{
}

// load, chop up and add to brain
// todo: add tags
sample brain::load_sound(std::string filename) {
    SF_INFO sfinfo;
    sfinfo.format=0;
    SNDFILE* f=sf_open(filename.c_str(), SFM_READ, &sfinfo);
    sample s(sfinfo.frames);
    sf_read_float(f, s.get_non_const_buffer(), s.get_length());
    sf_close(f);
    m_samples.push_back(s);
    return s;
}

// rewrites whole brain
void brain::init(u32 block_size, u32 overlap) {
    m_blocks.clear();
    m_block_size = block_size;
    m_overlap = overlap;
    for (vector<sample>::iterator i=m_samples.begin(); i!=m_samples.end(); ++i) {
        chop_and_add(*i, block_size, overlap);
    }
}

void brain::chop_and_add(const sample &s, u32 block_size, u32 overlap) {
    u32 pos=0;
    while (pos+block_size-1<s.get_length()) {
        sample region;
        s.get_region(region,pos,pos+block_size-1);
        m_blocks.push_back(brain_block("",region,44100));
        pos += block_size-overlap;
    }
}

const sample &brain::get_block_pcm(u32 index) const {
    return m_blocks[index].get_pcm();
}


// returns index to block
u32 brain::search(const brain_block &target, float ratio) const {
    double closest = 999999999;
    u32 closest_index = 0;
    u32 index = 0;
    for (vector<brain_block>::const_iterator i=m_blocks.begin(); i!=m_blocks.end(); ++i) {
        double diff = target.compare(*i,ratio);
        if (diff<closest) {
            closest=diff;
            closest_index = index;
        }
        ++index;
    }
    return closest_index;
}

// take another brain and rebuild this brain from bits of that one
// (presumably this one is made from a single sample)
sample brain::resynth(const brain &other, float ratio){
    sample out(m_block_size*m_blocks.size());
    u32 pos=0;
    for (vector<brain_block>::iterator i=m_blocks.begin(); i!=m_blocks.end(); ++i) {
        u32 index = other.search(*i,ratio);
        out.mix(other.get_block_pcm(index),pos);
        pos += m_block_size-m_overlap;
    }
    return out;
}


bool brain::unit_test() {
    brain b;
    assert(b.m_samples.size()==0);
    assert(b.m_blocks.size()==0);

    sample s=b.load_sound("test_data/100f32.wav");
    assert(b.m_samples.size()==1);
    assert(s.get_length()==100);

    s=b.load_sound("test_data/100i16.wav");
    assert(b.m_samples.size()==2);
    assert(s.get_length()==100);

    b.init(10, 0);
    assert(b.m_samples.size()==2);
    assert(b.m_blocks.size()==20);
    b.init(10, 5);
    assert(b.m_samples.size()==2);
    assert(b.m_blocks.size()==38);
    b.init(20, 5);
    assert(b.m_samples.size()==2);
    assert(b.m_blocks.size()==12);

    // replicate brain
    brain b2;
    b2.load_sound("test_data/100f32.wav");
    b2.load_sound("test_data/100f32.wav");
    assert(b2.m_samples.size()==2);
    b2.init(10, 0);
    b.init(10, 0);
    assert(b2.m_blocks.size()==20);
    assert(b.search(b2.m_blocks[0],1)==0);
    assert(b.search(b2.m_blocks[9],1)==9);

    sample r = b2.resynth(b,1);
    assert(r.get_length()==200);

    return true;
}
