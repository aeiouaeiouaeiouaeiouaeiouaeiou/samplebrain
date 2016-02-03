// Copyright (C) 2015 Dave Griffiths
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

#include <QtGui>
#include <iostream>
#include <list>

#include "MainWindow.h"
#include "feedback.h"
#include "renderer.h"

using namespace std;

MainWindow::MainWindow() :
    m_last_file("."),
    m_feedback("8890")
{
    m_Ui.setupUi(this);
    setUnifiedTitleAndToolBarOnMac(true);

    m_audio_address = lo_address_new_from_url("osc.udp://localhost:8888");
    m_process_address = lo_address_new_from_url("osc.udp://localhost:8889");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_status()));
    timer->start(1000);
    timer->setInterval(500);

    m_save_wav="";
    m_record_id=0;
}

void MainWindow::init_from_session(const string &filename) {
  // pull the bits out of the file to set the interface...
  // is this easier than direct access? no idea??
  ifstream ifs(filename.c_str(),ios::binary);

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
  ifs||target_windowsize||target_overlap;
  ifs||source_windowsize||source_overlap;
  ifs||target_window||source_window;
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

  switch(r.get_search_algo()) {
  case renderer::BASIC: m_Ui.radioButtonAlgoBasic->setChecked(true); break;
  case renderer::REV_BASIC: m_Ui.radioButtonAlgoRevBasic->setChecked(true); break;
  case renderer::SYNAPTIC: m_Ui.radioButtonSynaptic->setChecked(true); break;
  case renderer::SYNAPTIC_SLIDE: m_Ui.radioButtonSynapticSlide->setChecked(true); break;
  };

  m_Ui.sliderSynapses->setValue(p->m_num_synapses);
  m_Ui.spinBoxSynapses->setValue(p->m_num_synapses);
  m_Ui.sliderSlideError->setValue(r.get_slide_error());
  m_Ui.spinBoxSlideError->setValue(r.get_slide_error());

  // target
  m_Ui.spinBoxBlockSizeTarget->setValue(t.get_block_size());
  m_Ui.doubleSpinBoxBlockOverlapTarget->setValue(t.get_overlap()/(float)t.get_block_size());

  m_Ui.radioButton_dodgyTarget->setChecked(false);
  m_Ui.radioButton_bartlettTarget->setChecked(false);
  m_Ui.radioButton_blackmanTarget->setChecked(false);
  m_Ui.radioButton_flattopTarget->setChecked(false);
  m_Ui.radioButton_gaussianTarget->setChecked(false);
  m_Ui.radioButton_hammingTarget->setChecked(false);
  m_Ui.radioButton_hannTarget->setChecked(false);
  m_Ui.radioButton_rectangleTarget->setChecked(false);

  switch(target_window) {
  case window::DODGY: m_Ui.radioButton_dodgyTarget->setChecked(true); break;
  case window::BARTLETT: m_Ui.radioButton_bartlettTarget->setChecked(true); break;
  case window::BLACKMAN: m_Ui.radioButton_blackmanTarget->setChecked(true); break;
  case window::FLAT_TOP: m_Ui.radioButton_flattopTarget->setChecked(true); break;
  case window::GAUSSIAN: m_Ui.radioButton_gaussianTarget->setChecked(true); break;
  case window::HAMMING: m_Ui.radioButton_hammingTarget->setChecked(true); break;
  case window::HANN: m_Ui.radioButton_hannTarget->setChecked(true); break;
  case window::RECTANGLE:  m_Ui.radioButton_rectangleTarget->setChecked(true); break;
  };

  // source
  m_Ui.spinBoxBlockSize->setValue(s.get_block_size());
  m_Ui.doubleSpinBoxBlockOverlap->setValue(s.get_overlap()/(float)s.get_block_size());
  switch(source_window) {
  case window::DODGY: m_Ui.radioButton_dodgy->setChecked(true); break;
  case window::BARTLETT: m_Ui.radioButton_bartlett->setChecked(true); break;
  case window::BLACKMAN: m_Ui.radioButton_blackman->setChecked(true); break;
  case window::FLAT_TOP: m_Ui.radioButton_flattop->setChecked(true); break;
  case window::GAUSSIAN: m_Ui.radioButton_gaussian->setChecked(true); break;
  case window::HAMMING: m_Ui.radioButton_hamming->setChecked(true); break;
  case window::HANN: m_Ui.radioButton_hann->setChecked(true); break;
  case window::RECTANGLE:  m_Ui.radioButton_rectagle->setChecked(true); break;
  };

  // brain samples
  m_Ui.listWidgetSounds->clear();
  const std::list<brain::sound> samples = s.get_samples();
  for (std::list<brain::sound>::const_iterator i=samples.begin();
       i!=samples.end(); ++i) {
    m_Ui.listWidgetSounds->addItem(QString::fromStdString(i->m_filename));
  }

  // mix
  m_Ui.sliderTargetMix->setValue(r.get_target_mix()*100);
  m_Ui.doubleSpinBoxTargetMix->setValue(r.get_target_mix());
  m_Ui.sliderNMix->setValue(r.get_n_mix()*100);
  m_Ui.doubleSpinBoxNMix->setValue(r.get_n_mix());
  m_Ui.sliderAutotune->setValue(r.get_autotune()*100);
  m_Ui.doubleSpinBoxAutotune->setValue(r.get_autotune());



}
