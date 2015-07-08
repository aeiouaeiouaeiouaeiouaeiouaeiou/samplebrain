#include <vector>
#include "jellyfish/fluxa/sample.h"
#include "jellyfish/core/types.h"
#include "fft.h"

using namespace spiralcore;

class brain_block {
public:
    // runs analysis on pcm
    brain_block(const sample &pcm);

    // returns distance based on ratio of fft-mfcc values
    float compare(const brain_block &other, float ratio);

    static void init_fft(u32 block_size);

private:
    sample m_pcm;
    sample m_fft;
    sample m_mfcc;

    static FFT *m_fftw;

};
