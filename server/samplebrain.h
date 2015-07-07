#include "sample.h"
#include <vector>

class brain_block {
    // runs analysis on pcm
    brain_block(const sample &pcm);

    // returns distance based on ratio of fft-mfcc values
    float compare(const brain_block &other, float ratio);

public:
    sample m_pcm;
    sample m_fft;
    sample m_mfcc;
};

class sample_brain {
public:
    sample_brain();

    // rewrites whole brain
    void init(u32 block_size, u32 overlap);

    // take another brain and rebuild this brain from bits of that one
    // (presumably this one is made from a single sample)
    sample resynth(const sample_brain *other, ratio);

private:

    vector<brain_block> m_brain;

    u32 m_block_size;
    u32 m_overlap;

};
