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
#include "jellyfish/types.h"
#include "jellyfish/sample.h"
#include "block_source.h"
#include "block.h"
#include "search_params.h"
#include "window.h"

#ifndef BRAIN
#define BRAIN

namespace spiralcore {

class brain : public block_source {
public:
    brain();

    enum stereo_mode { MIX, LEFT, RIGHT };

    // rewrites whole brain
    void init(u32 block_size, u32 overlap, window::type t, bool ditchpcm=false);

    void clear();

    // load, chop up and add to brain
    // todo: add tags
    void load_sound(std::string filename, stereo_mode mode);
    void delete_sound(std::string filename);
    void clear_sounds() { m_samples.clear(); }
    // turns on/off a sound in realtime without reprocessing
    void activate_sound(std::string filename, bool active);

    const sample &get_block_pcm(u32 index) const;
    const sample &get_block_n_pcm(u32 index) const;

    virtual const block &get_block(u32 index) const;
    virtual u32 get_num_blocks() const { return m_blocks.size(); }

    void set_usage_falloff(float s) { m_usage_falloff=s; }
    float get_usage_falloff() { return m_usage_falloff; }

    // basic search
    u32 search(const block &target, const search_params &params);
    u32 rev_search(const block &target, const search_params &params);

    // synaptic search
    double calc_average_diff(search_params &params);
    void build_synapses_thresh(search_params &params, double threshold);
    void build_synapses_fixed(search_params &params);
    u32 search_synapses(const block &target, search_params &params);
    double get_current_error() { return m_current_error; }
    // randomise the synaptic pointer
    void jiggle();

    static bool unit_test();

    class sound {
    public:
        sound(const std::string &name, const sample &sample) :
            m_filename(name), m_sample(sample), m_num_blocks(0),
            m_enabled(true), m_start(0), m_end(0) {}
        sound() {}; // needed for streaming
        std::string m_filename;
        sample m_sample;
        // filled in during chop_and_add
        u32 m_num_blocks;
        bool m_enabled;
        // we store the blocks separately in a flat list, so we can
        // directly index them, but we need to filter them by source
        // sound - so we need to be able to turn large contiguous sets
        // of them on and off (without a big impact on the processing
        // time)
        u32 m_start,m_end;
    };

    const std::list<sound> &get_samples() { return m_samples; }

private:

    void chop_and_add(sound &s, u32 count, bool ditchpcm=false);
    void deplete_usage();
    u32 stickify(const block &target, u32 closest_index, f32 dist, const search_params &params);
    void recompute_sample_sections();
    // checks sample sections
    bool is_block_active(u32 index);

    vector<block> m_blocks;
    std::list<sound> m_samples;
    vector<string> m_active_sounds;

    window m_window;

    u32 m_current_block_index;
    double m_current_error;
    double m_average_error;
    float m_usage_falloff;

    friend ios &operator||(ios &s, brain &b);
    friend ios &operator||(ios &s, sound &b);

};

ios &operator||(ios &s, brain::sound &b);
ios &operator||(ios &s, brain &b);

}

#endif
