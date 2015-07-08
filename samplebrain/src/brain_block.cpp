#include <assert.h>
#include <iostream>

#include "libmfcc.h"
#include "brain_block.h"

using namespace spiralcore;

FFT *brain_block::m_fftw;

static const int MFCC_FILTERS=48;

void enveloper(sample &s, u32 start, u32 end) {
    for(u32 i=0; i<start; ++i) {
        s[i]*=i/(float)start;
    }
    for(u32 i=0; i<end; ++i) {
        s[(s.get_length()-1)-i]*=i/(float)end;
    }
}

brain_block::brain_block(const string &filename, const sample &pcm, u32 rate, bool ditchpcm) :
    m_pcm(pcm),
    m_fft(pcm.get_length()),
    m_mfcc(MFCC_FILTERS),
    m_block_size(pcm.get_length()),
    m_rate(rate),
    m_orig_filename(filename)
{
    init_fft(m_pcm.get_length());

    enveloper(m_pcm,50,50);

    m_fftw->impulse2freq(m_pcm.get_non_const_buffer(),
                         m_fft.get_non_const_buffer());

    if (m_block_size>30) m_fft.crop_to(30);
    if (ditchpcm) m_pcm.clear();

//    for (u32 i=0; i<MFCC_FILTERS; i++) {
//        m_mfcc[i] = GetCoefficient(m_fft.get_non_const_buffer(), rate, MFCC_FILTERS, m_block_size, i);
//    }
}

void brain_block::init_fft(u32 block_size)
{
    if (m_fftw == NULL || m_fftw->m_length!=block_size) {
        if (m_fftw == NULL) delete m_fftw;
        m_fftw = new FFT(block_size);
    }
}

double brain_block::compare(const brain_block &other, float ratio) const {
    double acc=0;
    // just mfcc
    //if (ratio==1)
    {
        for (u32 i=0; i<m_fft.get_length(); ++i) {
            acc+=(m_fft[i]-other.m_fft[i]) * (m_fft[i]-other.m_fft[i]);
        }

        //for (u32 i=0; i<MFCC_FILTERS; ++i) {
        //    acc+=(m_mfcc[i]-other.m_mfcc[i]) * (m_mfcc[i]-other.m_mfcc[i]);
        //}
    }
    return acc;
}


bool brain_block::unit_test() {
    sample data(20);
    for (u32 i=0; i<data.get_length(); i++) {
        data[i]=i/(float)data.get_length();
    }

    brain_block bb("test",data,44100);

    assert(bb.m_pcm.get_length()==data.get_length());
    assert(bb.m_fft.get_length()==data.get_length());
    assert(bb.m_mfcc.get_length()==MFCC_FILTERS);
    assert(bb.m_orig_filename==string("test"));
    assert(bb.m_rate==44100);
    assert(bb.m_block_size==data.get_length());

    brain_block bb2("test",data,44100);
    assert(bb.compare(bb2,1)==0);

    sample data2(20);
    for (u32 i=0; i<data.get_length(); i++) {
        data[i]=i;
    }

    brain_block cpy("test",data,100);
    {
    brain_block bb3("test",data2,44100);
    cerr<<bb.compare(bb3,1)<<endl;
    assert(bb.compare(bb3,1)!=0);
    cpy=bb3;
    }

    assert(cpy.m_pcm.get_length()==20);

    return true;
}
