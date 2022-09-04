// Copyright (C) 2003 Dave Griffiths
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

#ifndef SAMPLE
#define SAMPLE

#include <memory.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "types.h"
#include "allocator.h"
#include "stream.h"

namespace spiralcore
{
//#define DEBUG

  inline float linear(float bot,float top,float pos,float val1,float val2) {
    float t=(pos-bot)/(top-bot);
    return val1*t + val2*(1.0f-t);
  }

  inline bool feq(float a, float b, float tol=0.00001) {
    return (a>b-tol && a<b+tol);
  }

  class sample
  {
  public:
    enum sample_type {AUDIO=0, IMAGE, MIDI};

    sample(unsigned int len=0);
    sample(const sample &rhs);
    sample(const audio_type *s, unsigned int len);
    ~sample();

    static void set_allocator(base_allocator *s) { m_allocator=s; }
    static base_allocator *get_allocator() { return m_allocator; }

    bool allocate(unsigned int size);
    void clear();
    void zero();
    void set(audio_type val);
    void insert(const sample &s, unsigned int pos);
    void add(const sample &s);
    void mix(const sample &s, unsigned int pos=0);
    void mul_mix(const sample &s, unsigned int pos, float m);
    void mul_clip_mix(const sample &s, float m);
    void remove(unsigned int start, unsigned int end);
    void reverse(unsigned int start, unsigned int end);
    void move(unsigned int dist);
    // will wrap with minus start index
    void get_region(sample &s, int start, unsigned int end) const;
    const audio_type *get_buffer() const {return m_data;}
    audio_type *get_non_const_buffer() {return m_data;}
    unsigned int get_length() const {return m_length;}
    unsigned int get_length_in_bytes() const {return m_length*sizeof(audio_type);}
    void expand(unsigned int length);
    void shrink(unsigned int length);
    void crop_to(unsigned int new_length);

    audio_type &wrapped_get(int i) const {
      return m_data[i%m_length];
    }

    audio_type &operator[](unsigned int i) const {
#ifdef DEBUG
      cerr<<"debug..."<<endl;
      assert(i<m_length);
#endif
      return m_data[i%m_length];
    }

    // linear interpolated
    inline audio_type operator[](float i) const {
      unsigned int ii=(unsigned int)i;

#ifdef DEBUG
      assert(ii<m_length);
#endif

      if (ii==m_length-1) return m_data[ii%m_length];
      audio_type t=i-ii;
      return ((m_data[ii%m_length]*(1-t))+
	      (m_data[(ii+1)%m_length])*t);
    }


    void set(unsigned int i, audio_type v) {
#ifdef DEBUG
      assert(i<m_length);
#endif
      m_data[i%m_length]=v;
    }

    sample &operator=(const sample &rhs) {
      if (get_length()!=rhs.get_length()) allocate(rhs.get_length());
      memcpy(m_data,rhs.get_buffer(),get_length_in_bytes());
      return *this;
    }

    friend ios &operator||(ios &s, sample &sa);

  private:
    audio_type *m_data;
    unsigned int m_length;

    sample_type m_sample_type;
    static base_allocator *m_allocator;
  };

  ios &operator||(ios &s, sample &sa);

}
#endif
