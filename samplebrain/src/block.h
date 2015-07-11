#include <string>
#include "jellyfish/fluxa/sample.h"
#include "jellyfish/core/types.h"
#include "fft.h"
#include "mfcc.h"
#include "search_params.h"

#ifndef BLOCK
#define BLOCK

namespace spiralcore {

class block {
public:
    // runs analysis on pcm
    block(const std::string &filename, const sample &pcm, u32 rate, u32 env, bool ditchpcm=false);

    // returns distance based on ratio of fft-mfcc values
    double compare(const block &other, const search_params &params) const;

    static void init_fft(u32 block_size);
    static bool unit_test();

    const sample &get_pcm() const { return m_pcm; }

private:
    sample m_pcm;
    sample m_fft;
    sample m_mfcc;

    u32 m_block_size;
    u32 m_rate;
    std::string m_orig_filename;
    static FFT *m_fftw;
    static Aquila::Mfcc *m_mfcc_proc;

};

}

#endif
