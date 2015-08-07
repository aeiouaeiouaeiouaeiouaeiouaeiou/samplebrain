/********************************************************************************
** Form generated from reading UI file 'samplebrainj21537.ui'
**
** Created: Fri Aug 7 09:55:34 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SAMPLEBRAINJ21537_H
#define SAMPLEBRAINJ21537_H

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
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *controlTab;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_6;
    QSlider *sliderRatio;
    QDoubleSpinBox *doubleSpinBoxRatio;
    QHBoxLayout *horizontalLayout;
    QLabel *label_20;
    QSlider *sliderNRatio;
    QDoubleSpinBox *doubleSpinBoxNRatio;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLabel *label_9;
    QSpinBox *spinBoxFFT1Start;
    QLabel *label_10;
    QSpinBox *spinBoxFFT1End;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_24;
    QSlider *sliderNovelty;
    QDoubleSpinBox *doubleSpinBoxNovelty;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_25;
    QSlider *sliderBoredom;
    QDoubleSpinBox *doubleSpinBoxBoredom;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_28;
    QSlider *sliderSearchStretch;
    QSpinBox *spinBoxSearchStretch;
    QLabel *label_27;
    QHBoxLayout *horizontalLayout_18;
    QRadioButton *radioButtonAlgoBasic;
    QRadioButton *radioButtonAlgoRevBasic;
    QRadioButton *radioButtonSynaptic;
    QRadioButton *radioButtonSynapticSlide;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_26;
    QSlider *sliderSynapses;
    QSpinBox *spinBoxSynapses;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_29;
    QSlider *sliderSlideError;
    QSpinBox *spinBoxSlideError;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_21;
    QSlider *sliderNMix;
    QDoubleSpinBox *doubleSpinBoxNMix;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_22;
    QSlider *sliderTargetMix;
    QDoubleSpinBox *doubleSpinBoxTargetMix;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_16;
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
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpinBox *spinBoxBlockSize;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxBlockOverlap;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_gaussian;
    QRadioButton *radioButton_hamming;
    QRadioButton *radioButton_dodgy;
    QRadioButton *radioButton_blackman;
    QRadioButton *radioButton_rectagle;
    QRadioButton *radioButton_bartlett;
    QRadioButton *radioButton_flattop;
    QRadioButton *radioButton_hann;
    QLabel *label_4;
    QPushButton *pushButtonGenerate;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButtonLoadBrain;
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
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1134, 707);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font;
        font.setFamily(QString::fromUtf8("Comic Sans MS"));
        font.setBold(true);
        font.setWeight(75);
        tabWidget->setFont(font);
        controlTab = new QWidget();
        controlTab->setObjectName(QString::fromUtf8("controlTab"));
        horizontalLayout_5 = new QHBoxLayout(controlTab);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
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
        font2.setPointSize(9);
        font2.setBold(true);
        font2.setWeight(75);
        label_6->setFont(font2);

        horizontalLayout_16->addWidget(label_6);

        sliderRatio = new QSlider(controlTab);
        sliderRatio->setObjectName(QString::fromUtf8("sliderRatio"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sliderRatio->sizePolicy().hasHeightForWidth());
        sliderRatio->setSizePolicy(sizePolicy);
        sliderRatio->setMaximum(100);
        sliderRatio->setValue(50);
        sliderRatio->setOrientation(Qt::Horizontal);

        horizontalLayout_16->addWidget(sliderRatio);

        doubleSpinBoxRatio = new QDoubleSpinBox(controlTab);
        doubleSpinBoxRatio->setObjectName(QString::fromUtf8("doubleSpinBoxRatio"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBoxRatio->sizePolicy().hasHeightForWidth());
        doubleSpinBoxRatio->setSizePolicy(sizePolicy1);
        doubleSpinBoxRatio->setMaximum(1);
        doubleSpinBoxRatio->setSingleStep(0.01);
        doubleSpinBoxRatio->setValue(0.5);

        horizontalLayout_16->addWidget(doubleSpinBoxRatio);


        verticalLayout_3->addLayout(horizontalLayout_16);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_20 = new QLabel(controlTab);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font2);

        horizontalLayout->addWidget(label_20);

        sliderNRatio = new QSlider(controlTab);
        sliderNRatio->setObjectName(QString::fromUtf8("sliderNRatio"));
        sizePolicy.setHeightForWidth(sliderNRatio->sizePolicy().hasHeightForWidth());
        sliderNRatio->setSizePolicy(sizePolicy);
        sliderNRatio->setMaximum(100);
        sliderNRatio->setValue(0);
        sliderNRatio->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(sliderNRatio);

        doubleSpinBoxNRatio = new QDoubleSpinBox(controlTab);
        doubleSpinBoxNRatio->setObjectName(QString::fromUtf8("doubleSpinBoxNRatio"));
        sizePolicy1.setHeightForWidth(doubleSpinBoxNRatio->sizePolicy().hasHeightForWidth());
        doubleSpinBoxNRatio->setSizePolicy(sizePolicy1);
        doubleSpinBoxNRatio->setMaximum(1);
        doubleSpinBoxNRatio->setSingleStep(0.01);
        doubleSpinBoxNRatio->setValue(0);

        horizontalLayout->addWidget(doubleSpinBoxNRatio);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_7 = new QLabel(controlTab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);

        horizontalLayout_3->addWidget(label_7);

        label_9 = new QLabel(controlTab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);
        label_9->setFont(font);

        horizontalLayout_3->addWidget(label_9);

        spinBoxFFT1Start = new QSpinBox(controlTab);
        spinBoxFFT1Start->setObjectName(QString::fromUtf8("spinBoxFFT1Start"));

        horizontalLayout_3->addWidget(spinBoxFFT1Start);

        label_10 = new QLabel(controlTab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy2.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy2);
        label_10->setFont(font);

        horizontalLayout_3->addWidget(label_10);

        spinBoxFFT1End = new QSpinBox(controlTab);
        spinBoxFFT1End->setObjectName(QString::fromUtf8("spinBoxFFT1End"));
        spinBoxFFT1End->setValue(99);

        horizontalLayout_3->addWidget(spinBoxFFT1End);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_24 = new QLabel(controlTab);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font2);

        horizontalLayout_10->addWidget(label_24);

        sliderNovelty = new QSlider(controlTab);
        sliderNovelty->setObjectName(QString::fromUtf8("sliderNovelty"));
        sizePolicy.setHeightForWidth(sliderNovelty->sizePolicy().hasHeightForWidth());
        sliderNovelty->setSizePolicy(sizePolicy);
        sliderNovelty->setMaximum(100);
        sliderNovelty->setValue(0);
        sliderNovelty->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(sliderNovelty);

        doubleSpinBoxNovelty = new QDoubleSpinBox(controlTab);
        doubleSpinBoxNovelty->setObjectName(QString::fromUtf8("doubleSpinBoxNovelty"));
        sizePolicy1.setHeightForWidth(doubleSpinBoxNovelty->sizePolicy().hasHeightForWidth());
        doubleSpinBoxNovelty->setSizePolicy(sizePolicy1);
        doubleSpinBoxNovelty->setMaximum(1);
        doubleSpinBoxNovelty->setSingleStep(0.01);
        doubleSpinBoxNovelty->setValue(0);

        horizontalLayout_10->addWidget(doubleSpinBoxNovelty);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_25 = new QLabel(controlTab);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font2);

        horizontalLayout_11->addWidget(label_25);

        sliderBoredom = new QSlider(controlTab);
        sliderBoredom->setObjectName(QString::fromUtf8("sliderBoredom"));
        sizePolicy.setHeightForWidth(sliderBoredom->sizePolicy().hasHeightForWidth());
        sliderBoredom->setSizePolicy(sizePolicy);
        sliderBoredom->setMaximum(100);
        sliderBoredom->setValue(0);
        sliderBoredom->setOrientation(Qt::Horizontal);

        horizontalLayout_11->addWidget(sliderBoredom);

        doubleSpinBoxBoredom = new QDoubleSpinBox(controlTab);
        doubleSpinBoxBoredom->setObjectName(QString::fromUtf8("doubleSpinBoxBoredom"));
        sizePolicy1.setHeightForWidth(doubleSpinBoxBoredom->sizePolicy().hasHeightForWidth());
        doubleSpinBoxBoredom->setSizePolicy(sizePolicy1);
        doubleSpinBoxBoredom->setMaximum(1);
        doubleSpinBoxBoredom->setSingleStep(0.01);
        doubleSpinBoxBoredom->setValue(0);

        horizontalLayout_11->addWidget(doubleSpinBoxBoredom);


        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_28 = new QLabel(controlTab);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setFont(font2);

        horizontalLayout_19->addWidget(label_28);

        sliderSearchStretch = new QSlider(controlTab);
        sliderSearchStretch->setObjectName(QString::fromUtf8("sliderSearchStretch"));
        sizePolicy.setHeightForWidth(sliderSearchStretch->sizePolicy().hasHeightForWidth());
        sliderSearchStretch->setSizePolicy(sizePolicy);
        sliderSearchStretch->setMinimum(1);
        sliderSearchStretch->setMaximum(50);
        sliderSearchStretch->setValue(1);
        sliderSearchStretch->setOrientation(Qt::Horizontal);

        horizontalLayout_19->addWidget(sliderSearchStretch);

        spinBoxSearchStretch = new QSpinBox(controlTab);
        spinBoxSearchStretch->setObjectName(QString::fromUtf8("spinBoxSearchStretch"));
        sizePolicy1.setHeightForWidth(spinBoxSearchStretch->sizePolicy().hasHeightForWidth());
        spinBoxSearchStretch->setSizePolicy(sizePolicy1);
        spinBoxSearchStretch->setMinimum(1);
        spinBoxSearchStretch->setMaximum(50);
        spinBoxSearchStretch->setValue(1);

        horizontalLayout_19->addWidget(spinBoxSearchStretch);


        verticalLayout_3->addLayout(horizontalLayout_19);

        label_27 = new QLabel(controlTab);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Comic Sans MS"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        label_27->setFont(font3);

        verticalLayout_3->addWidget(label_27);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        radioButtonAlgoBasic = new QRadioButton(controlTab);
        buttonGroup_3 = new QButtonGroup(MainWindow);
        buttonGroup_3->setObjectName(QString::fromUtf8("buttonGroup_3"));
        buttonGroup_3->addButton(radioButtonAlgoBasic);
        radioButtonAlgoBasic->setObjectName(QString::fromUtf8("radioButtonAlgoBasic"));
        radioButtonAlgoBasic->setChecked(true);

        horizontalLayout_18->addWidget(radioButtonAlgoBasic);

        radioButtonAlgoRevBasic = new QRadioButton(controlTab);
        buttonGroup_3->addButton(radioButtonAlgoRevBasic);
        radioButtonAlgoRevBasic->setObjectName(QString::fromUtf8("radioButtonAlgoRevBasic"));

        horizontalLayout_18->addWidget(radioButtonAlgoRevBasic);

        radioButtonSynaptic = new QRadioButton(controlTab);
        buttonGroup_3->addButton(radioButtonSynaptic);
        radioButtonSynaptic->setObjectName(QString::fromUtf8("radioButtonSynaptic"));
        radioButtonSynaptic->setChecked(false);

        horizontalLayout_18->addWidget(radioButtonSynaptic);

        radioButtonSynapticSlide = new QRadioButton(controlTab);
        buttonGroup_3->addButton(radioButtonSynapticSlide);
        radioButtonSynapticSlide->setObjectName(QString::fromUtf8("radioButtonSynapticSlide"));
        radioButtonSynapticSlide->setEnabled(true);
        radioButtonSynapticSlide->setCheckable(true);

        horizontalLayout_18->addWidget(radioButtonSynapticSlide);


        verticalLayout_3->addLayout(horizontalLayout_18);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_26 = new QLabel(controlTab);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setFont(font2);

        horizontalLayout_17->addWidget(label_26);

        sliderSynapses = new QSlider(controlTab);
        sliderSynapses->setObjectName(QString::fromUtf8("sliderSynapses"));
        sizePolicy.setHeightForWidth(sliderSynapses->sizePolicy().hasHeightForWidth());
        sliderSynapses->setSizePolicy(sizePolicy);
        sliderSynapses->setMaximum(1000);
        sliderSynapses->setValue(20);
        sliderSynapses->setOrientation(Qt::Horizontal);

        horizontalLayout_17->addWidget(sliderSynapses);

        spinBoxSynapses = new QSpinBox(controlTab);
        spinBoxSynapses->setObjectName(QString::fromUtf8("spinBoxSynapses"));
        sizePolicy1.setHeightForWidth(spinBoxSynapses->sizePolicy().hasHeightForWidth());
        spinBoxSynapses->setSizePolicy(sizePolicy1);
        spinBoxSynapses->setMaximum(1000);
        spinBoxSynapses->setValue(20);

        horizontalLayout_17->addWidget(spinBoxSynapses);


        verticalLayout_3->addLayout(horizontalLayout_17);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_29 = new QLabel(controlTab);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setFont(font2);

        horizontalLayout_20->addWidget(label_29);

        sliderSlideError = new QSlider(controlTab);
        sliderSlideError->setObjectName(QString::fromUtf8("sliderSlideError"));
        sizePolicy.setHeightForWidth(sliderSlideError->sizePolicy().hasHeightForWidth());
        sliderSlideError->setSizePolicy(sizePolicy);
        sliderSlideError->setMaximum(10000);
        sliderSlideError->setSingleStep(100);
        sliderSlideError->setValue(1000);
        sliderSlideError->setOrientation(Qt::Horizontal);

        horizontalLayout_20->addWidget(sliderSlideError);

        spinBoxSlideError = new QSpinBox(controlTab);
        spinBoxSlideError->setObjectName(QString::fromUtf8("spinBoxSlideError"));
        sizePolicy1.setHeightForWidth(spinBoxSlideError->sizePolicy().hasHeightForWidth());
        spinBoxSlideError->setSizePolicy(sizePolicy1);
        spinBoxSlideError->setMaximum(10000);
        spinBoxSlideError->setSingleStep(100);
        spinBoxSlideError->setValue(1000);

        horizontalLayout_20->addWidget(spinBoxSlideError);


        verticalLayout_3->addLayout(horizontalLayout_20);

        horizontalSpacer_2 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_2);

        label_23 = new QLabel(controlTab);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        verticalLayout_3->addWidget(label_23);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_21 = new QLabel(controlTab);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font2);

        horizontalLayout_8->addWidget(label_21);

        sliderNMix = new QSlider(controlTab);
        sliderNMix->setObjectName(QString::fromUtf8("sliderNMix"));
        sizePolicy.setHeightForWidth(sliderNMix->sizePolicy().hasHeightForWidth());
        sliderNMix->setSizePolicy(sizePolicy);
        sliderNMix->setValue(0);
        sliderNMix->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(sliderNMix);

        doubleSpinBoxNMix = new QDoubleSpinBox(controlTab);
        doubleSpinBoxNMix->setObjectName(QString::fromUtf8("doubleSpinBoxNMix"));
        sizePolicy1.setHeightForWidth(doubleSpinBoxNMix->sizePolicy().hasHeightForWidth());
        doubleSpinBoxNMix->setSizePolicy(sizePolicy1);
        doubleSpinBoxNMix->setMaximum(1);
        doubleSpinBoxNMix->setSingleStep(0.01);
        doubleSpinBoxNMix->setValue(0);

        horizontalLayout_8->addWidget(doubleSpinBoxNMix);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_22 = new QLabel(controlTab);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font2);

        horizontalLayout_9->addWidget(label_22);

        sliderTargetMix = new QSlider(controlTab);
        sliderTargetMix->setObjectName(QString::fromUtf8("sliderTargetMix"));
        sizePolicy.setHeightForWidth(sliderTargetMix->sizePolicy().hasHeightForWidth());
        sliderTargetMix->setSizePolicy(sizePolicy);
        sliderTargetMix->setValue(0);
        sliderTargetMix->setSliderPosition(0);
        sliderTargetMix->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(sliderTargetMix);

        doubleSpinBoxTargetMix = new QDoubleSpinBox(controlTab);
        doubleSpinBoxTargetMix->setObjectName(QString::fromUtf8("doubleSpinBoxTargetMix"));
        sizePolicy1.setHeightForWidth(doubleSpinBoxTargetMix->sizePolicy().hasHeightForWidth());
        doubleSpinBoxTargetMix->setSizePolicy(sizePolicy1);
        doubleSpinBoxTargetMix->setMaximum(1);
        doubleSpinBoxTargetMix->setSingleStep(0.01);
        doubleSpinBoxTargetMix->setValue(0);

        horizontalLayout_9->addWidget(doubleSpinBoxTargetMix);


        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_16 = new QLabel(controlTab);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font1);

        verticalLayout_6->addWidget(label_16);

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
        doubleSpinBoxBlockOverlapTarget->setValue(0);

        horizontalLayout_14->addWidget(doubleSpinBoxBlockOverlapTarget);


        verticalLayout_6->addLayout(horizontalLayout_14);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioButton_bartlettTarget = new QRadioButton(controlTab);
        buttonGroup_2 = new QButtonGroup(MainWindow);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->addButton(radioButton_bartlettTarget);
        radioButton_bartlettTarget->setObjectName(QString::fromUtf8("radioButton_bartlettTarget"));

        gridLayout_2->addWidget(radioButton_bartlettTarget, 3, 0, 1, 1);

        radioButton_blackmanTarget = new QRadioButton(controlTab);
        buttonGroup_2->addButton(radioButton_blackmanTarget);
        radioButton_blackmanTarget->setObjectName(QString::fromUtf8("radioButton_blackmanTarget"));

        gridLayout_2->addWidget(radioButton_blackmanTarget, 4, 0, 1, 1);

        radioButton_gaussianTarget = new QRadioButton(controlTab);
        buttonGroup_2->addButton(radioButton_gaussianTarget);
        radioButton_gaussianTarget->setObjectName(QString::fromUtf8("radioButton_gaussianTarget"));

        gridLayout_2->addWidget(radioButton_gaussianTarget, 2, 1, 1, 1);

        radioButton_hammingTarget = new QRadioButton(controlTab);
        buttonGroup_2->addButton(radioButton_hammingTarget);
        radioButton_hammingTarget->setObjectName(QString::fromUtf8("radioButton_hammingTarget"));

        gridLayout_2->addWidget(radioButton_hammingTarget, 3, 1, 1, 1);

        radioButton_hannTarget = new QRadioButton(controlTab);
        buttonGroup_2->addButton(radioButton_hannTarget);
        radioButton_hannTarget->setObjectName(QString::fromUtf8("radioButton_hannTarget"));

        gridLayout_2->addWidget(radioButton_hannTarget, 4, 1, 1, 1);

        radioButton_flattopTarget = new QRadioButton(controlTab);
        buttonGroup_2->addButton(radioButton_flattopTarget);
        radioButton_flattopTarget->setObjectName(QString::fromUtf8("radioButton_flattopTarget"));

        gridLayout_2->addWidget(radioButton_flattopTarget, 5, 0, 1, 1);

        radioButton_dodgyTarget = new QRadioButton(controlTab);
        buttonGroup_2->addButton(radioButton_dodgyTarget);
        radioButton_dodgyTarget->setObjectName(QString::fromUtf8("radioButton_dodgyTarget"));
        radioButton_dodgyTarget->setChecked(true);

        gridLayout_2->addWidget(radioButton_dodgyTarget, 2, 0, 1, 1);

        radioButton_rectangleTarget = new QRadioButton(controlTab);
        buttonGroup_2->addButton(radioButton_rectangleTarget);
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


        horizontalLayout_5->addLayout(verticalLayout_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_3 = new QLabel(controlTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(controlTab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_4->addWidget(label);

        spinBoxBlockSize = new QSpinBox(controlTab);
        spinBoxBlockSize->setObjectName(QString::fromUtf8("spinBoxBlockSize"));
        spinBoxBlockSize->setMaximum(99999);
        spinBoxBlockSize->setValue(3000);

        horizontalLayout_4->addWidget(spinBoxBlockSize);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(controlTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_6->addWidget(label_2);

        doubleSpinBoxBlockOverlap = new QDoubleSpinBox(controlTab);
        doubleSpinBoxBlockOverlap->setObjectName(QString::fromUtf8("doubleSpinBoxBlockOverlap"));
        doubleSpinBoxBlockOverlap->setMaximum(1);
        doubleSpinBoxBlockOverlap->setSingleStep(0.01);
        doubleSpinBoxBlockOverlap->setValue(0);

        horizontalLayout_6->addWidget(doubleSpinBoxBlockOverlap);


        verticalLayout_2->addLayout(horizontalLayout_6);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioButton_gaussian = new QRadioButton(controlTab);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButton_gaussian);
        radioButton_gaussian->setObjectName(QString::fromUtf8("radioButton_gaussian"));

        gridLayout->addWidget(radioButton_gaussian, 3, 1, 1, 1);

        radioButton_hamming = new QRadioButton(controlTab);
        buttonGroup->addButton(radioButton_hamming);
        radioButton_hamming->setObjectName(QString::fromUtf8("radioButton_hamming"));

        gridLayout->addWidget(radioButton_hamming, 4, 1, 1, 1);

        radioButton_dodgy = new QRadioButton(controlTab);
        buttonGroup->addButton(radioButton_dodgy);
        radioButton_dodgy->setObjectName(QString::fromUtf8("radioButton_dodgy"));
        radioButton_dodgy->setChecked(true);

        gridLayout->addWidget(radioButton_dodgy, 3, 0, 1, 1);

        radioButton_blackman = new QRadioButton(controlTab);
        buttonGroup->addButton(radioButton_blackman);
        radioButton_blackman->setObjectName(QString::fromUtf8("radioButton_blackman"));

        gridLayout->addWidget(radioButton_blackman, 5, 0, 1, 1);

        radioButton_rectagle = new QRadioButton(controlTab);
        buttonGroup->addButton(radioButton_rectagle);
        radioButton_rectagle->setObjectName(QString::fromUtf8("radioButton_rectagle"));

        gridLayout->addWidget(radioButton_rectagle, 6, 1, 1, 1);

        radioButton_bartlett = new QRadioButton(controlTab);
        buttonGroup->addButton(radioButton_bartlett);
        radioButton_bartlett->setObjectName(QString::fromUtf8("radioButton_bartlett"));

        gridLayout->addWidget(radioButton_bartlett, 4, 0, 1, 1);

        radioButton_flattop = new QRadioButton(controlTab);
        buttonGroup->addButton(radioButton_flattop);
        radioButton_flattop->setObjectName(QString::fromUtf8("radioButton_flattop"));

        gridLayout->addWidget(radioButton_flattop, 6, 0, 1, 1);

        radioButton_hann = new QRadioButton(controlTab);
        buttonGroup->addButton(radioButton_hann);
        radioButton_hann->setObjectName(QString::fromUtf8("radioButton_hann"));

        gridLayout->addWidget(radioButton_hann, 5, 1, 1, 1);

        label_4 = new QLabel(controlTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        pushButtonGenerate = new QPushButton(controlTab);
        pushButtonGenerate->setObjectName(QString::fromUtf8("pushButtonGenerate"));
        pushButtonGenerate->setFont(font);

        verticalLayout_2->addWidget(pushButtonGenerate);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButtonLoadBrain = new QPushButton(controlTab);
        pushButtonLoadBrain->setObjectName(QString::fromUtf8("pushButtonLoadBrain"));
        pushButtonLoadBrain->setFont(font);

        horizontalLayout_7->addWidget(pushButtonLoadBrain);

        pushButtonSaveBrain = new QPushButton(controlTab);
        pushButtonSaveBrain->setObjectName(QString::fromUtf8("pushButtonSaveBrain"));
        pushButtonSaveBrain->setFont(font);

        horizontalLayout_7->addWidget(pushButtonSaveBrain);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 508, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_5->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(controlTab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        listWidgetSounds = new QListWidget(controlTab);
        listWidgetSounds->setObjectName(QString::fromUtf8("listWidgetSounds"));

        verticalLayout->addWidget(listWidgetSounds);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonLoadSound = new QPushButton(controlTab);
        pushButtonLoadSound->setObjectName(QString::fromUtf8("pushButtonLoadSound"));
        pushButtonLoadSound->setFont(font);

        horizontalLayout_2->addWidget(pushButtonLoadSound);

        pushButtonDeleteSound = new QPushButton(controlTab);
        pushButtonDeleteSound->setObjectName(QString::fromUtf8("pushButtonDeleteSound"));
        pushButtonDeleteSound->setFont(font);

        horizontalLayout_2->addWidget(pushButtonDeleteSound);

        pushButtonClearBrain = new QPushButton(controlTab);
        pushButtonClearBrain->setObjectName(QString::fromUtf8("pushButtonClearBrain"));
        pushButtonClearBrain->setFont(font);

        horizontalLayout_2->addWidget(pushButtonClearBrain);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout);

        tabWidget->addTab(controlTab, QString());
        logTab = new QWidget();
        logTab->setObjectName(QString::fromUtf8("logTab"));
        horizontalLayout_15 = new QHBoxLayout(logTab);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        plainTextEdit = new QPlainTextEdit(logTab);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        horizontalLayout_15->addWidget(plainTextEdit);

        tabWidget->addTab(logTab, QString());

        verticalLayout_4->addWidget(tabWidget);

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


        verticalLayout_4->addLayout(horizontalLayout_12);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonPlay, SIGNAL(released()), MainWindow, SLOT(play_slot()));
        QObject::connect(pushButtonStop, SIGNAL(released()), MainWindow, SLOT(stop_slot()));
        QObject::connect(dialVolume, SIGNAL(sliderMoved(int)), MainWindow, SLOT(volume_slot(int)));
        QObject::connect(pushButtonStopRecord, SIGNAL(released()), MainWindow, SLOT(stop_record()));
        QObject::connect(pushButtonRecord, SIGNAL(released()), MainWindow, SLOT(record()));
        QObject::connect(radioButton_dodgyTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_dodgy(bool)));
        QObject::connect(radioButton_blackmanTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_blackman(bool)));
        QObject::connect(spinBoxFFT1End, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft1_end_slot(int)));
        QObject::connect(doubleSpinBoxRatio, SIGNAL(valueChanged(double)), MainWindow, SLOT(ratio_slot(double)));
        QObject::connect(radioButton_hannTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_hann(bool)));
        QObject::connect(radioButton_gaussianTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_gaussian(bool)));
        QObject::connect(sliderSynapses, SIGNAL(valueChanged(int)), spinBoxSynapses, SLOT(setValue(int)));
        QObject::connect(doubleSpinBoxTargetMix, SIGNAL(valueChanged(double)), MainWindow, SLOT(target_mix_slot(double)));
        QObject::connect(pushButtonGenerateTarget, SIGNAL(released()), MainWindow, SLOT(generate_target_blocks()));
        QObject::connect(spinBoxBlockSizeTarget, SIGNAL(valueChanged(int)), MainWindow, SLOT(target_block_size(int)));
        QObject::connect(pushButtonLoadTarget, SIGNAL(released()), MainWindow, SLOT(load_target()));
        QObject::connect(spinBoxFFT1Start, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft1_start_slot(int)));
        QObject::connect(radioButton_hammingTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_hamming(bool)));
        QObject::connect(radioButton_flattopTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_flattop(bool)));
        QObject::connect(radioButton_bartlettTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_bartlett(bool)));
        QObject::connect(doubleSpinBoxBlockOverlapTarget, SIGNAL(valueChanged(double)), MainWindow, SLOT(target_block_overlap(double)));
        QObject::connect(radioButton_rectangleTarget, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_rectangle(bool)));
        QObject::connect(spinBoxSynapses, SIGNAL(valueChanged(int)), sliderSynapses, SLOT(setValue(int)));
        QObject::connect(spinBoxSynapses, SIGNAL(valueChanged(int)), MainWindow, SLOT(synapses(int)));
        QObject::connect(sliderRatio, SIGNAL(valueChanged(int)), MainWindow, SLOT(ratio_slot(int)));
        QObject::connect(sliderNRatio, SIGNAL(valueChanged(int)), MainWindow, SLOT(n_ratio_slot(int)));
        QObject::connect(doubleSpinBoxNRatio, SIGNAL(valueChanged(double)), MainWindow, SLOT(n_ratio_slot(double)));
        QObject::connect(radioButton_dodgy, SIGNAL(toggled(bool)), MainWindow, SLOT(window_dodgy(bool)));
        QObject::connect(sliderTargetMix, SIGNAL(valueChanged(int)), MainWindow, SLOT(target_mix_slot(int)));
        QObject::connect(sliderNMix, SIGNAL(valueChanged(int)), MainWindow, SLOT(n_mix_slot(int)));
        QObject::connect(doubleSpinBoxNMix, SIGNAL(valueChanged(double)), MainWindow, SLOT(n_mix_slot(double)));
        QObject::connect(pushButtonLoadBrain, SIGNAL(released()), MainWindow, SLOT(load_brain()));
        QObject::connect(radioButtonSynaptic, SIGNAL(toggled(bool)), MainWindow, SLOT(algo_synaptic(bool)));
        QObject::connect(doubleSpinBoxBoredom, SIGNAL(valueChanged(double)), MainWindow, SLOT(boredom_slot(double)));
        QObject::connect(doubleSpinBoxNovelty, SIGNAL(valueChanged(double)), MainWindow, SLOT(novelty_slot(double)));
        QObject::connect(sliderNovelty, SIGNAL(valueChanged(int)), MainWindow, SLOT(novelty_slot(int)));
        QObject::connect(sliderBoredom, SIGNAL(valueChanged(int)), MainWindow, SLOT(boredom_slot(int)));
        QObject::connect(radioButton_bartlett, SIGNAL(toggled(bool)), MainWindow, SLOT(window_bartlett(bool)));
        QObject::connect(radioButton_blackman, SIGNAL(toggled(bool)), MainWindow, SLOT(window_blackman(bool)));
        QObject::connect(sliderSynapses, SIGNAL(valueChanged(int)), MainWindow, SLOT(synapses(int)));
        QObject::connect(radioButtonSynapticSlide, SIGNAL(toggled(bool)), MainWindow, SLOT(algo_synaptic_slide(bool)));
        QObject::connect(spinBoxBlockSize, SIGNAL(valueChanged(int)), MainWindow, SLOT(block_size(int)));
        QObject::connect(doubleSpinBoxBlockOverlap, SIGNAL(valueChanged(double)), MainWindow, SLOT(block_overlap(double)));
        QObject::connect(radioButton_gaussian, SIGNAL(toggled(bool)), MainWindow, SLOT(window_gaussian(bool)));
        QObject::connect(radioButton_flattop, SIGNAL(toggled(bool)), MainWindow, SLOT(window_flattop(bool)));
        QObject::connect(radioButtonAlgoBasic, SIGNAL(toggled(bool)), MainWindow, SLOT(algo_basic(bool)));
        QObject::connect(radioButtonAlgoRevBasic, SIGNAL(toggled(bool)), MainWindow, SLOT(algo_rev_basic(bool)));
        QObject::connect(radioButton_rectagle, SIGNAL(toggled(bool)), MainWindow, SLOT(window_target_rectangle(bool)));
        QObject::connect(radioButton_hamming, SIGNAL(toggled(bool)), MainWindow, SLOT(window_hamming(bool)));
        QObject::connect(pushButtonSaveBrain, SIGNAL(released()), MainWindow, SLOT(save_brain()));
        QObject::connect(pushButtonDeleteSound, SIGNAL(released()), MainWindow, SLOT(delete_sound()));
        QObject::connect(pushButtonClearBrain, SIGNAL(released()), MainWindow, SLOT(clear_brain()));
        QObject::connect(pushButtonGenerate, SIGNAL(released()), MainWindow, SLOT(generate()));
        QObject::connect(pushButtonLoadSound, SIGNAL(released()), MainWindow, SLOT(load_sound()));
        QObject::connect(radioButton_hann, SIGNAL(toggled(bool)), MainWindow, SLOT(window_hann(bool)));
        QObject::connect(sliderSearchStretch, SIGNAL(valueChanged(int)), spinBoxSearchStretch, SLOT(setValue(int)));
        QObject::connect(spinBoxSearchStretch, SIGNAL(valueChanged(int)), sliderSearchStretch, SLOT(setValue(int)));
        QObject::connect(sliderSearchStretch, SIGNAL(valueChanged(int)), MainWindow, SLOT(search_stretch(int)));
        QObject::connect(sliderSlideError, SIGNAL(valueChanged(int)), spinBoxSlideError, SLOT(setValue(int)));
        QObject::connect(spinBoxSlideError, SIGNAL(valueChanged(int)), sliderSlideError, SLOT(setValue(int)));
        QObject::connect(sliderSlideError, SIGNAL(valueChanged(int)), MainWindow, SLOT(slide_error(int)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "samplebrain 0.9", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "brain tweaks", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "fft / mfcc", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderRatio->setToolTip(QApplication::translate("MainWindow", "plain fft match vs mfcc values ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_20->setText(QApplication::translate("MainWindow", "freq & dynamics / freq only", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderNRatio->setToolTip(QApplication::translate("MainWindow", "match original or normalised blocks", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_7->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("MainWindow", "fft subsection", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinBoxFFT1Start->setToolTip(QApplication::translate("MainWindow", "start frequency to use for fft match", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_10->setText(QApplication::translate("MainWindow", "End", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinBoxFFT1End->setToolTip(QApplication::translate("MainWindow", "end frequency to use for fft match", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_24->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_24->setText(QApplication::translate("MainWindow", "novelty", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderNovelty->setToolTip(QApplication::translate("MainWindow", "use new blocks rather than similar ones", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_25->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_25->setText(QApplication::translate("MainWindow", "boredom", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderBoredom->setToolTip(QApplication::translate("MainWindow", "how long it takes for the novelty to wear off", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_28->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_28->setText(QApplication::translate("MainWindow", "search stretch", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderSearchStretch->setToolTip(QApplication::translate("MainWindow", "repeat search (set novelty to 0 for dodgy jungle timessssstretch)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        spinBoxSearchStretch->setToolTip(QApplication::translate("MainWindow", "how many connections to search (ordered in closeness)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_27->setText(QApplication::translate("MainWindow", "algorithm", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonAlgoBasic->setToolTip(QApplication::translate("MainWindow", "full brain search", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButtonAlgoBasic->setText(QApplication::translate("MainWindow", "basic", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonAlgoRevBasic->setToolTip(QApplication::translate("MainWindow", "full brain reverse search", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButtonAlgoRevBasic->setText(QApplication::translate("MainWindow", "rev basic", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonSynaptic->setToolTip(QApplication::translate("MainWindow", "search based on synapse connections", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButtonSynaptic->setText(QApplication::translate("MainWindow", "synaptic", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButtonSynapticSlide->setToolTip(QApplication::translate("MainWindow", "search based on synapses and sonify search process", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButtonSynapticSlide->setText(QApplication::translate("MainWindow", "synaptic slide", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_26->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_26->setText(QApplication::translate("MainWindow", "num synpases", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderSynapses->setToolTip(QApplication::translate("MainWindow", "how many connections to search (ordered in closeness)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        spinBoxSynapses->setToolTip(QApplication::translate("MainWindow", "how many connections to search (ordered in closeness)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_29->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_29->setText(QApplication::translate("MainWindow", "synaptic slide error", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderSlideError->setToolTip(QApplication::translate("MainWindow", "block difference higher than this causes a new search, skipping the target", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        spinBoxSlideError->setToolTip(QApplication::translate("MainWindow", "how many connections to search (ordered in closeness)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_23->setText(QApplication::translate("MainWindow", "mix", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainWindow", "dynamic / normalised ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderNMix->setToolTip(QApplication::translate("MainWindow", "mix in the normalised blocks", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_22->setText(QApplication::translate("MainWindow", "brain / target", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sliderTargetMix->setToolTip(QApplication::translate("MainWindow", "mix in the original blocks", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_16->setText(QApplication::translate("MainWindow", "target sound", 0, QApplication::UnicodeUTF8));
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
        label_3->setText(QApplication::translate("MainWindow", "brain parameters", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "block size", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "block overlap", 0, QApplication::UnicodeUTF8));
        radioButton_gaussian->setText(QApplication::translate("MainWindow", "gaussian", 0, QApplication::UnicodeUTF8));
        radioButton_hamming->setText(QApplication::translate("MainWindow", "hamming", 0, QApplication::UnicodeUTF8));
        radioButton_dodgy->setText(QApplication::translate("MainWindow", "dodgy", 0, QApplication::UnicodeUTF8));
        radioButton_blackman->setText(QApplication::translate("MainWindow", "blackman", 0, QApplication::UnicodeUTF8));
        radioButton_rectagle->setText(QApplication::translate("MainWindow", "rectangle", 0, QApplication::UnicodeUTF8));
        radioButton_bartlett->setText(QApplication::translate("MainWindow", "bartlett", 0, QApplication::UnicodeUTF8));
        radioButton_flattop->setText(QApplication::translate("MainWindow", "flat top", 0, QApplication::UnicodeUTF8));
        radioButton_hann->setText(QApplication::translate("MainWindow", "hann", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "window shape", 0, QApplication::UnicodeUTF8));
        pushButtonGenerate->setText(QApplication::translate("MainWindow", "(re)generate brain", 0, QApplication::UnicodeUTF8));
        pushButtonLoadBrain->setText(QApplication::translate("MainWindow", "load brain", 0, QApplication::UnicodeUTF8));
        pushButtonSaveBrain->setText(QApplication::translate("MainWindow", "save brain", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "brain contents", 0, QApplication::UnicodeUTF8));
        pushButtonLoadSound->setText(QApplication::translate("MainWindow", "load sound", 0, QApplication::UnicodeUTF8));
        pushButtonDeleteSound->setText(QApplication::translate("MainWindow", "delete selected", 0, QApplication::UnicodeUTF8));
        pushButtonClearBrain->setText(QApplication::translate("MainWindow", "clear brain", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(controlTab), QApplication::translate("MainWindow", "search", 0, QApplication::UnicodeUTF8));
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

#endif // SAMPLEBRAINJ21537_H
