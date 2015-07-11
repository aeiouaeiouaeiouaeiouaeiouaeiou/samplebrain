#include <QtGui>
#include "generated/ui_samplebrain.h"

#include <iostream>
#include <lo/lo.h>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();



protected:

private slots:

    void play_slot() { lo_send(m_audio_address,"/start",""); }
    void stop_slot() { lo_send(m_audio_address,"/stop",""); }
    void ratio_slot(int s) { lo_send(m_audio_address,"/ratio","f",s/100.0f); }
    void ratio_slot(double s) { lo_send(m_audio_address,"/ratio","f",s); }
    void fft1_start_slot(int s) { lo_send(m_audio_address,"/fft1_start","i",s); }
    void fft1_end_slot(int s) { lo_send(m_audio_address,"/fft1_end","i",s); }
    void fft2_start_slot(int s){} // { m_renderer->get_params()->m_fft2_start=s; }
    void fft2_end_slot(int s){} // { m_renderer->get_params()->m_fft2_end=s; }
    void volume_slot(int s){} // {  m_renderer->set_volume(s/50.0f); }
    void run_slot() {}
    void load_target() {
        QString s=QFileDialog::getOpenFileName(
            this,
            QString("Select an wav file"),
            ".",
            QString("Sounds (*.wav)"));

        lo_send(m_process_address,"/load_target","s",s.toStdString().c_str());
    }
    void target_block_size(int s) { lo_send(m_process_address,"/target_block_size","i",s); }
    void target_block_overlap(double s) { lo_send(m_process_address,"/target_overlap","f",s); }
    void generate_target_blocks() {  lo_send(m_process_address,"/generate_target",""); }
    void block_size(int s) { lo_send(m_process_address,"/source_block_size","i",s); }
    void block_overlap(double s) { lo_send(m_process_address,"/source_overlap","f",s); }
    void fft_spectrum_size(int) {}
    void generate() { lo_send(m_process_address,"/generate_brain",""); }
    void load_sound() {
        QString s=QFileDialog::getOpenFileName(
            this,
            QString("Select an wav file"),
            ".",
            QString("Sounds (*.wav)"));

        lo_send(m_process_address,"/load_sample","s",s.toStdString().c_str());

        m_Ui.listWidgetSounds->addItem(s);
    }
    void delete_sound() {
        QList<QListWidgetItem *> itemList = m_Ui.listWidgetSounds->selectedItems();
        for (int i=0; i<itemList.size(); i++) {
            lo_send(m_process_address,"/delete_sample","s",itemList[i]->text().toStdString().c_str());
        }
        qDeleteAll(m_Ui.listWidgetSounds->selectedItems());
    }
    void clear_brain() {
        for (int i=0; i<m_Ui.listWidgetSounds->count(); i++) {
            lo_send(m_process_address,"/delete_sample","s",m_Ui.listWidgetSounds->item(i)->text().toStdString().c_str());
        }
        m_Ui.listWidgetSounds->clear();
    }
    void restart_audio() { lo_send(m_audio_address,"/restart_audio",""); }

private:
    Ui_MainWindow m_Ui;
    lo_address m_audio_address;
    lo_address m_process_address;
};
