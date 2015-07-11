/********************************************************************************
** Form generated from reading UI file 'samplebrainYv5241.ui'
**
** Created: Sat Jul 11 10:34:17 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SAMPLEBRAINYV5241_H
#define SAMPLEBRAINYV5241_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDial>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *controlTab;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonStop;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QDial *dialRatio;
    QDoubleSpinBox *doubleSpinBoxRatio;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QSpinBox *spinBoxFFT1Start;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_10;
    QSpinBox *spinBoxFFT1End;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QSpinBox *spinBoxFFT2Start;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_12;
    QSpinBox *spinBoxFFT2End;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_13;
    QSlider *verticalSliderVolume;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_16;
    QLabel *label_15;
    QPushButton *pushButtonLoadTarget;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_17;
    QSpinBox *spinBoxBlockSizeTarget;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_18;
    QSpinBox *spinBoxBlockOverlapTarget;
    QPushButton *pushButtonGenerateTarget;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_14;
    QTextEdit *textEdit;
    QPushButton *pushButtonRun;
    QWidget *sampleTab;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpinBox *spinBoxBlockSize;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QSpinBox *spinBoxBlockOverlap;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpinBox *spinBoxSpectSize;
    QPushButton *pushButtonGenerate;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButtonLosdBrain;
    QPushButton *pushButtonSaveBrain;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QListWidget *listWidgetSounds;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonLoadSound;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 603);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        controlTab = new QWidget();
        controlTab->setObjectName(QString::fromUtf8("controlTab"));
        horizontalLayout_15 = new QHBoxLayout(controlTab);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_19 = new QLabel(controlTab);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        QFont font;
        font.setFamily(QString::fromUtf8("Comic Sans MS"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label_19->setFont(font);

        verticalLayout_7->addWidget(label_19);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        pushButtonPlay = new QPushButton(controlTab);
        pushButtonPlay->setObjectName(QString::fromUtf8("pushButtonPlay"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Comic Sans MS"));
        font1.setBold(true);
        font1.setWeight(75);
        pushButtonPlay->setFont(font1);
        pushButtonPlay->setFlat(false);

        horizontalLayout_12->addWidget(pushButtonPlay);

        pushButtonStop = new QPushButton(controlTab);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setFont(font1);

        horizontalLayout_12->addWidget(pushButtonStop);


        verticalLayout_7->addLayout(horizontalLayout_12);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_6 = new QLabel(controlTab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        verticalLayout_3->addWidget(label_6);

        dialRatio = new QDial(controlTab);
        dialRatio->setObjectName(QString::fromUtf8("dialRatio"));
        dialRatio->setEnabled(true);

        verticalLayout_3->addWidget(dialRatio);

        doubleSpinBoxRatio = new QDoubleSpinBox(controlTab);
        doubleSpinBoxRatio->setObjectName(QString::fromUtf8("doubleSpinBoxRatio"));

        verticalLayout_3->addWidget(doubleSpinBoxRatio);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_7 = new QLabel(controlTab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);

        verticalLayout_4->addWidget(label_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_9 = new QLabel(controlTab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font1);

        horizontalLayout_3->addWidget(label_9);

        spinBoxFFT1Start = new QSpinBox(controlTab);
        spinBoxFFT1Start->setObjectName(QString::fromUtf8("spinBoxFFT1Start"));

        horizontalLayout_3->addWidget(spinBoxFFT1Start);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_10 = new QLabel(controlTab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font1);

        horizontalLayout_9->addWidget(label_10);

        spinBoxFFT1End = new QSpinBox(controlTab);
        spinBoxFFT1End->setObjectName(QString::fromUtf8("spinBoxFFT1End"));

        horizontalLayout_9->addWidget(spinBoxFFT1End);


        verticalLayout_4->addLayout(horizontalLayout_9);


        verticalLayout_3->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_8 = new QLabel(controlTab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);

        verticalLayout_5->addWidget(label_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_11 = new QLabel(controlTab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font1);

        horizontalLayout_10->addWidget(label_11);

        spinBoxFFT2Start = new QSpinBox(controlTab);
        spinBoxFFT2Start->setObjectName(QString::fromUtf8("spinBoxFFT2Start"));

        horizontalLayout_10->addWidget(spinBoxFFT2Start);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_12 = new QLabel(controlTab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);

        horizontalLayout_11->addWidget(label_12);

        spinBoxFFT2End = new QSpinBox(controlTab);
        spinBoxFFT2End->setObjectName(QString::fromUtf8("spinBoxFFT2End"));

        horizontalLayout_11->addWidget(spinBoxFFT2End);


        verticalLayout_5->addLayout(horizontalLayout_11);


        verticalLayout_3->addLayout(verticalLayout_5);


        verticalLayout_7->addLayout(verticalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_13 = new QLabel(controlTab);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font1);

        verticalLayout_6->addWidget(label_13);

        verticalSliderVolume = new QSlider(controlTab);
        verticalSliderVolume->setObjectName(QString::fromUtf8("verticalSliderVolume"));
        verticalSliderVolume->setOrientation(Qt::Vertical);

        verticalLayout_6->addWidget(verticalSliderVolume);


        verticalLayout_7->addLayout(verticalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);


        horizontalLayout_15->addLayout(verticalLayout_7);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_16 = new QLabel(controlTab);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font);

        verticalLayout_9->addWidget(label_16);

        label_15 = new QLabel(controlTab);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font1);

        verticalLayout_9->addWidget(label_15);

        pushButtonLoadTarget = new QPushButton(controlTab);
        pushButtonLoadTarget->setObjectName(QString::fromUtf8("pushButtonLoadTarget"));
        pushButtonLoadTarget->setFont(font1);

        verticalLayout_9->addWidget(pushButtonLoadTarget);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_17 = new QLabel(controlTab);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font1);

        horizontalLayout_13->addWidget(label_17);

        spinBoxBlockSizeTarget = new QSpinBox(controlTab);
        spinBoxBlockSizeTarget->setObjectName(QString::fromUtf8("spinBoxBlockSizeTarget"));

        horizontalLayout_13->addWidget(spinBoxBlockSizeTarget);


        verticalLayout_9->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_18 = new QLabel(controlTab);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font1);

        horizontalLayout_14->addWidget(label_18);

        spinBoxBlockOverlapTarget = new QSpinBox(controlTab);
        spinBoxBlockOverlapTarget->setObjectName(QString::fromUtf8("spinBoxBlockOverlapTarget"));

        horizontalLayout_14->addWidget(spinBoxBlockOverlapTarget);


        verticalLayout_9->addLayout(horizontalLayout_14);

        pushButtonGenerateTarget = new QPushButton(controlTab);
        pushButtonGenerateTarget->setObjectName(QString::fromUtf8("pushButtonGenerateTarget"));
        pushButtonGenerateTarget->setFont(font1);

        verticalLayout_9->addWidget(pushButtonGenerateTarget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer);


        horizontalLayout_15->addLayout(verticalLayout_9);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_14 = new QLabel(controlTab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font);

        verticalLayout_8->addWidget(label_14);

        textEdit = new QTextEdit(controlTab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout_8->addWidget(textEdit);

        pushButtonRun = new QPushButton(controlTab);
        pushButtonRun->setObjectName(QString::fromUtf8("pushButtonRun"));
        pushButtonRun->setFont(font1);

        verticalLayout_8->addWidget(pushButtonRun);


        horizontalLayout_15->addLayout(verticalLayout_8);

        tabWidget->addTab(controlTab, QString());
        sampleTab = new QWidget();
        sampleTab->setObjectName(QString::fromUtf8("sampleTab"));
        horizontalLayout_8 = new QHBoxLayout(sampleTab);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_3 = new QLabel(sampleTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(sampleTab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        horizontalLayout_4->addWidget(label);

        spinBoxBlockSize = new QSpinBox(sampleTab);
        spinBoxBlockSize->setObjectName(QString::fromUtf8("spinBoxBlockSize"));

        horizontalLayout_4->addWidget(spinBoxBlockSize);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(sampleTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        horizontalLayout_6->addWidget(label_2);

        spinBoxBlockOverlap = new QSpinBox(sampleTab);
        spinBoxBlockOverlap->setObjectName(QString::fromUtf8("spinBoxBlockOverlap"));

        horizontalLayout_6->addWidget(spinBoxBlockOverlap);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(sampleTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        horizontalLayout_5->addWidget(label_4);

        spinBoxSpectSize = new QSpinBox(sampleTab);
        spinBoxSpectSize->setObjectName(QString::fromUtf8("spinBoxSpectSize"));

        horizontalLayout_5->addWidget(spinBoxSpectSize);


        verticalLayout_2->addLayout(horizontalLayout_5);

        pushButtonGenerate = new QPushButton(sampleTab);
        pushButtonGenerate->setObjectName(QString::fromUtf8("pushButtonGenerate"));
        pushButtonGenerate->setFont(font1);

        verticalLayout_2->addWidget(pushButtonGenerate);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButtonLosdBrain = new QPushButton(sampleTab);
        pushButtonLosdBrain->setObjectName(QString::fromUtf8("pushButtonLosdBrain"));
        pushButtonLosdBrain->setFont(font1);

        horizontalLayout_7->addWidget(pushButtonLosdBrain);

        pushButtonSaveBrain = new QPushButton(sampleTab);
        pushButtonSaveBrain->setObjectName(QString::fromUtf8("pushButtonSaveBrain"));
        pushButtonSaveBrain->setFont(font1);

        horizontalLayout_7->addWidget(pushButtonSaveBrain);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_8->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(sampleTab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        verticalLayout->addWidget(label_5);

        listWidgetSounds = new QListWidget(sampleTab);
        listWidgetSounds->setObjectName(QString::fromUtf8("listWidgetSounds"));

        verticalLayout->addWidget(listWidgetSounds);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonLoadSound = new QPushButton(sampleTab);
        pushButtonLoadSound->setObjectName(QString::fromUtf8("pushButtonLoadSound"));
        pushButtonLoadSound->setFont(font1);

        horizontalLayout_2->addWidget(pushButtonLoadSound);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_8->addLayout(verticalLayout);

        tabWidget->addTab(sampleTab, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonPlay, SIGNAL(released()), MainWindow, SLOT(play_slot()));
        QObject::connect(pushButtonStop, SIGNAL(released()), MainWindow, SLOT(stop_slot()));
        QObject::connect(dialRatio, SIGNAL(sliderMoved(int)), MainWindow, SLOT(ratio_slot(int)));
        QObject::connect(doubleSpinBoxRatio, SIGNAL(valueChanged(double)), MainWindow, SLOT(ratio_slot(double)));
        QObject::connect(spinBoxFFT1Start, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft1_start_slot(int)));
        QObject::connect(spinBoxFFT1End, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft1_end_slot(int)));
        QObject::connect(spinBoxFFT2Start, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft2_start_slot(int)));
        QObject::connect(spinBoxFFT2End, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft2_end_slot(int)));
        QObject::connect(verticalSliderVolume, SIGNAL(sliderMoved(int)), MainWindow, SLOT(volume_slot(int)));
        QObject::connect(pushButtonRun, SIGNAL(released()), MainWindow, SLOT(run_slot()));
        QObject::connect(pushButtonLoadTarget, SIGNAL(released()), MainWindow, SLOT(load_target()));
        QObject::connect(spinBoxBlockSizeTarget, SIGNAL(valueChanged(int)), MainWindow, SLOT(target_block_size(int)));
        QObject::connect(spinBoxBlockOverlapTarget, SIGNAL(valueChanged(int)), MainWindow, SLOT(target_block_overlap(int)));
        QObject::connect(pushButtonGenerateTarget, SIGNAL(released()), MainWindow, SLOT(generate_target_blocks()));
        QObject::connect(spinBoxBlockSize, SIGNAL(valueChanged(int)), MainWindow, SLOT(block_size(int)));
        QObject::connect(spinBoxBlockOverlap, SIGNAL(valueChanged(int)), MainWindow, SLOT(block_overlap(int)));
        QObject::connect(spinBoxSpectSize, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft_spectrum_size(int)));
        QObject::connect(pushButtonGenerate, SIGNAL(released()), MainWindow, SLOT(generate()));
        QObject::connect(pushButtonLoadSound, SIGNAL(released()), MainWindow, SLOT(load_sound()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "samplebrain 0.0.3", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "tweakage", 0, QApplication::UnicodeUTF8));
        pushButtonPlay->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        pushButtonStop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "fft <-> mfcc ratio", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "fft subsection 1", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "End", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "fft subsection 2", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "End", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Volume", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "target sound", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        pushButtonLoadTarget->setText(QApplication::translate("MainWindow", "load target", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "block size", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "block overlap", 0, QApplication::UnicodeUTF8));
        pushButtonGenerateTarget->setText(QApplication::translate("MainWindow", "generate blocks", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "livecode brain", 0, QApplication::UnicodeUTF8));
        pushButtonRun->setText(QApplication::translate("MainWindow", "run", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(controlTab), QApplication::translate("MainWindow", "search", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "brain parameters", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "block size", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "block overlap", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "fft spectrum size", 0, QApplication::UnicodeUTF8));
        pushButtonGenerate->setText(QApplication::translate("MainWindow", "generate", 0, QApplication::UnicodeUTF8));
        pushButtonLosdBrain->setText(QApplication::translate("MainWindow", "load", 0, QApplication::UnicodeUTF8));
        pushButtonSaveBrain->setText(QApplication::translate("MainWindow", "save", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "brain contents", 0, QApplication::UnicodeUTF8));
        pushButtonLoadSound->setText(QApplication::translate("MainWindow", "load sound", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(sampleTab), QApplication::translate("MainWindow", "brain", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SAMPLEBRAINYV5241_H
