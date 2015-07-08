#include <vector>
#include <string>
#include "jellyfish/core/types.h"
#include "jellyfish/fluxa/sample.h"
#include "brain_block.h"

#ifndef BRAIN
#define BRAIN

namespace spiralcore {

class brain {
public:
    brain();

    // rewrites whole brain
    void init(u32 block_size, u32 overlap, bool ditchpcm=false);

    // load, chop up and add to brain
    // todo: add tags
    sample load_sound(std::string filename);
    // take another brain and rebuild this brain from bits of that one
    // (presumably this one is made from a single sample)
    void resynth(const std::string &filename, const brain &other, float ratio);

    const sample &get_block_pcm(u32 index) const;
    static bool unit_test();

private:

    u32 search(const brain_block &target, float ratio) const;
    void chop_and_add(const sample &s, u32 block_size, u32 overlap, bool ditchpcm=false);

    vector<brain_block> m_blocks;
    vector<sample> m_samples;

    u32 m_block_size;
    u32 m_overlap;
};

#endif

}
