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

#include <iostream>
#include <algorithm>
#include <sndfile.h>
#include <float.h>
#include <spiralcore/audio.h>
#include "brain.h"
#include "status.h"

using namespace std;
using namespace spiralcore;

static const u32 NUM_FIXED_SYNAPSES = 1000;
static const double usage_factor = 1000;

brain::brain() :
  m_current_block_index(0),
  m_current_error(0),
  m_average_error(0),
  m_usage_falloff(0.9)
{
  status::update("brain ready...");
}

// load, chop up and add to brain
// todo: add tags
void brain::load_sound(std::string filename, stereo_mode mode) {
  SF_INFO sfinfo;
  sfinfo.format=0;
  SNDFILE* f=sf_open(filename.c_str(), SFM_READ, &sfinfo);
  if (f!=NULL) {
    sample s(sfinfo.frames);
    float *temp = new float[sfinfo.channels * sfinfo.frames];

    sf_read_float(f, temp, sfinfo.channels * sfinfo.frames);

    if (mode==MIX) {
      for(u32 i=0; i<sfinfo.frames; i++) {
	s[i]=0;
	// mix down stereo to mono
	for(u32 j = 0; j < sfinfo.channels; j++) {
	  s[i]+=temp[i*sfinfo.channels + j];
	}
      }
    } else {
      // just take one channel (assume stereo, split if mono)
      for(u32 i=0; i<sfinfo.frames; i++) {
	u32 si=i*sfinfo.channels;
	if (mode==RIGHT && sfinfo.channels>1) si++;
	s[i]=temp[si];
      }
    }

    delete[] temp;
    m_samples.push_back(sound(filename,s));
    status::update("loaded %s",filename.c_str());
  }
}

void brain::delete_sound(std::string filename) {
  for (auto i=m_samples.begin(); i!=m_samples.end(); ++i) {
    if (i->m_filename==filename) {
      m_samples.erase(i);
      status::update("deleted %s",filename.c_str());
      return;
    }
  }
  recompute_sample_sections();
}

void brain::activate_sound(std::string filename, bool active) {
  for (auto i=m_samples.begin(); i!=m_samples.end(); ++i) {
    if (filename==i->m_filename) {
      i->m_enabled=active;
    }
  }
}

void brain::clear() {
  m_blocks.clear();
  m_samples.clear();
  m_active_sounds.clear();
}

// rewrites whole brain
void brain::init(u32 block_size, u32 overlap, window::type t, bool ditchpcm) {
  m_blocks.clear();
  m_block_size = block_size;
  m_overlap = overlap;
  m_window.init(block_size);
  m_window.set_current_type(t);
  u32 count=0;
  for (auto &s:m_samples) {
    status::sound_item(s.m_filename,"lightgrey");
  }
  for (auto &s:m_samples) {
    status::sound_item(s.m_filename,"yellow");
    count++;
    chop_and_add(s, count, ditchpcm);
    if (count%2==0) status::sound_item(s.m_filename,"lightblue");
    else status::sound_item(s.m_filename,"pink");
  }
  status::sound_item_refresh();
  status::update("all samples processed");
}

void brain::chop_and_add(sound &s, u32 count, bool ditchpcm) {
  s.m_start = m_blocks.size();
  u32 pos=0;
  if (m_overlap>=m_block_size) m_overlap=0;
  u32 len = s.m_sample.get_length();

  // need to stop the progress updates flooding osc
  u32 update_period = (len/m_block_size)/100;
  u32 update_tick = 0;

  while (pos+m_block_size-1<len) {
    sample region;
    s.m_sample.get_region(region,pos,pos+m_block_size-1);
    m_blocks.push_back(block(m_blocks.size(),s.m_filename,region,44100,m_window,ditchpcm));
    pos += (m_block_size-m_overlap);

    // periodic progress update
    if (update_tick>update_period) {
      status::update("processing sample %d: %d%%",count,(int)(pos/(float)s.m_sample.get_length()*100));
      update_tick=0;
    }
    update_tick++;
  }
  s.m_end = m_blocks.size()-1;
  s.m_num_blocks = s.m_end-s.m_start;
}

// needed after we delete a sample from the brain
void brain::recompute_sample_sections() {
  u32 pos=0;
  for (auto &s : m_samples) {
    s.m_start = pos;
    pos += s.m_num_blocks;
    s.m_end = pos+1;
  }
}

const block &brain::get_block(u32 index) const {
  return m_blocks[index];
}

// helper to do the stickyness comparison and sort out current_block_index
u32 brain::stickify(const block &target, u32 closest_index, f32 dist, const search_params &params) {
  u32 next_index = m_current_block_index+1;

  // if we have stickyness turned on and the next block exists
  if (params.m_stickyness>0 && next_index<m_blocks.size()) {
    // get next block
    f32 dist_to_next = target.compare(m_blocks[next_index],params);
    if (dist_to_next * (1-params.m_stickyness) <
	dist * params.m_stickyness) {
      // use the next block rather than the closest
      m_current_block_index = next_index;
      return m_current_block_index;
    }
  }
  // use the closest block
  m_current_block_index = closest_index;
  return m_current_block_index;
}

// returns index to block
u32 brain::search(const block &target, const search_params &params) {
  double closest = FLT_MAX;
  u32 closest_index = 0;
  // check each sample section
  for (auto &s : m_samples) {
    if (s.m_enabled) { // are we turned on?
      // loop through indexes for this section
      for (u32 i=s.m_start; i<s.m_end; ++i) {
	double diff = target.compare(m_blocks[i],params);
	if (diff<closest) {
	  closest=diff;
	  closest_index = i;
	}
      }
    }
  }
  deplete_usage();
  m_blocks[closest_index].get_usage()+=usage_factor;
  return stickify(target,closest_index,closest,params);
}

// returns index to block
u32 brain::rev_search(const block &target, const search_params &params) {
  double furthest = 0;
  u32 furthest_index = 0;
  // check each sample section
  for (auto &s : m_samples) {
    if (s.m_enabled) { // are we turned on?
      // loop through indexes for this section
      for (u32 i=s.m_start; i<s.m_end; ++i) {
	double diff = target.compare(m_blocks[i],params);
	if (diff>furthest) {
	  furthest=diff;
	  furthest_index = i;
	}
      }
    }
  }
  deplete_usage();
  m_blocks[furthest_index].get_usage()+=usage_factor;
  m_current_block_index = furthest_index;

  return furthest_index;
}

// really slow - every to every comparison of blocks calculating average distance
double brain::calc_average_diff(search_params &params) {
  double diff=0;
  for (auto &i:m_blocks) {
    for (auto &j:m_blocks) {
      diff += j.compare(i,params);
    }
    diff/=(double)m_blocks.size();
  }
  return diff;
}

void brain::build_synapses_thresh(search_params &params, double thresh) {
  m_average_error = calc_average_diff(params)*thresh;
  double err = m_average_error*thresh;
  u32 brain_size = m_blocks.size();
  u32 outer_index = 0;
  for (auto &i : m_blocks) {
    u32 index = 0;
    status::update("building synapses %d%%",(int)(outer_index/(float)brain_size*100));
    for (auto &j : m_blocks) {
      if (index!=outer_index) {
	// collect connections that are under threshold in closeness
	double diff = i.compare(j,params);
	if (diff<err) {
	  i.get_synapse().push_back(index);
	}
      }
      ++index;
    }
    ++outer_index;
  }
}

void brain::build_synapses_fixed(search_params &params) {
  //m_average_error = calc_average_diff(params)*thresh;
  u32 brain_size = m_blocks.size();
  u32 outer_index = 0;
  u32 num_synapses = NUM_FIXED_SYNAPSES;
  if (num_synapses>=m_blocks.size()) num_synapses=m_blocks.size()-1;

  for (auto &i:m_blocks) {
    status::update("building synapses %d%%",(int)(outer_index/(float)brain_size*100));
    u32 index = 0;
    vector<pair<u32,double>> collect;

    // collect comparisons to all other blocks
    for (auto &j:m_blocks) {
      assert(index<m_blocks.size());
      if (index!=outer_index) {
	double diff = i.compare(j,params);
	collect.push_back(pair<u32,double>(index,diff));
      }
      ++index;
    }

    // sort them by closeness
    sort(collect.begin(),collect.end(),
	 [](const pair<u32,double> &a,
	    const pair<u32,double> &b) -> bool {
	   return a.second<b.second;
	 });

    // add the closest ones to the list
    for(u32 n=0; n<num_synapses; ++n) {
      assert(collect[n].first<m_blocks.size());
      i.get_synapse().push_back(collect[n].first);
    }

    ++outer_index;
  }
  status::update("Done: %d synapses grown for %d blocks",num_synapses*brain_size,brain_size);
}

// randomise the current block
void brain::jiggle() {
  if (m_blocks.size()>0) {
    m_current_block_index=rand()%m_blocks.size();
  } else {
    m_current_block_index=0;
  }
}

bool brain::is_block_active(u32 index) {
  // check each sample section
  for (auto &s:m_samples) {
    if (index>=s.m_start && index<s.m_end && s.m_enabled) {
      return true;
    }
  }
  return false;
}

u32 brain::search_synapses(const block &target, search_params &params) {
  const block &current = get_block(m_current_block_index);
  double closest = DBL_MAX;
  u32 closest_index = 0;

  // find nearest in synaptic connections
  if (current.get_synapse_const().size()<params.m_num_synapses) {
    params.m_num_synapses = current.get_synapse_const().size()-1;
  }
  //    assert(current.get_synapse_const().size()>params.m_num_synapses);

  u32 synapse_count=0;
  // use m_num_synapses to restrict search
  // only makes sense when ordered by closeness in fixed mode
  vector<u32>::const_iterator i=current.get_synapse_const().begin();
  while (i!=current.get_synapse_const().end() &&
	 synapse_count<params.m_num_synapses) {
    //assert(*i<m_blocks.size());

    if (is_block_active(*i)) {
      const block &other = get_block(*i);
      double diff = target.compare(other,params);
      if (diff<closest) {
	closest=diff;
	closest_index = *i;
      }
    }
    ++i;
    ++synapse_count;
  }

  deplete_usage();
  m_blocks[m_current_block_index].get_usage()+=usage_factor;
  m_current_error = closest;

  // probably impossible to be false?
  if (closest_index!=0) {
    //cerr<<"usage:"<<m_blocks[closest_index].get_usage()<<endl;
    return stickify(target,closest_index,closest,params);
  }
  return m_current_block_index;
}

void brain::deplete_usage() {
  for (vector<block>::iterator i=m_blocks.begin(); i!=m_blocks.end(); ++i) {
    i->get_usage()*=m_usage_falloff;
  }
}


// take another brain and rebuild this brain from bits of that one
// (presumably this one is made from a single sample)
/*void brain::resynth(const string &filename, const brain &other, const search_params &params){
  sample out((m_block_size-m_overlap)*m_blocks.size());
  out.zero();
  u32 pos = 0;
  u32 count = 0;
  cerr<<other.m_blocks.size()<<" brain blocks..."<<endl;
  cerr<<endl;
  for (vector<block>::iterator i=m_blocks.begin(); i!=m_blocks.end(); ++i) {
  cerr<<'\r';
  cerr<<"searching: "<<count/float(m_blocks.size())*100;
  u32 index = other.search(*i, params);
  //cerr<<index<<endl;
  out.mul_mix(other.get_block_pcm(index),pos,0.2);

  if (count%1000==0) {
  audio_device::save_sample(filename,out);
  }

  ++count;
  pos += (m_block_size-m_overlap);
  }
  audio_device::save_sample(filename,out);
  }
*/

ios &spiralcore::operator||(ios &s, brain::sound &b) {
  u32 version=1;
  string id("brain::sound");
  s||id||version;
  s||b.m_filename||b.m_sample;
  if (version>0) {
    s||b.m_num_blocks||b.m_start||b.m_end||b.m_enabled;
  }
  return s;
}

ios &spiralcore::operator||(ios &s, brain &b) {
  u32 version=1;
  string id("brain");
  // changes here need to be reflected in interface loading
  s||id||version;
  stream_vector(s,b.m_blocks);
  stream_list(s,b.m_samples);
  s||b.m_block_size||b.m_overlap||b.m_window;
  s||b.m_current_block_index||b.m_current_error||
    b.m_average_error||b.m_usage_falloff;
  return s;
}

bool brain::unit_test() {
  brain b;
  assert(b.m_samples.size()==0);
  assert(b.m_blocks.size()==0);

  b.load_sound("test_data/100f32.wav",MIX);
  b.load_sound("test_data/100i16.wav",MIX);
  assert(b.m_samples.size()==2);

  b.init(10, 0, window::RECTANGLE);
  assert(b.m_blocks.size()==20);
  b.init(10, 5, window::RECTANGLE);
  assert(b.m_samples.size()==2);
  assert(b.m_blocks.size()==38);
  b.init(20, 5, window::RECTANGLE);
  assert(b.m_samples.size()==2);
  assert(b.m_blocks.size()==12);


  // replicate brains
  brain b2;
  b2.load_sound("test_data/up.wav",MIX);
  brain b3;
  b3.load_sound("test_data/up.wav",MIX);

  b2.init(512, 0, window::BLACKMAN);
  b3.init(512, 0, window::BLACKMAN);

  search_params p(1,0,0,100,0);

  assert(b3.search(b2.m_blocks[0],p)==0);
  //assert(b3.search(b2.m_blocks[9],p)==9);
  //assert(b3.search(b2.m_blocks[19],p)==19);
  //assert(b3.search(b2.m_blocks[29],p)==29);


  ofstream of("test_data/test.brain",ios::binary);
  of||b3;
  of.close();

  brain b4;
  ifstream ifs("test_data/test.brain",ios::binary);
  ifs||b4;
  ifs.close();

  assert(b3.m_samples.size()==b4.m_samples.size());
  assert(b3.m_blocks.size()==b4.m_blocks.size());

  assert(b4.search(b2.m_blocks[0],p)==0);
  //assert(b4.search(b2.m_blocks[9],p)==9);
  //assert(b4.search(b2.m_blocks[19],p)==19);
  //assert(b4.search(b2.m_blocks[29],p)==29);


  //cerr<<"!!!"<<endl;

  //    sample r = b2.resynth(b,1);
  //    assert(r.get_length()==200);

  return true;
}
