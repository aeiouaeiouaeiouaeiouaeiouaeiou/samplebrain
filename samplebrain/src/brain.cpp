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

void save_sample(const string &filename, const sample s) {
    SF_INFO sfinfo;
    sfinfo.format=SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    sfinfo.frames=s.get_length();
    sfinfo.samplerate=44100;
    sfinfo.channels=1;
    sfinfo.sections=1;
    sfinfo.seekable=0;
    SNDFILE* f=sf_open(filename.c_str(), SFM_WRITE, &sfinfo);
    if (!f) cerr<<"couldn't open "<<filename<<endl;
    u32 written = sf_writef_float(f, s.get_buffer(), s.get_length());
    if (written!=s.get_length()) cerr<<"error: wrote "<<written<<endl;
    sf_close(f);
}

// rewrites whole brain
void brain::init(u32 block_size, u32 overlap, u32 env, bool ditchpcm) {
    m_blocks.clear();
    m_block_size = block_size;
    m_overlap = overlap;
    for (std::list<sound>::iterator i=m_samples.begin(); i!=m_samples.end(); ++i) {
        chop_and_add(i->m_sample, block_size, overlap, env, ditchpcm);
    }
}

void brain::chop_and_add(const sample &s, u32 block_size, u32 overlap, u32 env, bool ditchpcm) {
    u32 pos=0;
    while (pos+block_size-1<s.get_length()) {
        cerr<<'\r';
        cerr<<"adding: "<<pos/(float)s.get_length()*100;
        sample region;
        s.get_region(region,pos,pos+block_size-1);
        m_blocks.push_back(block("",region,44100,env,ditchpcm));
        pos += (block_size-overlap);
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
    double closest = 999999999;
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
            save_sample(filename,out);
        }

        ++count;
        pos += (m_block_size-m_overlap);
    }
    save_sample(filename,out);
}


bool brain::unit_test() {
    brain b;
    assert(b.m_samples.size()==0);
    assert(b.m_blocks.size()==0);

    b.load_sound("test_data/100f32.wav");
    b.load_sound("test_data/100i16.wav");
    assert(b.m_samples.size()==2);
    b.init(10, 0, 0);
    assert(b.m_blocks.size()==20);
    b.init(10, 5, 0);
    assert(b.m_samples.size()==2);
    assert(b.m_blocks.size()==38);
    b.init(20, 5, 0);
    assert(b.m_samples.size()==2);
    assert(b.m_blocks.size()==12);

    // replicate brains
    brain b2;
    b2.load_sound("test_data/up.wav");
    brain b3;
    b3.load_sound("test_data/up.wav");

    b2.init(512, 0, 20);
    b3.init(512, 0, 20);

    search_params p(1,0,100,0,100);

    assert(b3.search(b2.m_blocks[0],p)==0);
    assert(b3.search(b2.m_blocks[9],p)==9);
    assert(b3.search(b2.m_blocks[19],p)==19);
    assert(b3.search(b2.m_blocks[29],p)==29);

//    sample r = b2.resynth(b,1);
//    assert(r.get_length()==200);

    return true;
}
