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

#include "spiralcore/OSC_server.h"
#include "spiralcore/audio.h"
#include "process_thread.h"
#include "renderer.h"
#include "block_stream.h"

#pragma once

namespace spiralcore {

class audio_thread {
public:
    audio_thread(process_thread &p);
    ~audio_thread();

    void process(sample &left_in, sample &right_in, sample &left_out, sample &right_out);

    static void run_audio(void* c, unsigned int frames);
    audio_device *m_audio_device;

    renderer *m_left_renderer;
    renderer *m_right_renderer;
    block_stream *m_block_stream;

private:
    void start_audio();

	OSC_server m_osc;
    process_thread &m_process_thread;
    pthread_mutex_t* m_brain_mutex;
    bool m_stereo_mode;
    bool m_mic_mode;
};

}
