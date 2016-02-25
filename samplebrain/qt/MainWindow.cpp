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

    m_sound_item_enable_mapper = new QSignalMapper(this);
    m_Ui.brain_contents->setAlignment(Qt::AlignTop);
    m_Ui.brain_contents->setSpacing(0);
    m_Ui.brain_contents->setMargin(0);
    m_Ui.brain_contents->setContentsMargins(0,0,0,0);
    connect(m_sound_item_enable_mapper,
            SIGNAL(mapped(int)), this, SLOT(sound_enable(int)));
    m_current_sound_id=0;

    // add default local dest
    // turn on first one

    QSignalMapper* enable_mapper = new QSignalMapper(this);
    QSignalMapper* connect_mapper = new QSignalMapper(this);

    for (int i=0; i<10; i++) {
      osc_destination d;
      d.m_id=i;
      d.m_audio_address = lo_address_new_from_url("osc.udp://localhost:8888");
      d.m_process_address = lo_address_new_from_url("osc.udp://localhost:8889");
      if (i==0) d.m_enabled=true;
      else d.m_enabled=false;
      add_gui_address(d,enable_mapper,connect_mapper);

      if (i==0) {
        d.m_enable->setChecked(true);
        d.m_address->setText("osc.udp://localhost");
      }
      m_destinations.push_back(d);
    }

    connect(enable_mapper, SIGNAL(mapped(int)), this, SLOT(net_enable(int)));
    connect(connect_mapper, SIGNAL(mapped(int)), this, SLOT(net_connect(int)));

    m_Ui.netContainer->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_status()));
    timer->start(1000);
    timer->setInterval(500);

    m_save_wav="";
    m_record_id=0;
}

void MainWindow::add_gui_address(osc_destination &dest,
                                 QSignalMapper* enable_mapper,
                                 QSignalMapper* connect_mapper) {
  QHBoxLayout *h = new QHBoxLayout();
  dest.m_enable = new QCheckBox();
  dest.m_enable->setText("enable");
  dest.m_enable->setChecked(false);
  h->addWidget(dest.m_enable);
  dest.m_address = new QLineEdit();
  h->addWidget(dest.m_address);
  //QPushButton *ping = new QPushButton();
  //ping->setText("connect");
  //h->addWidget(ping);
  m_Ui.netContainer->addLayout(h);

  QObject::connect(dest.m_enable, SIGNAL(clicked()), enable_mapper, SLOT(map()));
  enable_mapper->setMapping(dest.m_enable, dest.m_id);
  //QObject::connect(ping, SIGNAL(clicked()), connect_mapper, SLOT(map()));
  //connect_mapper->setMapping(ping, dest.m_id);
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
  //  m_Ui.listWidgetSounds->clear();
  const std::list<brain::sound> samples = s.get_samples();
  for (std::list<brain::sound>::const_iterator i=samples.begin();
       i!=samples.end(); ++i) {
        add_sound_item(i->m_filename);
  }


  // mix
  m_Ui.sliderTargetMix->setValue(r.get_target_mix()*100);
  m_Ui.doubleSpinBoxTargetMix->setValue(r.get_target_mix());
  m_Ui.sliderNMix->setValue(r.get_n_mix()*100);
  m_Ui.doubleSpinBoxNMix->setValue(r.get_n_mix());
  m_Ui.sliderAutotune->setValue(r.get_autotune()*100);
  m_Ui.doubleSpinBoxAutotune->setValue(r.get_autotune());



}


void MainWindow::add_sound_item(const string &name) {
  sound_item si;
  si.m_filename = name;
  si.m_id = m_current_sound_id++;
  QString style("background-color:lightblue;");
  if (m_sound_items.size()%2==0) style="background-color:pink;";

  si.m_container = new QHBoxLayout();
  si.m_enable = new QCheckBox();
  si.m_enable->setChecked(true);
  si.m_enable->setStyleSheet(style);
  si.m_container->addWidget(si.m_enable);
  QLabel *l = new QLabel();


  QFileInfo fi(QString::fromStdString(name));
  l->setText(fi.fileName());
  l->setStyleSheet(style);
  si.m_container->addWidget(l);

  QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  //spacer->setStyleSheet(style);
  si.m_container->addItem(spacer);

  QPushButton *del = new QPushButton();
  del->setText("x");
  del->setMaximumWidth(20);
  del->setMaximumHeight(20);
  si.m_container->addWidget(del);

  m_Ui.brain_contents->addLayout(si.m_container);

  QObject::connect(si.m_enable, SIGNAL(clicked()), m_sound_item_enable_mapper, SLOT(map()));
  m_sound_item_enable_mapper->setMapping(si.m_enable, si.m_id);

  m_sound_items.push_back(si);
}

void MainWindow::clear_sound_items() {
  for (auto si:m_sound_items) {
    delete si.m_container;
  }
  m_sound_items.clear();
}


void MainWindow::delete_sound_item(const string &name) {
}
