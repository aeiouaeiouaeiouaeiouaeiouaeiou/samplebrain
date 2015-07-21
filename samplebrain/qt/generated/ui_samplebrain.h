/********************************************************************************
** Form generated from reading UI file 'samplebrainB32443.ui'
**
** Created: Tue Jul 21 14:56:57 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SAMPLEBRAINB32443_H
#define SAMPLEBRAINB32443_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDial>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QTabWidget *tabWidget;
    QWidget *controlTab;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_6;
    QSlider *sliderRatio;
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
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_16;
    QLabel *label_15;
    QPushButton *pushButtonLoadTarget;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_17;
    QSpinBox *spinBoxBlockSizeTarget;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBoxBlockOverlapTarget;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton_bartlettTarget;
    QRadioButton *radioButton_blackmanTarget;
    QRadioButton *radioButton_gaussianTarget;
    QRadioButton *radioButton_hammingTarget;
    QRadioButton *radioButton_hannTarget;
    QRadioButton *radioButton_flattopTarget;
    QRadioButton *radioButton_dodgyTarget;
    QRadioButton *radioButton_rectangleTarget;
    QLabel *label_14;
    QPushButton *pushButtonGenerateTarget;
    QSpacerItem *verticalSpacer;
    QWidget *sampleTab;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpinBox *spinBoxBlockSize;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxBlockOverlap;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_bartlett;
    QRadioButton *radioButton_dodgy;
    QRadioButton *radioButton_blackman;
    QRadioButton *radioButton_gaussian;
    QRadioButton *radioButton_hamming;
    QRadioButton *radioButton_hann;
    QRadioButton *radioButton_flattop;
    QRadioButton *radioButton_rectagle;
    QLabel *label_4;
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
    QPushButton *pushButtonDeleteSound;
    QPushButton *pushButtonClearBrain;
    QWidget *logTab;
    QHBoxLayout *horizontalLayout_15;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonRecord;
    QPushButton *pushButtonStopRecord;
    QDial *dialVolume;
    QSpacerItem *horizontalSpacer;
    QLabel *label_13;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(724, 613);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font;
        font.setFamily(QString::fromUtf8("Comic Sans MS"));
        font.setBold(true);
        font.setWeight(75);
        tabWidget->setFont(font);
        controlTab = new QWidget();
        controlTab->setObjectName(QString::fromUtf8("controlTab"));
        horizontalLayout_8 = new QHBoxLayout(controlTab);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_19 = new QLabel(controlTab);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Comic Sans MS"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        label_19->setFont(font1);

        verticalLayout_3->addWidget(label_19);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_6 = new QLabel(controlTab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Comic Sans MS"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        label_6->setFont(font2);

        horizontalLayout_16->addWidget(label_6);


        verticalLayout_3->addLayout(horizontalLayout_16);

        sliderRatio = new QSlider(controlTab);
        sliderRatio->setObjectName(QString::fromUtf8("sliderRatio"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sliderRatio->sizePolicy().hasHeightForWidth());
        sliderRatio->setSizePolicy(sizePolicy);
        sliderRatio->setValue(50);
        sliderRatio->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(sliderRatio);

        doubleSpinBoxRatio = new QDoubleSpinBox(controlTab);
        doubleSpinBoxRatio->setObjectName(QString::fromUtf8("doubleSpinBoxRatio"));
        doubleSpinBoxRatio->setMaximum(1);
        doubleSpinBoxRatio->setSingleStep(0.01);
        doubleSpinBoxRatio->setValue(0.5);

        verticalLayout_3->addWidget(doubleSpinBoxRatio);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_7 = new QLabel(controlTab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);

        verticalLayout_4->addWidget(label_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_9 = new QLabel(controlTab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        horizontalLayout_3->addWidget(label_9);

        spinBoxFFT1Start = new QSpinBox(controlTab);
        spinBoxFFT1Start->setObjectName(QString::fromUtf8("spinBoxFFT1Start"));

        horizontalLayout_3->addWidget(spinBoxFFT1Start);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_10 = new QLabel(controlTab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);

        horizontalLayout_9->addWidget(label_10);

        spinBoxFFT1End = new QSpinBox(controlTab);
        spinBoxFFT1End->setObjectName(QString::fromUtf8("spinBoxFFT1End"));
        spinBoxFFT1End->setValue(99);

        horizontalLayout_9->addWidget(spinBoxFFT1End);


        verticalLayout_4->addLayout(horizontalLayout_9);


        verticalLayout_3->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_8 = new QLabel(controlTab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font2);

        verticalLayout_5->addWidget(label_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_11 = new QLabel(controlTab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);

        horizontalLayout_10->addWidget(label_11);

        spinBoxFFT2Start = new QSpinBox(controlTab);
        spinBoxFFT2Start->setObjectName(QString::fromUtf8("spinBoxFFT2Start"));

        horizontalLayout_10->addWidget(spinBoxFFT2Start);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_12 = new QLabel(controlTab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);

        horizontalLayout_11->addWidget(label_12);

        spinBoxFFT2End = new QSpinBox(controlTab);
        spinBoxFFT2End->setObjectName(QString::fromUtf8("spinBoxFFT2End"));
        spinBoxFFT2End->setValue(99);

        horizontalLayout_11->addWidget(spinBoxFFT2End);


        verticalLayout_5->addLayout(horizontalLayout_11);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);


        verticalLayout_3->addLayout(verticalLayout_5);


        horizontalLayout_8->addLayout(verticalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_16 = new QLabel(controlTab);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font1);

        verticalLayout_6->addWidget(label_16);

        label_15 = new QLabel(controlTab);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font);

        verticalLayout_6->addWidget(label_15);

        pushButtonLoadTarget = new QPushButton(controlTab);
        pushButtonLoadTarget->setObjectName(QString::fromUtf8("pushButtonLoadTarget"));
        pushButtonLoadTarget->setFont(font);

        verticalLayout_6->addWidget(pushButtonLoadTarget);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_17 = new QLabel(controlTab);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font);

        horizontalLayout_13->addWidget(label_17);

        spinBoxBlockSizeTarget = new QSpinBox(controlTab);
        spinBoxBlockSizeTarget->setObjectName(QString::fromUtf8("spinBoxBlockSizeTarget"));
        spinBoxBlockSizeTarget->setMaximum(99999);
        spinBoxBlockSizeTarget->setValue(3000);

        horizontalLayout_13->addWidget(spinBoxBlockSizeTarget);


        verticalLayout_6->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_18 = new QLabel(controlTab);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font);

        horizontalLayout_14->addWidget(label_18);

        doubleSpinBoxBlockOverlapTarget = new QDoubleSpinBox(controlTab);
        doubleSpinBoxBlockOverlapTarget->setObjectName(QString::fromUtf8("doubleSpinBoxBlockOverlapTarget"));
        doubleSpinBoxBlockOverlapTarget->setMaximum(1);
        doubleSpinBoxBlockOverlapTarget->setSingleStep(0.01);
        doubleSpinBoxBlockOverlapTarget->setValue(0.75);

        horizontalLayout_14->addWidget(doubleSpinBoxBlockOverlapTarget);


        verticalLayout_6->addLayout(horizontalLayout_14);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButton_bartlettTarget = new QRadioButton(controlTab);
        radioButton_bartlettTarget->setObjectName(QString::fromUtf8("radioButton_bartlettTarget"));

        gridLayout_2->addWidget(radioButton_bartlettTarget, 3, 0, 1, 1);

        radioButton_blackmanTarget = new QRadioButton(controlTab);
        radioButton_blackmanTarget->setObjectName(QString::fromUtf8("radioButton_blackmanTarget"));

        gridLayout_2->addWidget(radioButton_blackmanTarget, 4, 0, 1, 1);

        radioButton_gaussianTarget = new QRadioButton(controlTab);
        radioButton_gaussianTarget->setObjectName(QString::fromUtf8("radioButton_gaussianTarget"));

        gridLayout_2->addWidget(radioButton_gaussianTarget, 2, 1, 1, 1);

        radioButton_hammingTarget = new QRadioButton(controlTab);
        radioButton_hammingTarget->setObjectName(QString::fromUtf8("radioButton_hammingTarget"));

        gridLayout_2->addWidget(radioButton_hammingTarget, 3, 1, 1, 1);

        radioButton_hannTarget = new QRadioButton(controlTab);
        radioButton_hannTarget->setObjectName(QString::fromUtf8("radioButton_hannTarget"));

        gridLayout_2->addWidget(radioButton_hannTarget, 4, 1, 1, 1);

        radioButton_flattopTarget = new QRadioButton(controlTab);
        radioButton_flattopTarget->setObjectName(QString::fromUtf8("radioButton_flattopTarget"));

        gridLayout_2->addWidget(radioButton_flattopTarget, 5, 0, 1, 1);

        radioButton_dodgyTarget = new QRadioButton(controlTab);
        radioButton_dodgyTarget->setObjectName(QString::fromUtf8("radioButton_dodgyTarget"));
        radioButton_dodgyTarget->setChecked(true);

        gridLayout_2->addWidget(radioButton_dodgyTarget, 2, 0, 1, 1);

        radioButton_rectangleTarget = new QRadioButton(controlTab);
        radioButton_rectangleTarget->setObjectName(QString::fromUtf8("radioButton_rectangleTarget"));

        gridLayout_2->addWidget(radioButton_rectangleTarget, 5, 1, 1, 1);

        label_14 = new QLabel(controlTab);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 1, 0, 1, 1);


        verticalLayout_6->addLayout(gridLayout_2);

        pushButtonGenerateTarget = new QPushButton(controlTab);
        pushButtonGenerateTarget->setObjectName(QString::fromUtf8("pushButtonGenerateTarget"));
        pushButtonGenerateTarget->setFont(font);

        verticalLayout_6->addWidget(pushButtonGenerateTarget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        horizontalLayout_8->addLayout(verticalLayout_6);

        tabWidget->addTab(controlTab, QString());
        sampleTab = new QWidget();
        sampleTab->setObjectName(QString::fromUtf8("sampleTab"));
        horizontalLayout_5 = new QHBoxLayout(sampleTab);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_3 = new QLabel(sampleTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(sampleTab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_4->addWidget(label);

        spinBoxBlockSize = new QSpinBox(sampleTab);
        spinBoxBlockSize->setObjectName(QString::fromUtf8("spinBoxBlockSize"));
        spinBoxBlockSize->setMaximum(99999);
        spinBoxBlockSize->setValue(3000);

        horizontalLayout_4->addWidget(spinBoxBlockSize);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(sampleTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_6->addWidget(label_2);

        doubleSpinBoxBlockOverlap = new QDoubleSpinBox(sampleTab);
        doubleSpinBoxBlockOverlap->setObjectName(QString::fromUtf8("doubleSpinBoxBlockOverlap"));
        doubleSpinBoxBlockOverlap->setMaximum(1);
        doubleSpinBoxBlockOverlap->setSingleStep(0.01);
        doubleSpinBoxBlockOverlap->setValue(0.75);

        horizontalLayout_6->addWidget(doubleSpinBoxBlockOverlap);


        verticalLayout_2->addLayout(horizontalLayout_6);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButton_bartlett = new QRadioButton(sampleTab);
        radioButton_bartlett->setObjectName(QString::fromUtf8("radioButton_bartlett"));

        gridLayout->addWidget(radioButton_bartlett, 3, 0, 1, 1);

        radioButton_dodgy = new QRadioButton(sampleTab);
        radioButton_dodgy->setObjectName(QString::fromUtf8("radioButton_dodgy"));
        radioButton_dodgy->setChecked(true);

        gridLayout->addWidget(radioButton_dodgy, 2, 0, 1, 1);

        radioButton_blackman = new QRadioButton(sampleTab);
        radioButton_blackman->setObjectName(QString::fromUtf8("radioButton_blackman"));

        gridLayout->addWidget(radioButton_blackman, 4, 0, 1, 1);

        radioButton_gaussian = new QRadioButton(sampleTab);
        radioButton_gaussian->setObjectName(QString::fromUtf8("radioButton_gaussian"));

        gridLayout->addWidget(radioButton_gaussian, 2, 1, 1, 1);

        radioButton_hamming = new QRadioButton(sampleTab);
        radioButton_hamming->setObjectName(QString::fromUtf8("radioButton_hamming"));

        gridLayout->addWidget(radioButton_hamming, 3, 1, 1, 1);

        radioButton_hann = new QRadioButton(sampleTab);
        radioButton_hann->setObjectName(QString::fromUtf8("radioButton_hann"));

        gridLayout->addWidget(radioButton_hann, 4, 1, 1, 1);

        radioButton_flattop = new QRadioButton(sampleTab);
        radioButton_flattop->setObjectName(QString::fromUtf8("radioButton_flattop"));

        gridLayout->addWidget(radioButton_flattop, 5, 0, 1, 1);

        radioButton_rectagle = new QRadioButton(sampleTab);
        radioButton_rectagle->setObjectName(QString::fromUtf8("radioButton_rectagle"));

        gridLayout->addWidget(radioButton_rectagle, 5, 1, 1, 1);

        label_4 = new QLabel(sampleTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        pushButtonGenerate = new QPushButton(sampleTab);
        pushButtonGenerate->setObjectName(QString::fromUtf8("pushButtonGenerate"));
        pushButtonGenerate->setFont(font);

        verticalLayout_2->addWidget(pushButtonGenerate);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButtonLosdBrain = new QPushButton(sampleTab);
        pushButtonLosdBrain->setObjectName(QString::fromUtf8("pushButtonLosdBrain"));
        pushButtonLosdBrain->setFont(font);

        horizontalLayout_7->addWidget(pushButtonLosdBrain);

        pushButtonSaveBrain = new QPushButton(sampleTab);
        pushButtonSaveBrain->setObjectName(QString::fromUtf8("pushButtonSaveBrain"));
        pushButtonSaveBrain->setFont(font);

        horizontalLayout_7->addWidget(pushButtonSaveBrain);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 508, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_5->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(sampleTab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        listWidgetSounds = new QListWidget(sampleTab);
        listWidgetSounds->setObjectName(QString::fromUtf8("listWidgetSounds"));

        verticalLayout->addWidget(listWidgetSounds);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonLoadSound = new QPushButton(sampleTab);
        pushButtonLoadSound->setObjectName(QString::fromUtf8("pushButtonLoadSound"));
        pushButtonLoadSound->setFont(font);

        horizontalLayout_2->addWidget(pushButtonLoadSound);

        pushButtonDeleteSound = new QPushButton(sampleTab);
        pushButtonDeleteSound->setObjectName(QString::fromUtf8("pushButtonDeleteSound"));
        pushButtonDeleteSound->setFont(font);

        horizontalLayout_2->addWidget(pushButtonDeleteSound);

        pushButtonClearBrain = new QPushButton(sampleTab);
        pushButtonClearBrain->setObjectName(QString::fromUtf8("pushButtonClearBrain"));
        pushButtonClearBrain->setFont(font);

        horizontalLayout_2->addWidget(pushButtonClearBrain);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout);

        tabWidget->addTab(sampleTab, QString());
        logTab = new QWidget();
        logTab->setObjectName(QString::fromUtf8("logTab"));
        horizontalLayout_15 = new QHBoxLayout(logTab);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        plainTextEdit = new QPlainTextEdit(logTab);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        horizontalLayout_15->addWidget(plainTextEdit);

        tabWidget->addTab(logTab, QString());

        verticalLayout_7->addWidget(tabWidget);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        pushButtonPlay = new QPushButton(centralwidget);
        pushButtonPlay->setObjectName(QString::fromUtf8("pushButtonPlay"));
        pushButtonPlay->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonPlay->setIcon(icon);
        pushButtonPlay->setIconSize(QSize(64, 64));
        pushButtonPlay->setFlat(true);

        horizontalLayout_12->addWidget(pushButtonPlay);

        pushButtonStop = new QPushButton(centralwidget);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonStop->setIcon(icon1);
        pushButtonStop->setIconSize(QSize(64, 64));
        pushButtonStop->setFlat(true);

        horizontalLayout_12->addWidget(pushButtonStop);

        pushButtonRecord = new QPushButton(centralwidget);
        pushButtonRecord->setObjectName(QString::fromUtf8("pushButtonRecord"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/record.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonRecord->setIcon(icon2);
        pushButtonRecord->setIconSize(QSize(64, 64));
        pushButtonRecord->setFlat(true);

        horizontalLayout_12->addWidget(pushButtonRecord);

        pushButtonStopRecord = new QPushButton(centralwidget);
        pushButtonStopRecord->setObjectName(QString::fromUtf8("pushButtonStopRecord"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonStopRecord->setIcon(icon3);
        pushButtonStopRecord->setIconSize(QSize(64, 64));
        pushButtonStopRecord->setFlat(true);

        horizontalLayout_12->addWidget(pushButtonStopRecord);

        dialVolume = new QDial(centralwidget);
        dialVolume->setObjectName(QString::fromUtf8("dialVolume"));
        dialVolume->setValue(99);

        horizontalLayout_12->addWidget(dialVolume);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer);

        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/images/images/at.png")));

        horizontalLayout_12->addWidget(label_13);


        verticalLayout_7->addLayout(horizontalLayout_12);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonPlay, SIGNAL(released()), MainWindow, SLOT(play_slot()));
        QObject::connect(pushButtonStop, SIGNAL(released()), MainWindow, SLOT(stop_slot()));
        QObject::connect(doubleSpinBoxRatio, SIGNAL(valueChanged(double)), MainWindow, SLOT(ratio_slot(double)));
        QObject::connect(spinBoxFFT1Start, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft1_start_slot(int)));
        QObject::connect(spinBoxFFT1End, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft1_end_slot(int)));
        QObject::connect(spinBoxFFT2Start, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft2_start_slot(int)));
        QObject::connect(spinBoxFFT2End, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft2_end_slot(int)));
        QObject::connect(pushButtonLoadTarget, SIGNAL(released()), MainWindow, SLOT(load_target()));
        QObject::connect(spinBoxBlockSizeTarget, SIGNAL(valueChanged(int)), MainWindow, SLOT(target_block_size(int)));
        QObject::connect(pushButtonGenerateTarget, SIGNAL(released()), MainWindow, SLOT(generate_target_blocks()));
        QObject::connect(spinBoxBlockSize, SIGNAL(valueChanged(int)), MainWindow, SLOT(block_size(int)));
        QObject::connect(pushButtonGenerate, SIGNAL(released()), MainWindow, SLOT(generate()));
        QObject::connect(pushButtonLoadSound, SIGNAL(released()), MainWindow, SLOT(load_sound()));
        QObject::connect(dialVolume, SIGNAL(sliderMoved(int)), MainWindow, SLOT(volume_slot(int)));
        QObject::connect(doubleSpinBoxBlockOverlap, SIGNAL(valueChanged(double)), MainWindow, SLOT(block_overlap(double)));
        QObject::connect(doubleSpinBoxBlockOverlapTarget, SIGNAL(valueChanged(double)), MainWindow, SLOT(target_block_overlap(double)));
        QObject::connect(pushButtonClearBrain, SIGNAL(released()), MainWindow, SLOT(clear_brain()));
        QObject::connect(pushButtonDeleteSound, SIGNAL(released()), MainWindow, SLOT(delete_sound()));
        QObject::connect(radioButton_bartlett, SIGNAL(toggled(bool)), MainWindow, SLOT(window_bartlett(bool)));
        QObject::connect(radioButton_blackman, SIGNAL(toggled(bool)), MainWindow, SLOT(window_blackman(bool)));
        QObject::connect(radioButton_dodgy, SIGNAL(toggled(bool)), MainWindow, SLOT(window_dodgy(bool)));
        QObject::connect(radioButton_flattop, SIGNAL(toggled(bool)), MainWindow, SLOT(window_flattop(bool)));
        QObject::connect(radioButton_gaussian, SIGNAL(toggled(bool)), MainWindow, SLOT(window_gaussian(bool)));
        QObject::connect(radioButton_hamming, SIGNAL(toggled(bool)), MainWindow, SLOT(window_hamming(bool)));
        QObject::connect(radioButton_hann, SIGNAL(toggled(bool)), MainWindow, SLOT(window_hann(bool)));
        QObject::connect(radioButton_rectagle, SIGNAL(toggled(bool)), MainWindow, SLOT(window_rectangle(bool)));
        QObject::connect(radioButton_bartlettTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_bartlett(bool)));
        QObject::connect(radioButton_blackmanTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_blackman(bool)));
        QObject::connect(radioButton_dodgyTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_dodgy(bool)));
        QObject::connect(radioButton_flattopTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_flattop(bool)));
        QObject::connect(radioButton_gaussianTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_gaussian(bool)));
        QObject::connect(radioButton_hammingTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_hamming(bool)));
        QObject::connect(radioButton_hannTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_hann(bool)));
        QObject::connect(radioButton_rectangleTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_rectangle(bool)));
        QObject::connect(sliderRatio, SIGNAL(valueChanged(int)), MainWindow, SLOT(ratio_slot(int)));
        QObject::connect(pushButtonStopRecord, SIGNAL(released()), MainWindow, SLOT(stop_record()));
        QObject::connect(pushButtonRecord, SIGNAL(released()), MainWindow, SLOT(record()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "samplebrain 0.0.4", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "tweakage", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "fft <-> mfcc ratio", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "fft subsection 1", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "End", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "fft subsection 2", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "End", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "target sound", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "no sound yet...", 0, QApplication::UnicodeUTF8));
        pushButtonLoadTarget->setText(QApplication::translate("MainWindow", "load target", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "block size", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "block overlap", 0, QApplication::UnicodeUTF8));
        radioButton_bartlettTarget->setText(QApplication::translate("MainWindow", "bartlett", 0, QApplication::UnicodeUTF8));
        radioButton_blackmanTarget->setText(QApplication::translate("MainWindow", "blackman", 0, QApplication::UnicodeUTF8));
        radioButton_gaussianTarget->setText(QApplication::translate("MainWindow", "gaussian", 0, QApplication::UnicodeUTF8));
        radioButton_hammingTarget->setText(QApplication::translate("MainWindow", "hamming", 0, QApplication::UnicodeUTF8));
        radioButton_hannTarget->setText(QApplication::translate("MainWindow", "hann", 0, QApplication::UnicodeUTF8));
        radioButton_flattopTarget->setText(QApplication::translate("MainWindow", "flat top", 0, QApplication::UnicodeUTF8));
        radioButton_dodgyTarget->setText(QApplication::translate("MainWindow", "dodgy", 0, QApplication::UnicodeUTF8));
        radioButton_rectangleTarget->setText(QApplication::translate("MainWindow", "rectangle", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "window shape", 0, QApplication::UnicodeUTF8));
        pushButtonGenerateTarget->setText(QApplication::translate("MainWindow", "(re)generate blocks", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(controlTab), QApplication::translate("MainWindow", "search", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "brain parameters", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "block size", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "block overlap", 0, QApplication::UnicodeUTF8));
        radioButton_bartlett->setText(QApplication::translate("MainWindow", "bartlett", 0, QApplication::UnicodeUTF8));
        radioButton_dodgy->setText(QApplication::translate("MainWindow", "dodgy", 0, QApplication::UnicodeUTF8));
        radioButton_blackman->setText(QApplication::translate("MainWindow", "blackman", 0, QApplication::UnicodeUTF8));
        radioButton_gaussian->setText(QApplication::translate("MainWindow", "gaussian", 0, QApplication::UnicodeUTF8));
        radioButton_hamming->setText(QApplication::translate("MainWindow", "hamming", 0, QApplication::UnicodeUTF8));
        radioButton_hann->setText(QApplication::translate("MainWindow", "hann", 0, QApplication::UnicodeUTF8));
        radioButton_flattop->setText(QApplication::translate("MainWindow", "flat top", 0, QApplication::UnicodeUTF8));
        radioButton_rectagle->setText(QApplication::translate("MainWindow", "rectangle", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "window shape", 0, QApplication::UnicodeUTF8));
        pushButtonGenerate->setText(QApplication::translate("MainWindow", "(re)generate", 0, QApplication::UnicodeUTF8));
        pushButtonLosdBrain->setText(QApplication::translate("MainWindow", "load", 0, QApplication::UnicodeUTF8));
        pushButtonSaveBrain->setText(QApplication::translate("MainWindow", "save", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "brain contents", 0, QApplication::UnicodeUTF8));
        pushButtonLoadSound->setText(QApplication::translate("MainWindow", "load sound", 0, QApplication::UnicodeUTF8));
        pushButtonDeleteSound->setText(QApplication::translate("MainWindow", "delete selected", 0, QApplication::UnicodeUTF8));
        pushButtonClearBrain->setText(QApplication::translate("MainWindow", "clear brain", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(sampleTab), QApplication::translate("MainWindow", "brain", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(logTab), QApplication::translate("MainWindow", "log", 0, QApplication::UnicodeUTF8));
        pushButtonPlay->setText(QString());
        pushButtonStop->setText(QString());
        pushButtonRecord->setText(QString());
        pushButtonStopRecord->setText(QString());
        label_13->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SAMPLEBRAINB32443_H
