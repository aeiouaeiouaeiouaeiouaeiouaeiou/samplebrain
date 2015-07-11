#include <QtGui>
#include "generated/ui_samplebrain.h"

#include "brain.h"
#include "renderer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void init_brain();

    spiralcore::brain m_source, m_target;
    spiralcore::renderer *m_renderer;

protected:

private slots:

    void play_slot() {}
    void stop_slot() {}
    void ratio_slot(int s) { m_renderer->set_ratio(s/100.0f); }
    void ratio_slot(double) {}
    void fft1_start_slot(int) {}
    void fft1_end_slot(int) {}
    void fft2_start_slot(int) {}
    void fft2_end_slot(int) {}
    void volume_slot(int) {}
    void run_slot() {}
    void load_target() {}
    void target_block_size(int) {}
    void target_block_overlap(int) {}
    void generate_target_blocks() {}
    void block_size(int) {}
    void block_overlap(int) {}
    void fft_spectrum_size(int) {}
    void generate() {}
    void load_sound() {}

private:
    Ui_MainWindow m_Ui;

};
