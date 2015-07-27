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

#include <assert.h>
#include <float.h>
#include <iostream>

#include "block.h"

using namespace spiralcore;

FFT *block::m_fftw;
Aquila::Mfcc *block::m_mfcc_proc;

static const int MFCC_FILTERS=12;

double blend(double a, double b, double t) {
    return a*(1-t)+b*t;
}

double square(double a) {
    return a*a;
}

void normalise(sample &in) {
    // find min/max
    float max = 0;
    float min = FLT_MAX;
    for (u32 i=0; i<in.get_length(); ++i) {
        if (in[i]<min) min=in[i];
        if (in[i]>max) max=in[i];
    }

    float mid = min+(max-min)/2.0f;

    // remove dc
    for (u32 i=0; i<in.get_length(); ++i) {
        in[i]-=mid;
    }
    min-=mid;
    max-=mid;

    // squash so biggest value is 1 or -1
    float div = fabs(min);
    if (div<max) div=max;
    div=1/div;

    for (u32 i=0; i<in.get_length(); ++i) {
        in[i]*=div;
    }
}

block::block(const string &filename, const sample &pcm, u32 rate, const window &w, bool ditchpcm) :
    m_pcm(pcm),
    m_fft(pcm.get_length()),
    m_mfcc(MFCC_FILTERS),
    m_n_pcm(pcm),
    m_n_fft(pcm.get_length()),
    m_n_mfcc(MFCC_FILTERS),
    m_block_size(pcm.get_length()),
    m_rate(rate),
    m_orig_filename(filename),
    m_usage(0)
{
    init_fft(m_pcm.get_length());
    assert(m_mfcc_proc!=NULL);
    assert(m_fftw!=NULL);

    w.run(m_pcm);
    process(m_pcm,m_fft,m_mfcc);

    // rerun the normalised version
    normalise(m_n_pcm);
    process(m_n_pcm,m_n_fft,m_n_mfcc);

    if (ditchpcm) {
        m_pcm.clear();
        m_n_pcm.clear();
    }
}


void block::init_fft(u32 block_size)
{
    if (m_fftw == NULL || m_fftw->m_length!=block_size) {
        if (m_fftw == NULL) delete m_fftw;
        m_fftw = new FFT(block_size,100);
        if (m_mfcc_proc == NULL) delete m_mfcc_proc;
        m_mfcc_proc = new Aquila::Mfcc(block_size);
    }
}

void block::process(const sample &pcm, sample &fft, sample &mfcc) {
    m_fftw->impulse2freq(pcm.get_buffer());
    m_fftw->calculate_bins();

    // calculate fft
    std::vector<std::complex<double> > mfspec;
    for (u32 i=0; i<m_block_size; ++i) {
        mfspec.push_back(std::complex<double>(m_fftw->m_spectrum[i][0],
                                              m_fftw->m_spectrum[i][1]));
    }

    u32 fft_size = m_block_size;
    if (fft_size>100) {
        fft.crop_to(100);
        fft_size=100;
    }

    for (u32 i=0; i<fft_size; ++i) {
        fft[i]=m_fftw->m_bin[i];
    }


    // calculate mfcc
    std::vector<double> m = m_mfcc_proc->calculate(mfspec,MFCC_FILTERS);
    for (u32 i=0; i<MFCC_FILTERS; ++i) {
        mfcc[i] = m[i];
    }
}


#define FFT_BIAS 200

double block::_compare(const sample &fft_a, const sample &mfcc_a,
                       const sample &fft_b, const sample &mfcc_b,
                       const search_params &params) const
{
    double mfcc_acc=0;
    double fft_acc=0;

    s32 fft_start = params.m_fft1_start;
    s32 fft_end = fmin(params.m_fft1_end,m_fft.get_length());

    if (params.m_ratio==0) {
        for (u32 i=fft_start; i<fft_end; ++i) {
            fft_acc+=square(fft_a[i]-fft_b[i]);
        }
        return (fft_acc/(float)fft_a.get_length())*FFT_BIAS;
    }

    if (params.m_ratio==1) {
        for (u32 i=0; i<MFCC_FILTERS; ++i) {
            mfcc_acc+=square(mfcc_a[i]-mfcc_b[i]);
        }
        return mfcc_acc/(float)MFCC_FILTERS;
    }

    // calculate both
    for (u32 i=fft_start; i<fft_end; ++i) {
        fft_acc+=square(fft_a[i]-fft_b[i]);
    }
    for (u32 i=0; i<MFCC_FILTERS; ++i) {
        mfcc_acc+=square(mfcc_a[i]-mfcc_b[i]);
    }

    return blend(fft_acc/(float)fft_a.get_length(),
                 mfcc_acc/(float)MFCC_FILTERS,
                 params.m_ratio);
}

double block::compare(const block &other, const search_params &params) const {
    return blend(
        blend(_compare(m_fft, m_mfcc, other.m_fft, other.m_mfcc, params),
              _compare(m_n_fft, m_n_mfcc, other.m_n_fft, other.m_n_mfcc, params),
              params.m_n_ratio),
        other.m_usage, params.m_usage_importance);
}

bool block::unit_test() {

    sample ntest(3);
    u32 idx=0;
    ntest[idx++]=-1;
    ntest[idx++]=1;
    ntest[idx++]=-1;
    idx=0;
    normalise(ntest);
    assert(feq(ntest[idx++],-1));
    assert(feq(ntest[idx++],1));
    assert(feq(ntest[idx++],-1));
    idx=0;
    ntest[idx++]=-2;
    ntest[idx++]=2;
    ntest[idx++]=-2;
    normalise(ntest);
    idx=0;
    assert(feq(ntest[idx++],-1));
    assert(feq(ntest[idx++],1));
    assert(feq(ntest[idx++],-1));
    idx=0;
    ntest[idx++]=19;
    ntest[idx++]=20;
    ntest[idx++]=19;
    normalise(ntest);
    idx=0;
    assert(feq(ntest[idx++],-1));
    assert(feq(ntest[idx++],1));
    assert(feq(ntest[idx++],-1));

    sample data(200);
    for (u32 i=0; i<data.get_length(); i++) {
        data[i]=i/(float)data.get_length();
    }
    window w;
    w.init(data.get_length());
    w.set_current_type(window::RECTANGLE);

    block bb("test",data,44100,w);

    assert(bb.m_pcm.get_length()==data.get_length());
    //assert(bb.m_fft.get_length()==data.get_length());
    assert(bb.m_mfcc.get_length()==MFCC_FILTERS);
    assert(bb.m_orig_filename==string("test"));
    assert(bb.m_rate==44100);
    assert(bb.m_block_size==data.get_length());

    search_params p(0,0,0,100,0);
    block bb2("test",data,44100,w);
    assert(bb.compare(bb2,p)==0);
    p.m_ratio=1;
    assert(bb.compare(bb2,p)==0);
    p.m_ratio=0.5;
    assert(bb.compare(bb2,p)==0);

    sample data2(200);
    for (u32 i=0; i<data.get_length(); i++) {
        data[i]=i%10;
    }

    block cpy("test",data,100,w);
    {
        block bb3("test",data2,44100,w);
        p.m_ratio=0.0;
        assert(bb.compare(bb3,p)!=0);
        assert(bb.compare(bb3,p)!=0);
        p.m_ratio=0.5;
        assert(bb.compare(bb3,p)!=0);
        cpy=bb3;
    }

    assert(cpy.m_pcm.get_length()==200);



    return true;
}
