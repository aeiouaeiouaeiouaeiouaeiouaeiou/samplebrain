#include <string>
#include "jellyfish/fluxa/sample.h"
#include "jellyfish/core/types.h"
#include "fft.h"

#ifndef BRAIN_BLOCK
#define BRAIN_BLOCK

namespace spiralcore {

class brain_block {
public:
    // runs analysis on pcm
    brain_block(const std::string &filename, const sample &pcm, u32 rate);

    // returns distance based on ratio of fft-mfcc values
    double compare(const brain_block &other, float ratio) const;

    static void init_fft(u32 block_size);
    static bool unit_test();

private:
    sample m_pcm;
    sample m_fft;
    sample m_mfcc;

    u32 m_block_size;
    u32 m_rate;
    std::string m_orig_filename;
    static FFT *m_fftw;

};

}

#endif
