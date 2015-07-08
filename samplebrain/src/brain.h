#include <vector>
#include "sample.h"
#include "fft.h"

class brain {
public:
    brain();

    // rewrites whole brain
    void init(u32 block_size, u32 overlap);

    // take another brain and rebuild this brain from bits of that one
    // (presumably this one is made from a single sample)
    sample resynth(const sample_brain *other, ratio);

private:

    vector<brain_block> m_blocks;

    u32 m_block_size;
    u32 m_overlap;

};
