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

#include <list>
#include <vector>
#include <string>
#include "jellyfish/core/types.h"
#include "jellyfish/fluxa/sample.h"
#include "block.h"
#include "search_params.h"
#include "window.h"

#ifndef BRAIN
#define BRAIN

namespace spiralcore {

class brain {
public:
    brain();

    // rewrites whole brain
    void init(u32 block_size, u32 overlap, window::type t, bool ditchpcm=false);

    class sound {
    public:
        sound(const std::string &name, const sample &sample) :
            m_filename(name), m_sample(sample) {}

        std::string m_filename;
        sample m_sample;
    };

    // load, chop up and add to brain
    // todo: add tags
    void load_sound(std::string filename);
    void delete_sound(std::string filename);
    void clear_sounds() { m_samples.clear(); }
    // take another brain and rebuild this brain from bits of that one
    // (presumably this one is made from a single sample)
    void resynth(const std::string &filename, const brain &other, const search_params &params);

    const sample &get_block_pcm(u32 index) const;
    const block &get_block(u32 index) const;
    u32 get_num_blocks() const { return m_blocks.size(); }
    u32 get_block_size() const { return m_block_size; }
    u32 get_overlap() const { return m_overlap; }

    u32 search(const block &target, const search_params &params) const;
    u32 rev_search(const block &target, const search_params &params) const;

    static bool unit_test();

private:

    void chop_and_add(const sample &s, bool ditchpcm=false);

    vector<block> m_blocks;
    std::list<sound> m_samples;

    u32 m_block_size;
    u32 m_overlap;

    window m_window;

};

}

#endif
