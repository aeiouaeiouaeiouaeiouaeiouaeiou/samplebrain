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


#include <string.h>
#include "types.h"
#include "sample.h"

using namespace spiralcore;

base_allocator *sample::m_allocator = new malloc_allocator();

sample::sample(unsigned int len) :
  m_data(NULL),
  m_length(0)
{
  if (len) {
      allocate(len);
  }
}


sample::sample(const sample &rhs):
  m_data(NULL),
  m_length(0)
{
  *this=rhs;
}


sample::sample(const audio_type *s, unsigned int len):
  m_data(NULL),
  m_length(0)
{
  assert(s);
  allocate(len);
  memcpy(m_data,s,get_length_in_bytes());
}


sample::~sample() {
  clear();
}



bool sample::allocate(unsigned int size) {
  clear();

  m_data = (audio_type*) m_allocator->anew(size*sizeof(audio_type));
  m_length=size;

  memset(m_data,0,get_length_in_bytes());

  return (m_data);
}

void sample::clear() {
  if (m_data) {
    m_allocator->adelete((char*)m_data);
    m_length=0;
    m_data=NULL;
  }
}

void sample::zero() {
  memset(m_data,0,get_length_in_bytes());
}

void sample::set(audio_type val) {
  for (unsigned int n=0; n<m_length; n++) {
    m_data[n]=val;
  }
}

void sample::insert(const sample &s, unsigned int pos) {
  // do some checking
  assert(pos<=get_length());

  unsigned int new_len = get_length()+s.get_length();
  audio_type *new_buf = (audio_type*) m_allocator->anew(new_len*sizeof(audio_type));
  unsigned int from_pos=0, to_pos=0, temp_buf_pos=0;

  while (from_pos<=get_length()) {
    if (from_pos==pos) {
      for (temp_buf_pos=0; temp_buf_pos<s.get_length(); temp_buf_pos++) {
	new_buf[to_pos]=s[temp_buf_pos];
	to_pos++;
      }
    } else {
      // this test is needed so the loop can deal
      // with samples being "inserted" on to the
      // very end of the buffer
      if (from_pos<get_length()) {
	new_buf[to_pos]=m_data[from_pos];
      }
    }
    from_pos++;
    to_pos++;
  }

  clear();
  m_data=new_buf;
  m_length=new_len;
}

void sample::add(const sample &s) {
  insert(s,get_length());
}

void sample::mix(const sample &s, unsigned int pos) {
  // do some checking
  assert(pos<get_length());

  unsigned int to_pos=pos;

  for (unsigned int from_pos=0; from_pos<s.get_length(); from_pos++) {
    m_data[to_pos]=m_data[to_pos]+s[from_pos];
    
    if (to_pos>get_length()) to_pos=0;
    to_pos++;
  }
}

void sample::mul_mix(const sample &s, unsigned int pos, float m) {
  // do some checking
  assert(pos<get_length());

  unsigned int to_pos=pos;

  for (unsigned int from_pos=0; from_pos<s.get_length(); from_pos++) {
    m_data[to_pos]=m_data[to_pos]+s[from_pos]*m;
    
    if (to_pos>get_length()) to_pos=0;
    to_pos++;
  }
}

void sample::mul_clip_mix(const sample &s, float m) {
  unsigned int to_pos=0;
  
  for (unsigned int from_pos=0; from_pos<s.get_length(); from_pos++) {
    float t=s[from_pos]*m;
    if (t>m) t=m;
    else if (t<-m) t=-m;
    
    m_data[to_pos]=m_data[to_pos]+t;
    
    if (to_pos>get_length()) to_pos=0;
    to_pos++;
  }
}

void sample::remove(unsigned int start, unsigned int end) {
  // do some checking
  assert(end<get_length() && start<get_length());
  assert(start<=end);

  // check the range
  if (end>get_length()) end=get_length();
  // unsigned, impossible
  //if (start<0) start=0;

  // calc lengths and allocate memory
  unsigned int cut_len = end - start;
  // has to be granulated by the buffer size

  unsigned int new_len = get_length()-cut_len;

  audio_type *temp_buf = (audio_type*) m_allocator->anew(new_len*sizeof(audio_type));

  unsigned int to_pos=0;

  for (unsigned int from_pos=0; from_pos<get_length(); from_pos++) {
    // copy the areas outside of the cut range
    if (from_pos<start || from_pos>end) {
      temp_buf[to_pos]=m_data[from_pos];
      to_pos++;
      // check the position is in range of the calculated length
      assert(to_pos<=new_len);
    }
  }
  
  clear();
  m_data=temp_buf;
  m_length=new_len;
}

void sample::reverse(unsigned int start, unsigned int end) {
  // do some checking
  assert(end<get_length() && start<get_length());
  assert(start<=end);

  // check the range
  if (end>get_length()) end=get_length();

  unsigned int new_len = end-start;
  audio_type *temp_buf = (audio_type*) m_allocator->anew(new_len*sizeof(audio_type));
  unsigned int to_pos=0;
  unsigned int from_pos=0;

  // get the reversed sample
  for (from_pos=end; from_pos>start; from_pos--) {
    temp_buf[to_pos]=m_data[from_pos];
    to_pos++;
    assert(to_pos<=new_len);
  }

  from_pos=0;

  // overwrite back into place
  for (to_pos=start; to_pos<end; to_pos++) {
    m_data[to_pos]=temp_buf[from_pos];
    from_pos++;
  }

}

void sample::move(unsigned int dist) {
  unsigned int length=get_length();
  audio_type *temp_buf = (audio_type*) m_allocator->anew(length*sizeof(audio_type));
  unsigned int to_pos=0;
  unsigned int from_pos=dist;

  // unsigned - impossible
  //if (from_pos<0) from_pos+=length;
  if (from_pos>length) from_pos-=length;

  // get the offset sample
  for (to_pos=0; to_pos<length; to_pos++) {
    temp_buf[to_pos]=m_data[from_pos];
    from_pos++;
    if (from_pos>=length) from_pos=0;
  }

  clear();
  m_data=temp_buf;
  m_length=length;
}

// will wrap with minus start index
void sample::get_region(sample &s, int start, unsigned int end) const {
  // do some checking
  assert(end<get_length() && start<(s32)get_length());
  assert(start<=(s32)end);

  unsigned int length=end-start;
  s.allocate(length);

  unsigned int from_pos=start;

  for (unsigned int to_pos=0; to_pos<length; to_pos++) {
    s.set(to_pos,wrapped_get(from_pos));
    from_pos++;
  }
}

void sample::crop_to(unsigned int new_length) {
  assert (new_length<get_length());

  audio_type *temp = (audio_type*) m_allocator->anew(new_length*sizeof(audio_type));

  for(unsigned int n=0; n<new_length; n++) {
    temp[n]=m_data[n];
  }

  clear();
  m_data=temp;
  m_length=new_length;
}

// adds length amount of blank space
void sample::expand(unsigned int length) {
  sample temp(length);
  temp.zero();

  add(temp);
}

// shrink the samle by length amount
void sample::shrink(unsigned int length) {
  unsigned int new_length=get_length()-length;
  assert(new_length>0 && new_length<=get_length());

  audio_type *temp = (audio_type*) m_allocator->anew(new_length*sizeof(audio_type));

  for(unsigned int n=0; n<new_length; n++) {
    temp[n]=m_data[n];
  }

  clear();
  m_data=temp;
  m_length=new_length;
}

ios &spiralcore::operator||(ios &s, sample &sa) {
  unsigned int version=1;
  string id("sample");
  s||id||version;
  s||sa.m_sample_type;

  ofstream *pos=dynamic_cast<ofstream*>(&s);
  if (pos!=NULL) {
    ofstream &os = *pos;
    size_t len = sa.m_length;
    os.write((char*)&len,sizeof(size_t));
    os.write((char*)sa.m_data,sa.m_length*sizeof(audio_type));
    return os;
  }
  else
    {
      ifstream *pis=dynamic_cast<ifstream*>(&s);
      assert(pis!=NULL);
      ifstream &is = *pis;
      size_t len=0;
      is.read((char *)&len,sizeof(size_t));
      float *data = new float[len];
      is.read((char*)data,len*sizeof(audio_type));
      sa.m_data = data;
      sa.m_length = len;
      return is;
    }
}
