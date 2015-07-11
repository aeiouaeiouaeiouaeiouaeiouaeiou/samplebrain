#include <QtGui>
#include <iostream>

#include "MainWindow.h"

using namespace spiralcore;
using namespace std;

MainWindow::MainWindow()
{
    m_Ui.setupUi(this);
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::init_brain() {
    cerr<<"starting"<<endl;
//    m_source.load_sound("../sound/source/shostakovich6.wav");
    m_source.load_sound("../../sound/source/808.wav");
    m_source.load_sound("../../sound/source/joey.wav");
    m_source.load_sound("../../sound/source/pw2.wav");
    m_source.load_sound("../../sound/source/pw3.wav");
    m_source.load_sound("../../sound/source/claps.wav");
    m_source.load_sound("../../sound/source/eagle.wav");
//    m_source.load_sound("../sound/source/sailingbybit.wav");


    //target.load_sound("../sound/source/sb-left.wav");
    m_target.load_sound("../../sound/source/apache.wav");
    cerr<<"loaded sounds"<<endl;
    cerr<<endl;
    u32 len=3000;
    m_source.init(len,len-len,50);
    m_target.init(len,len-len/8,50);
    cerr<<"ready..."<<endl;
    cerr<<"we have "<<m_source.get_num_blocks()<<" brain blocks ("<<m_source.get_num_blocks()*len/44100.0<<" secs)"<<endl<<endl;


    //target.resynth_listen("shosta-dream-0.5.wav",source,0.5,a);

    m_renderer = new renderer(m_source,m_target);

}
