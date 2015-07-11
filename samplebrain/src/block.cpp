#include <assert.h>
#include <iostream>

#include "block.h"

using namespace spiralcore;

FFT *block::m_fftw;
Aquila::Mfcc *block::m_mfcc_proc;

static const int MFCC_FILTERS=12;

void enveloper(sample &s, u32 start, u32 end) {
    for(u32 i=0; i<start; ++i) {
        s[i]*=i/(float)start;
    }
    for(u32 i=0; i<end; ++i) {
        s[(s.get_length()-1)-i]*=i/(float)end;
    }
}

block::block(const string &filename, const sample &pcm, u32 rate, u32 env, bool ditchpcm) :
    m_pcm(pcm),
    m_fft(pcm.get_length()),
    m_mfcc(MFCC_FILTERS),
    m_block_size(pcm.get_length()),
    m_rate(rate),
    m_orig_filename(filename)
{
    init_fft(m_pcm.get_length());
    assert(m_mfcc_proc!=NULL);
    assert(m_fftw!=NULL);

    enveloper(m_pcm,env,env);

    m_fftw->impulse2freq(m_pcm.get_non_const_buffer());

    std::vector<std::complex<double> > mfspec;

    for (u32 i=0; i<m_block_size; ++i) {
        m_fft[i]=m_fftw->m_spectrum[i][0];

        mfspec.push_back(std::complex<double>(m_fftw->m_spectrum[i][0],
                                              m_fftw->m_spectrum[i][1]));
    }

    if (m_block_size>100) m_fft.crop_to(100);
    if (ditchpcm) m_pcm.clear();

    // calculate mfcc
    std::vector<double> m = m_mfcc_proc->calculate(mfspec,MFCC_FILTERS);

    for (u32 i=0; i<MFCC_FILTERS; ++i) {
        m_mfcc[i] = m[i];
    }

}

void block::init_fft(u32 block_size)
{
    if (m_fftw == NULL || m_fftw->m_length!=block_size) {
        if (m_fftw == NULL) delete m_fftw;
        m_fftw = new FFT(block_size);
        if (m_mfcc_proc == NULL) delete m_mfcc_proc;
        m_mfcc_proc = new Aquila::Mfcc(block_size);
    }
}

#define FFT_BIAS 200

double block::compare(const block &other, const search_params &params) const {
    double mfcc_acc=0;
    double fft_acc=0;

/*    s32 fft_start = fftwack-10;
    s32 fft_end = fftwack+10;
    if (fft_start<0) fft_start=0;
    if (fft_end>m_fft.get_length()) fft_end=m_fft.get_length();
*/
    s32 fft_start = params.m_fft1_start;
    s32 fft_end = fmin(params.m_fft1_end,m_fft.get_length());

    if (params.m_ratio==0) {
        for (u32 i=fft_start; i<fft_end; ++i) {
            fft_acc+=(m_fft[i]-other.m_fft[i]) * (m_fft[i]-other.m_fft[i]);
        }
        return (fft_acc/(float)m_fft.get_length())*FFT_BIAS;
    }

    if (params.m_ratio==1) {
        for (u32 i=0; i<MFCC_FILTERS; ++i) {
            mfcc_acc+=(m_mfcc[i]-other.m_mfcc[i]) * (m_mfcc[i]-other.m_mfcc[i]);
        }
        return mfcc_acc/(float)MFCC_FILTERS;
    }

    // calculate both
    for (u32 i=fft_start; i<fft_end; ++i) {
        fft_acc+=(m_fft[i]-other.m_fft[i]) * (m_fft[i]-other.m_fft[i]);
    }
    for (u32 i=0; i<MFCC_FILTERS; ++i) {
        mfcc_acc+=(m_mfcc[i]-other.m_mfcc[i]) * (m_mfcc[i]-other.m_mfcc[i]);
    }

    return (fft_acc/(float)m_fft.get_length())*(1-params.m_ratio)*FFT_BIAS +
        (mfcc_acc/(float)MFCC_FILTERS)*params.m_ratio;
}


bool block::unit_test() {
    sample data(200);
    for (u32 i=0; i<data.get_length(); i++) {
        data[i]=i/(float)data.get_length();
    }

    block bb("test",data,44100,0);

    assert(bb.m_pcm.get_length()==data.get_length());
    //assert(bb.m_fft.get_length()==data.get_length());
    assert(bb.m_mfcc.get_length()==MFCC_FILTERS);
    assert(bb.m_orig_filename==string("test"));
    assert(bb.m_rate==44100);
    assert(bb.m_block_size==data.get_length());

    search_params p(0,0,100,0,100);

    block bb2("test",data,44100,0);
    assert(bb.compare(bb2,p)==0);
    p.m_ratio=1;
    assert(bb.compare(bb2,p)==0);
    p.m_ratio=0.5;
    assert(bb.compare(bb2,p)==0);

    sample data2(200);
    for (u32 i=0; i<data.get_length(); i++) {
        data[i]=i%10;
    }

    block cpy("test",data,100,4);
    {
        block bb3("test",data2,44100,4);
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
