// Copyright (C) 2022 Then Try This
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
#include <spiralcore/sample.h>
#include "brain.h"
#include "block_stream.h"

#ifndef SB_RENDERER
#define SB_RENDERER

namespace spiralcore {

  class renderer {
  public:
  renderer(brain &source, brain &target) :
    m_source(source),
    m_target(target),
    m_search_params(0,0,0,100,0)
    { init(source,target); }

    enum search_algo {
      BASIC = 0,
      REV_BASIC,
      SYNAPTIC,
      SYNAPTIC_SLIDE
    };

    void init(brain &source, brain &target);

    void reset();

    // block stream should be NULL if we are reading the target brain instead
    void process(u32 nframes, float *buf, const block_stream *bs=NULL);

    void set_search_algo(search_algo s) { m_search_algo=s; }
    void set_playing(bool s) { m_playing=s; }
    void set_volume(float s) { m_volume=s; }
    void set_n_mix(float s) { m_n_mix=s; }
    void set_target_mix(float s) { m_target_mix=s; }
    void set_slide_error(double s) { m_slide_error=s; }
    void set_stretch(u32 s) { m_stretch=s; }
    void set_autotune(float s) { m_autotune=s; }
    search_params *get_params() { return &m_search_params; }

    search_algo get_search_algo() { return m_search_algo; }
    float get_volume() { return m_volume; }
    float get_n_mix() { return m_n_mix; }
    float get_target_mix() { return m_target_mix; }
    double get_slide_error() { return m_slide_error; }
    u32 get_stretch() { return m_stretch; }
    float get_autotune() { return m_autotune; }

    brain &get_source() { return m_source; }

    static bool unit_test();

    friend ios &operator||(ios &s, renderer &b);

  private:

    bool find_render_blocks(const block_source &target, u32 nframes);
    void render(const block_source &target, u32 nframes, float *buf);
    void clean_up();


    // realtime stuff
    class render_block {
    public:
    render_block(u32 index, u32 tgt_index, u32 time) :
      m_index(index),
        m_tgt_index(tgt_index),
        m_time(time),
        m_finished(false),
        m_position(0) {}
      u32 m_index;
      u32 m_tgt_index; // original target block
      u32 m_time; // in samples
      bool m_finished;
      float m_position; // in samples
    };

    brain &m_source;
    brain &m_target;

    search_params m_search_params;
    float m_volume;
    bool m_playing;
    u32 m_target_index;
    u32 m_render_index;
    float m_target_time;
    u32 m_render_time;
    u32 m_stretch;
    float m_n_mix;
    float m_target_mix;
    float m_autotune;

    search_algo m_search_algo;
    double m_slide_error;
    u32 m_last_tgt_shift;

    std::list<render_block> m_render_blocks;
  };

  std::ios &operator||(std::ios &s, renderer &b);

}


#endif
