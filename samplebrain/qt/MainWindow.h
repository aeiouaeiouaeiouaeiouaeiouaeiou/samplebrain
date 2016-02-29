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

#include <QtGui>
#include <QDirIterator>
#include "generated/ui_samplebrain.h"

#include <iostream>
#include <lo/lo.h>
#include <string>
#include <list>
#include "window.h"
#include "feedback.h"
#include "sound_items.h"

using namespace std;
using namespace spiralcore;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();


protected:

private slots:

    void play_slot() { send_audio_osc("/start",""); }
    void stop_slot() { send_audio_osc("/pause",""); }

    void ratio_slot(int s) {
      send_audio_osc("/ratio","f",s/100.0f);
      m_Ui.doubleSpinBoxRatio->setValue(s/100.0f);
    }
    void ratio_slot(double s) {
        send_audio_osc("/ratio","f",s);
        m_Ui.sliderRatio->setValue(s*100);
    }

    void n_ratio_slot(int s) {
        send_audio_osc("/n_ratio","f",s/100.0f);
        m_Ui.doubleSpinBoxNRatio->setValue(s/100.0f);
    }
    void n_ratio_slot(double s) {
        send_audio_osc("/n_ratio","f",s);
        m_Ui.sliderNRatio->setValue(s*100);
    }

    void autotune(int s) {
        send_audio_osc("/autotune","f",s/100.0f);
        m_Ui.doubleSpinBoxAutotune->setValue(s/100.0f);
    }
    void autotune(double s) {
        send_audio_osc("/autotune","f",s);
        m_Ui.sliderAutotune->setValue(s*100);
    }

    void fft1_start_slot(int s) { send_audio_osc("/fft1_start","i",s); }
    void fft1_end_slot(int s) { send_audio_osc("/fft1_end","i",s); }
    void fft2_start_slot(int s){} // { m_renderer->get_params()->m_fft2_start=s; }
    void fft2_end_slot(int s){} // { m_renderer->get_params()->m_fft2_end=s; }

    void n_mix_slot(int s) {
        send_audio_osc("/n_mix","f",s/100.0f);
        m_Ui.doubleSpinBoxNMix->setValue(s/100.0f);
    }
    void n_mix_slot(double s) {
        send_audio_osc("/n_mix","f",s);
        m_Ui.sliderNMix->setValue(s*100);
    }

    void novelty_slot(int s) {
        send_audio_osc("/novelty","f",s/100.0f);
        m_Ui.doubleSpinBoxNovelty->setValue(s/100.0f);
    }
    void novelty_slot(double s) {
        send_audio_osc("/novelty","f",s);
        m_Ui.sliderNovelty->setValue(s*100);
    }

    void boredom_slot(int s) {
        float v=s/100.0f;
        send_audio_osc("/boredom","f",v);
        m_Ui.doubleSpinBoxBoredom->setValue(v);
    }
    void boredom_slot(double s) {
        send_audio_osc("/boredom","f",s);
        m_Ui.sliderBoredom->setValue(s*100);
    }
    void synapses(int s) {
        send_audio_osc("/synapses","i",s);
    }
    void target_mix_slot(int s) {
        send_audio_osc("/target_mix","f",s/100.0f);
        m_Ui.doubleSpinBoxTargetMix->setValue(s/100.0f);
    }
    void target_mix_slot(double s) {
        send_audio_osc("/target_mix","f",s);
        m_Ui.sliderTargetMix->setValue(s*100);
    }
    void search_stretch(int s) {
        send_audio_osc("/search-stretch","i",s);
    }
    void slide_error(int s) {
        send_audio_osc("/slide-error","i",s);
    }
    void stickyness_slot(int s) {
        send_audio_osc("/stickyness","f",s/100.0f);
        m_Ui.doubleSpinBoxStickyness->setValue(s/100.0f);
    }
    void stickyness_slot(double s) {
        send_audio_osc("/stickyness","f",s);
        m_Ui.sliderStickyness->setValue(s*100);
    }

    void volume_slot(int s) { send_audio_osc("/volume","f",s/100.0f); }
    void algo(int n) {  send_audio_osc("/search_algo","i",n); }

    void run_slot() {}
    void load_target() {
        m_last_file=QFileDialog::getOpenFileName(
            this,
            QString("Select an wav file"),
            m_last_file,
            QString("Sounds (*.wav)"));

        send_process_osc("/load_target","s",m_last_file.toStdString().c_str());
    }
    void target_block_size(int s) { send_process_osc("/target_block_size","i",s); }
    void target_block_overlap(double s) { send_process_osc("/target_overlap","f",s); }
    void generate_target_blocks() {  send_process_osc("/generate_target",""); }
    void block_size(int s) { send_process_osc("/source_block_size","i",s); }
    void block_overlap(double s) { send_process_osc("/source_overlap","f",s); }
    void fft_spectrum_size(int) {}
    void generate() { send_process_osc("/generate_brain",""); }
    void load_sound() {
        m_last_file=QFileDialog::getOpenFileName(
            this,
            QString("Select a wav file"),
            m_last_file,
            QString("Sounds (*.wav)"));

        send_process_osc("/load_sample","s",m_last_file.toStdString().c_str());

        sound_items::sound_item &si = m_sound_items.add(m_Ui.brain_contents, m_last_file.toStdString(),true);

        QObject::connect(si.m_enable, SIGNAL(clicked()), m_sound_item_enable_mapper, SLOT(map()));
        m_sound_item_enable_mapper->setMapping(si.m_enable, si.m_id);
        QObject::connect(si.m_del, SIGNAL(clicked()), m_sound_item_delete_mapper, SLOT(map()));
        m_sound_item_delete_mapper->setMapping(si.m_del, si.m_id);
    }


   void load_sounds() {
     m_last_file=QFileDialog::getExistingDirectory(this,
                                                   QString("Select a directory"),
                                                   m_last_file);


     QDirIterator dirIt(m_last_file,QDirIterator::Subdirectories);
     while (dirIt.hasNext()) {
       dirIt.next();
       if (QFileInfo(dirIt.filePath()).isFile() &&
           QFileInfo(dirIt.filePath()).suffix() == "wav") {
         send_process_osc("/load_sample","s",dirIt.filePath().toStdString().c_str());

         sound_items::sound_item &si = m_sound_items.add(m_Ui.brain_contents, dirIt.filePath().toStdString(),true);

         QObject::connect(si.m_enable, SIGNAL(clicked()), m_sound_item_enable_mapper, SLOT(map()));
         m_sound_item_enable_mapper->setMapping(si.m_enable, si.m_id);
         QObject::connect(si.m_del, SIGNAL(clicked()), m_sound_item_delete_mapper, SLOT(map()));
         m_sound_item_delete_mapper->setMapping(si.m_del, si.m_id);

       }
     }
   }

   void select_all() {
     for (auto &si:m_sound_items.m_sound_items) {
       si.m_enable->setChecked(true);
       send_process_osc("/activate_sound","s",si.m_filename.c_str());
     }
   }

   void select_none() {
     for (auto &si:m_sound_items.m_sound_items) {
       si.m_enable->setChecked(false);
       send_process_osc("/deactivate_sound","s",si.m_filename.c_str());
     }
   }

    void sound_enable(int id) {
      // search for this id...
      for (auto &si:m_sound_items.m_sound_items) {
        if (si.m_id==id) {
          if (si.m_enable->isChecked()) {
            send_process_osc("/activate_sound","s",si.m_filename.c_str());
          } else {
            send_process_osc("/deactivate_sound","s",si.m_filename.c_str());
          }
        }
      }
    }

    void delete_sound(int id) {
      // search for this id...
      for (auto &si:m_sound_items.m_sound_items) {
        if (si.m_id==id) {
          send_process_osc("/delete_sample","s",si.m_filename.c_str());
          m_sound_items.remove(si.m_filename);
          // iterator is now invalidated...
          return;
        }
      }
    }
    void clear_brain() {
      for (auto &si:m_sound_items.m_sound_items) {
        send_process_osc("/delete_sample","s",si.m_filename.c_str());
      }
      m_sound_items.clear();
    }
    void restart_audio() { send_audio_osc("/restart_audio",""); }

    void brain_shape(int n) { send_process_osc("/window_type","i",n); }
    void target_shape(int n) { send_process_osc("/target_window_type","i",n); }

    void record() {
        if (m_save_wav=="") {
            m_last_file=QFileDialog::getSaveFileName(
                this,
                QString("Select a wav file"),
                m_last_file,
                QString("Sounds (*.wav)"));
            m_save_wav = m_last_file.toStdString();
            // chop off .wav
            size_t pos = m_save_wav.find_last_of(".");
            if (pos!=string::npos) {
                m_save_wav = m_save_wav.substr(0,pos);
            }

        }

        char fn[1024];
        snprintf(fn,1024,"%s-%i",m_save_wav.c_str(),m_record_id);
        send_audio_osc("/record","s",fn);
        cerr<<fn<<endl;
        m_record_id++;
    }

    void stop_record() {
        send_audio_osc("/stop","");
    }

    void load_brain() {
        m_last_file=QFileDialog::getOpenFileName(
            this,
            QString("Select a brain file"),
            m_last_file,
            QString("Brains (*.brain)"));

        send_process_osc("/load_brain","s",m_last_file.toStdString().c_str());
    }
    void save_brain() {
        m_last_file=QFileDialog::getSaveFileName(
            this,
            QString("Select a brain file"),
            m_last_file,
            QString("Brains (*.brain)"));

        send_process_osc("/save_brain","s",m_last_file.toStdString().c_str());
    }

    void load_session() {
        m_last_file=QFileDialog::getOpenFileName(
            this,
            QString("Select a session file"),
            m_last_file,
            QString("Sessions *.samplebrain (*.samplebrain)"));

        send_process_osc("/load_session","s",m_last_file.toStdString().c_str());
        init_from_session(m_last_file.toStdString());
    }

    void save_session() {
        m_last_file=QFileDialog::getSaveFileName(
            this,
            QString("Select a session file"),
            m_last_file,
            QString("Sessions *.samplebrain (*.samplebrain)"));

        send_process_osc("/save_session","s",m_last_file.toStdString().c_str());
    }

    void update_status() {
      m_feedback.poll(m_Ui.statusbar,&m_sound_items);
    }

    void stereo_mode(bool s) {
      send_audio_osc("/stereo","i",s);
    }

    void net_enable(int id) {
      osc_destination &d = m_destinations[id];

      if (d.m_enable->isChecked()) {
        // reconnect
        string url = d.m_address->text().toUtf8().constData();
        lo_address_free(d.m_audio_address);
        lo_address_free(d.m_process_address);
        d.m_audio_address = lo_address_new_from_url(string(url+":8888").c_str());
        d.m_process_address = lo_address_new_from_url(string(url+":8889").c_str());
        // start sending messages here
        d.m_enabled=true;
      } else {
        // stop sending messages here
        d.m_enabled=false;
      }

    }


private:

    ///////////////////////////////////////////////

    // we want to be able to send out to
    // multiple addresses over the network

    ////////////////////////////////////////////////


    // we want to be able to send out to
    // multiple addresses over the network
    class osc_destination {
    public:
      int m_id;
      lo_address m_audio_address;
      lo_address m_process_address;
      // can't find a way to address these via qt
      QLineEdit *m_address;
      QCheckBox *m_enable;
      bool m_enabled;
    };

    vector<osc_destination> m_destinations;

    // all this to work around liblo's use of varargs...
    void send_audio_osc(const char *name, const char *types) {
      for (auto dest:m_destinations) {
        if (dest.m_enabled) {
          lo_send(dest.m_audio_address,name,types);
        }
      }
    }

    template <class T>
    void send_audio_osc(const char *name, const char *types, T val) {
      for (auto dest:m_destinations) {
        if (dest.m_enabled) {
          lo_send(dest.m_audio_address,name,types,val);
        }
      }
    }

    void send_process_osc(const char *name, const char *types) {
      for (auto dest:m_destinations) {
        if (dest.m_enabled) {
          lo_send(dest.m_process_address,name,types);
        }
      }
    }

    template <class T>
    void send_process_osc(const char *name, const char *types, T val) {
      for (auto dest:m_destinations) {
        if (dest.m_enabled) {
          lo_send(dest.m_process_address,name,types,val);
        }
      }
    }


    void init_from_session(const string &filename);
    void add_gui_address(osc_destination &dest,
                         QSignalMapper* enable_mapper);

    string m_save_wav;
    QString m_last_file;
    u32 m_record_id;
    Ui_MainWindow m_Ui;
    feedback m_feedback;
    QSignalMapper* m_sound_item_enable_mapper;
    QSignalMapper* m_sound_item_delete_mapper;
    sound_items m_sound_items;


};
