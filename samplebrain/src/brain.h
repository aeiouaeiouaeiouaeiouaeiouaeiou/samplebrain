#include <vector>
#include <string>
#include "jellyfish/core/types.h"
#include "jellyfish/fluxa/sample.h"
#include "block.h"
#include "search_params.h"

#ifndef BRAIN
#define BRAIN

namespace spiralcore {

class brain {
public:
    brain();

    // rewrites whole brain
    void init(u32 block_size, u32 overlap, u32 env, bool ditchpcm=false);

    // load, chop up and add to brain
    // todo: add tags
    sample load_sound(std::string filename);
    // take another brain and rebuild this brain from bits of that one
    // (presumably this one is made from a single sample)
    void resynth(const std::string &filename, const brain &other, const search_params &params);

    const sample &get_block_pcm(u32 index) const;
    const block &get_block(u32 index) const;
    u32 get_num_blocks() const { return m_blocks.size(); }
    u32 get_block_size() const { return m_block_size; }
    u32 get_overlap() const { return m_overlap; }

    u32 search(const block &target, const search_params &params) const;

    static bool unit_test();

private:

    void chop_and_add(const sample &s, u32 block_size, u32 overlap, u32 env, bool ditchpcm=false);

    vector<block> m_blocks;
    vector<sample> m_samples;

    u32 m_block_size;
    u32 m_overlap;

};

}

#endif
