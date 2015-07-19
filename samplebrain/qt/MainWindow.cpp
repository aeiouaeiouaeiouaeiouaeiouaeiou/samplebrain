#include <QtGui>
#include <iostream>

#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow()
{
    m_Ui.setupUi(this);
    setUnifiedTitleAndToolBarOnMac(true);

    m_audio_address = lo_address_new_from_url("osc.udp://localhost:8888");
    m_process_address = lo_address_new_from_url("osc.udp://localhost:8889");
    m_save_wav="";
    m_record_id=0;
}
