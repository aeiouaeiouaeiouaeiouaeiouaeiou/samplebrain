#include <assert.h>
#include <iostream>

#include "libmfcc.h"
#include "brain_block.h"

using namespace spiralcore;

FFT *brain_block::m_fftw;

brain_block::brain_block(const string &filename, const sample &pcm, u32 rate) :
    m_pcm(pcm),
    m_fft(pcm.get_length()),
    m_mfcc(13),
    m_block_size(pcm.get_length()),
    m_rate(rate),
    m_orig_filename(filename)
{
    init_fft(m_pcm.get_length());

    for (u32 i=0; i<m_block_size; i++) {
        // convert from float to double
        m_fftw->m_in[i] = m_pcm[i];
    }

    m_fftw->raw_impulse2freq();

    double *spectrum = new double[m_block_size];

    for (u32 i=0; i<m_block_size; i++) {
        // convert from complex to float for storage
        m_fft[i] = m_fftw->m_spectrum[i][0];
        // convert from complex to double for mfcc calc
        spectrum[i] = m_fftw->m_spectrum[i][0];
    }

    for (u32 i=0; i<13; i++) {
        m_mfcc[i] = GetCoefficient(spectrum, rate, 48, m_block_size, i);
    }

    delete[] spectrum;
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
        for (u32 i=0; i<13; ++i) {
            acc+=(m_mfcc[i]-other.m_mfcc[i]) * (m_mfcc[i]-other.m_mfcc[i]);
        }
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
    assert(bb.m_mfcc.get_length()==13);
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
    assert(bb.compare(bb3,1)!=0);
    cpy=bb3;
    }

    assert(cpy.m_pcm.get_length()==20);

    return true;
}
