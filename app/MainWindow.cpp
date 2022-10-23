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

#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QtGui>
#include <iostream>
#include <list>

#include "MainWindow.h"
#include "feedback.h"
#include "renderer.h"

using namespace std;

MainWindow::MainWindow(const string &port, const string &audio_port, const string &process_port, QSettings *settings) :
    m_last_sound_file("."),
    m_last_target_file("."),
    m_last_brain_file("."),
    m_last_session_file("."),
    m_last_recording_file("."),
    m_feedback(port),
    m_audio_port(audio_port),
    m_process_port(process_port),
    m_format_string("Microsoft WAV (*.wav);;SGI/Apple AIFF (*.aiff);;SGI/Apple AIFC (*.aifc);;Sun/DEC/NeXT AU (*.au);;Sun/DEC/NeXT SND (*.snd);;Fasttracker 2 XI (*.xi);;Free Lossless Audio Codec FLAC (*.flac);;All files (*.*)")
{
  m_sound_item_enable_mapper = new QSignalMapper(this);
  m_sound_item_delete_mapper = new QSignalMapper(this);

  connect(m_sound_item_enable_mapper,
          SIGNAL(mapped(int)), this, SLOT(sound_enable(int)));
  connect(m_sound_item_delete_mapper,
          SIGNAL(mapped(int)), this, SLOT(delete_sound(int)));

  m_Ui.setupUi(this);
  setUnifiedTitleAndToolBarOnMac(true);

  m_Ui.verticalLayout_5->setSpacing(0);
  m_Ui.verticalLayout_5->setContentsMargins(0,0,0,0);
  
  m_Ui.brain_contents->setAlignment(Qt::AlignTop);
  m_Ui.brain_contents->setSpacing(0);
  m_Ui.brain_contents->setContentsMargins(0,0,0,0);

  m_settings_dialog = new SettingsDialog(this,settings);

    // add default local dest
    // turn on first one

  QSignalMapper* enable_mapper = new QSignalMapper(this);

    for (int i=0; i<10; i++) {
      osc_destination d;
      d.m_id=i;
      d.m_audio_address = lo_address_new_from_url(string("osc.udp://localhost:"+m_audio_port).c_str());
      d.m_process_address = lo_address_new_from_url(string("osc.udp://localhost:"+m_process_port).c_str());
      if (i==0) d.m_enabled=true;
      else d.m_enabled=false;
      add_gui_address(d,enable_mapper);

      if (i==0) {
        d.m_enable->setChecked(true);
        d.m_address->setText("osc.udp://localhost");
      }
      m_destinations.push_back(d);
    }

    connect(enable_mapper, SIGNAL(mapped(int)), this, SLOT(net_enable(int)));

    m_Ui.netContainer->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_status()));
    timer->start(1000);
    timer->setInterval(500);

    m_save_wav="";
    m_record_id=0;
}

void MainWindow::add_gui_address(osc_destination &dest,
                                 QSignalMapper* enable_mapper) {
  QHBoxLayout *h = new QHBoxLayout();
  dest.m_enable = new QCheckBox();
  dest.m_enable->setText("enable");
  dest.m_enable->setChecked(false);
  h->addWidget(dest.m_enable);
  dest.m_address = new QLineEdit();
  h->addWidget(dest.m_address);
  m_Ui.netContainer->addLayout(h);

  QObject::connect(dest.m_enable, SIGNAL(clicked()), enable_mapper, SLOT(map()));
  enable_mapper->setMapping(dest.m_enable, dest.m_id);
}

void MainWindow::init_from_session(const string &filename) {
  // pull the bits out of the file to set the interface...
  // is this easier than direct access? no idea??
  ifstream ifs(filename.c_str(),ios::binary);
  if (!ifs) return;
  
  brain s,t;
  u32 version=0;
  ifs||version;
  renderer r(s,t);
  ifs||r;
  ifs||r;

  u32 target_windowsize;
  u32 source_windowsize;
  window::type target_window;
  window::type source_window;
  float target_overlap;
  float source_overlap;
  int t_int;
  // skip this...
  ifs||source_windowsize||source_overlap;
  ifs||target_windowsize||target_overlap;
  ifs||source_window||target_window;
  // todo: probably don't need to load all the sample data too :/
  ifs||s;
  ifs||t;

  // brain tweaks
  search_params * p = r.get_params();

  m_Ui.sliderRatio->setValue(p->m_ratio*100);
  m_Ui.doubleSpinBoxRatio->setValue(p->m_ratio);
  m_Ui.sliderNRatio->setValue(p->m_n_ratio*100);
  m_Ui.doubleSpinBoxNRatio->setValue(p->m_n_ratio);
  m_Ui.spinBoxFFT1Start->setValue(p->m_fft1_start);
  m_Ui.spinBoxFFT1End->setValue(p->m_fft1_end);
  m_Ui.sliderNovelty->setValue(p->m_usage_importance*100);
  m_Ui.doubleSpinBoxNovelty->setValue(p->m_usage_importance);
  m_Ui.sliderBoredom->setValue(s.get_usage_falloff()*100);
  m_Ui.doubleSpinBoxBoredom->setValue(s.get_usage_falloff());
  m_Ui.sliderStickyness->setValue(p->m_stickyness*100);
  m_Ui.doubleSpinBoxStickyness->setValue(p->m_stickyness);
  m_Ui.sliderSearchStretch->setValue(r.get_stretch());
  m_Ui.spinBoxSearchStretch->setValue(r.get_stretch());

  m_Ui.comboBoxAlgorithm->setCurrentIndex(r.get_search_algo());

  m_Ui.sliderSynapses->setValue(p->m_num_synapses);
  m_Ui.spinBoxSynapses->setValue(p->m_num_synapses);
  m_Ui.sliderSlideError->setValue(r.get_slide_error());
  m_Ui.spinBoxSlideError->setValue(r.get_slide_error());

  // target
  m_Ui.spinBoxBlockSizeTarget->setValue(t.get_block_size());
  m_Ui.doubleSpinBoxBlockOverlapTarget->setValue(t.get_overlap()/(float)t.get_block_size());

  m_Ui.comboBoxTargetShape->setCurrentIndex(target_window);

  // source
  m_Ui.spinBoxBlockSize->setValue(s.get_block_size());
  m_Ui.doubleSpinBoxBlockOverlap->setValue(s.get_overlap()/(float)s.get_block_size());
  m_Ui.comboBoxBrainShape->setCurrentIndex(source_window);

  // brain samples
  m_sound_items.clear();
  for (auto &i:s.get_samples()) {
    sound_items::sound_item &si = m_sound_items.add(m_Ui.brain_contents,i.m_filename,i.m_enabled);

    QObject::connect(si.m_enable, SIGNAL(clicked()), m_sound_item_enable_mapper, SLOT(map()));
    m_sound_item_enable_mapper->setMapping(si.m_enable, si.m_id);
    QObject::connect(si.m_del, SIGNAL(clicked()), m_sound_item_delete_mapper, SLOT(map()));
    m_sound_item_delete_mapper->setMapping(si.m_del, si.m_id);
  }
  // todo: might contain unprocessed samples in colour scheme
  m_sound_items.recolour();

  // mix
  m_Ui.sliderTargetMix->setValue(r.get_target_mix()*100);
  m_Ui.doubleSpinBoxTargetMix->setValue(r.get_target_mix());
  m_Ui.sliderNMix->setValue(r.get_n_mix()*100);
  m_Ui.doubleSpinBoxNMix->setValue(r.get_n_mix());
  m_Ui.sliderAutotune->setValue(r.get_autotune()*100);
  m_Ui.doubleSpinBoxAutotune->setValue(r.get_autotune());



}

#endif
