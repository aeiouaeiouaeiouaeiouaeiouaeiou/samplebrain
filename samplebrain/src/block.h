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

#include <string>
#include "jellyfish/fluxa/sample.h"
#include "jellyfish/core/types.h"
#include "fft.h"
#include "mfcc.h"
#include "search_params.h"
#include "window.h"

#ifndef BLOCK
#define BLOCK

namespace spiralcore {

class block {
public:
    // runs analysis on pcm
    block(const std::string &filename, const sample &pcm, u32 rate, const window &w, bool ditchpcm=false);

    // returns distance based on ratio of fft-mfcc values
    double compare(const block &other, const search_params &params) const;

    static void init_fft(u32 block_size);
    static bool unit_test();

    const sample &get_pcm() const { return m_pcm; }

private:

    void process(const sample &pcm, sample &fft, sample &mfcc);

    double _compare(const sample &fft_a, const sample &mfcc_a,
                    const sample &fft_b, const sample &mfcc_b,
                    const search_params &params) const;

    sample m_pcm;
    sample m_fft;
    sample m_mfcc;

    sample m_n_pcm;
    sample m_n_fft;
    sample m_n_mfcc;

    u32 m_block_size;
    u32 m_rate;
    std::string m_orig_filename;
    static FFT *m_fftw;
    static Aquila::Mfcc *m_mfcc_proc;

};

}

#endif
