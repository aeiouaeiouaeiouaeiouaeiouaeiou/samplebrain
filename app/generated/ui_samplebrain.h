/********************************************************************************
** Form generated from reading UI file 'samplebrainqyBmgj.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SAMPLEBRAINQYBMGJ_H
#define SAMPLEBRAINQYBMGJ_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_30;
    QSlider *sliderStickyness;
    QDoubleSpinBox *doubleSpinBoxStickyness;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_28;
    QSlider *sliderSearchStretch;
    QSpinBox *spinBoxSearchStretch;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_32;
    QComboBox *comboBoxAlgorithm;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_26;
    QSlider *sliderSynapses;
    QSpinBox *spinBoxSynapses;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_29;
    QSlider *sliderSlideError;
    QSpinBox *spinBoxSlideError;
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
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_14;
    QComboBox *comboBoxTargetShape;
    QPushButton *pushButtonGenerateTarget;
    QCheckBox *mic;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_31;
    QSlider *sliderAutotune;
    QDoubleSpinBox *doubleSpinBoxAutotune;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_21;
    QSlider *sliderNMix;
    QDoubleSpinBox *doubleSpinBoxNMix;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_22;
    QSlider *sliderTargetMix;
    QDoubleSpinBox *doubleSpinBoxTargetMix;
    QCheckBox *checkBoxStereo;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_3;
    QToolButton *toolButtonAll;
    QToolButton *toolButtonNone;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *brain_contents;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonLoadSound;
    QPushButton *pushButtonLoadSounds;
    QPushButton *pushButtonClearBrain;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpinBox *spinBoxBlockSize;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxBlockOverlap;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_15;
    QComboBox *comboBoxBrainShape;
    QPushButton *pushButtonGenerate;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButtonLoadBrain;
    QPushButton *pushButtonSaveBrain;
    QSpacerItem *verticalSpacer_2;
    QWidget *netTab;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *netContainer;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonRecord;
    QPushButton *pushButtonStopRecord;
    QDial *dialVolume;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonLoadSession;
    QPushButton *pushButtonSaveSession;
    QSpacerItem *horizontalSpacer;
    QLabel *label_13;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1188, 898);
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
        doubleSpinBoxRatio->setMaximum(1.000000000000000);
        doubleSpinBoxRatio->setSingleStep(0.010000000000000);
        doubleSpinBoxRatio->setValue(0.500000000000000);

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
        doubleSpinBoxNRatio->setMaximum(1.000000000000000);
        doubleSpinBoxNRatio->setSingleStep(0.010000000000000);
        doubleSpinBoxNRatio->setValue(0.000000000000000);

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
        doubleSpinBoxNovelty->setMaximum(1.000000000000000);
        doubleSpinBoxNovelty->setSingleStep(0.010000000000000);
        doubleSpinBoxNovelty->setValue(0.000000000000000);

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
        doubleSpinBoxBoredom->setMaximum(1.000000000000000);
        doubleSpinBoxBoredom->setSingleStep(0.010000000000000);
        doubleSpinBoxBoredom->setValue(0.000000000000000);

        horizontalLayout_11->addWidget(doubleSpinBoxBoredom);


        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_30 = new QLabel(controlTab);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font2);

        horizontalLayout_21->addWidget(label_30);

        sliderStickyness = new QSlider(controlTab);
        sliderStickyness->setObjectName(QString::fromUtf8("sliderStickyness"));
        sizePolicy.setHeightForWidth(sliderStickyness->sizePolicy().hasHeightForWidth());
        sliderStickyness->setSizePolicy(sizePolicy);
        sliderStickyness->setMaximum(100);
        sliderStickyness->setValue(0);
        sliderStickyness->setOrientation(Qt::Horizontal);

        horizontalLayout_21->addWidget(sliderStickyness);

        doubleSpinBoxStickyness = new QDoubleSpinBox(controlTab);
        doubleSpinBoxStickyness->setObjectName(QString::fromUtf8("doubleSpinBoxStickyness"));
        sizePolicy1.setHeightForWidth(doubleSpinBoxStickyness->sizePolicy().hasHeightForWidth());
        doubleSpinBoxStickyness->setSizePolicy(sizePolicy1);
        doubleSpinBoxStickyness->setMaximum(1.000000000000000);
        doubleSpinBoxStickyness->setSingleStep(0.010000000000000);
        doubleSpinBoxStickyness->setValue(0.000000000000000);

        horizontalLayout_21->addWidget(doubleSpinBoxStickyness);


        verticalLayout_3->addLayout(horizontalLayout_21);

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

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_32 = new QLabel(controlTab);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setFont(font2);

        horizontalLayout_25->addWidget(label_32);

        comboBoxAlgorithm = new QComboBox(controlTab);
        comboBoxAlgorithm->addItem(QString());
        comboBoxAlgorithm->addItem(QString());
        comboBoxAlgorithm->addItem(QString());
        comboBoxAlgorithm->addItem(QString());
        comboBoxAlgorithm->setObjectName(QString::fromUtf8("comboBoxAlgorithm"));

        horizontalLayout_25->addWidget(comboBoxAlgorithm);


        verticalLayout_3->addLayout(horizontalLayout_25);

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
        spinBoxBlockSizeTarget->setMinimum(10);
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
        doubleSpinBoxBlockOverlapTarget->setMaximum(0.990000000000000);
        doubleSpinBoxBlockOverlapTarget->setSingleStep(0.010000000000000);
        doubleSpinBoxBlockOverlapTarget->setValue(0.800000000000000);

        horizontalLayout_14->addWidget(doubleSpinBoxBlockOverlapTarget);


        verticalLayout_6->addLayout(horizontalLayout_14);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_14 = new QLabel(controlTab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font);

        horizontalLayout_23->addWidget(label_14);

        comboBoxTargetShape = new QComboBox(controlTab);
        comboBoxTargetShape->addItem(QString());
        comboBoxTargetShape->addItem(QString());
        comboBoxTargetShape->addItem(QString());
        comboBoxTargetShape->addItem(QString());
        comboBoxTargetShape->addItem(QString());
        comboBoxTargetShape->addItem(QString());
        comboBoxTargetShape->addItem(QString());
        comboBoxTargetShape->addItem(QString());
        comboBoxTargetShape->setObjectName(QString::fromUtf8("comboBoxTargetShape"));

        horizontalLayout_23->addWidget(comboBoxTargetShape);


        verticalLayout_6->addLayout(horizontalLayout_23);

        pushButtonGenerateTarget = new QPushButton(controlTab);
        pushButtonGenerateTarget->setObjectName(QString::fromUtf8("pushButtonGenerateTarget"));
        pushButtonGenerateTarget->setFont(font);

        verticalLayout_6->addWidget(pushButtonGenerateTarget);

        mic = new QCheckBox(controlTab);
        mic->setObjectName(QString::fromUtf8("mic"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Comic Sans MS"));
        mic->setFont(font3);

        verticalLayout_6->addWidget(mic);

        label_23 = new QLabel(controlTab);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        verticalLayout_6->addWidget(label_23);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_31 = new QLabel(controlTab);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setFont(font2);

        horizontalLayout_22->addWidget(label_31);

        sliderAutotune = new QSlider(controlTab);
        sliderAutotune->setObjectName(QString::fromUtf8("sliderAutotune"));
        sizePolicy.setHeightForWidth(sliderAutotune->sizePolicy().hasHeightForWidth());
        sliderAutotune->setSizePolicy(sizePolicy);
        sliderAutotune->setValue(0);
        sliderAutotune->setOrientation(Qt::Horizontal);

        horizontalLayout_22->addWidget(sliderAutotune);

        doubleSpinBoxAutotune = new QDoubleSpinBox(controlTab);
        doubleSpinBoxAutotune->setObjectName(QString::fromUtf8("doubleSpinBoxAutotune"));
        sizePolicy1.setHeightForWidth(doubleSpinBoxAutotune->sizePolicy().hasHeightForWidth());
        doubleSpinBoxAutotune->setSizePolicy(sizePolicy1);
        doubleSpinBoxAutotune->setMaximum(1.000000000000000);
        doubleSpinBoxAutotune->setSingleStep(0.010000000000000);
        doubleSpinBoxAutotune->setValue(0.000000000000000);

        horizontalLayout_22->addWidget(doubleSpinBoxAutotune);


        verticalLayout_6->addLayout(horizontalLayout_22);

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
        doubleSpinBoxNMix->setMaximum(1.000000000000000);
        doubleSpinBoxNMix->setSingleStep(0.010000000000000);
        doubleSpinBoxNMix->setValue(0.000000000000000);

        horizontalLayout_8->addWidget(doubleSpinBoxNMix);


        verticalLayout_6->addLayout(horizontalLayout_8);

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
        doubleSpinBoxTargetMix->setMaximum(1.000000000000000);
        doubleSpinBoxTargetMix->setSingleStep(0.010000000000000);
        doubleSpinBoxTargetMix->setValue(0.000000000000000);

        horizontalLayout_9->addWidget(doubleSpinBoxTargetMix);


        verticalLayout_6->addLayout(horizontalLayout_9);

        checkBoxStereo = new QCheckBox(controlTab);
        checkBoxStereo->setObjectName(QString::fromUtf8("checkBoxStereo"));

        verticalLayout_6->addWidget(checkBoxStereo);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_3 = new QLabel(controlTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        horizontalLayout_18->addWidget(label_3);

        toolButtonAll = new QToolButton(controlTab);
        toolButtonAll->setObjectName(QString::fromUtf8("toolButtonAll"));

        horizontalLayout_18->addWidget(toolButtonAll);

        toolButtonNone = new QToolButton(controlTab);
        toolButtonNone->setObjectName(QString::fromUtf8("toolButtonNone"));

        horizontalLayout_18->addWidget(toolButtonNone);


        verticalLayout_2->addLayout(horizontalLayout_18);

        scrollArea = new QScrollArea(controlTab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(0, 200));
        scrollArea->setFrameShape(QFrame::StyledPanel);
        scrollArea->setFrameShadow(QFrame::Sunken);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 424, 198));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        brain_contents = new QVBoxLayout();
        brain_contents->setObjectName(QString::fromUtf8("brain_contents"));

        verticalLayout_5->addLayout(brain_contents);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonLoadSound = new QPushButton(controlTab);
        pushButtonLoadSound->setObjectName(QString::fromUtf8("pushButtonLoadSound"));
        pushButtonLoadSound->setFont(font);

        horizontalLayout_2->addWidget(pushButtonLoadSound);

        pushButtonLoadSounds = new QPushButton(controlTab);
        pushButtonLoadSounds->setObjectName(QString::fromUtf8("pushButtonLoadSounds"));
        pushButtonLoadSounds->setFont(font);

        horizontalLayout_2->addWidget(pushButtonLoadSounds);

        pushButtonClearBrain = new QPushButton(controlTab);
        pushButtonClearBrain->setObjectName(QString::fromUtf8("pushButtonClearBrain"));
        pushButtonClearBrain->setFont(font);

        horizontalLayout_2->addWidget(pushButtonClearBrain);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(controlTab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_4->addWidget(label);

        spinBoxBlockSize = new QSpinBox(controlTab);
        spinBoxBlockSize->setObjectName(QString::fromUtf8("spinBoxBlockSize"));
        spinBoxBlockSize->setMinimum(10);
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
        doubleSpinBoxBlockOverlap->setMaximum(0.990000000000000);
        doubleSpinBoxBlockOverlap->setSingleStep(0.010000000000000);
        doubleSpinBoxBlockOverlap->setValue(0.000000000000000);

        horizontalLayout_6->addWidget(doubleSpinBoxBlockOverlap);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_15 = new QLabel(controlTab);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font);

        horizontalLayout_24->addWidget(label_15);

        comboBoxBrainShape = new QComboBox(controlTab);
        comboBoxBrainShape->addItem(QString());
        comboBoxBrainShape->addItem(QString());
        comboBoxBrainShape->addItem(QString());
        comboBoxBrainShape->addItem(QString());
        comboBoxBrainShape->addItem(QString());
        comboBoxBrainShape->addItem(QString());
        comboBoxBrainShape->addItem(QString());
        comboBoxBrainShape->addItem(QString());
        comboBoxBrainShape->setObjectName(QString::fromUtf8("comboBoxBrainShape"));

        horizontalLayout_24->addWidget(comboBoxBrainShape);


        verticalLayout_2->addLayout(horizontalLayout_24);

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

        tabWidget->addTab(controlTab, QString());
        netTab = new QWidget();
        netTab->setObjectName(QString::fromUtf8("netTab"));
        horizontalLayout_15 = new QHBoxLayout(netTab);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        netContainer = new QVBoxLayout();
        netContainer->setObjectName(QString::fromUtf8("netContainer"));

        verticalLayout_7->addLayout(netContainer);

        label_4 = new QLabel(netTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);

        verticalLayout_7->addWidget(label_4);


        horizontalLayout_15->addLayout(verticalLayout_7);

        tabWidget->addTab(netTab, QString());

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

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButtonLoadSession = new QPushButton(centralwidget);
        pushButtonLoadSession->setObjectName(QString::fromUtf8("pushButtonLoadSession"));
        pushButtonLoadSession->setFont(font);

        verticalLayout->addWidget(pushButtonLoadSession);

        pushButtonSaveSession = new QPushButton(centralwidget);
        pushButtonSaveSession->setObjectName(QString::fromUtf8("pushButtonSaveSession"));
        pushButtonSaveSession->setFont(font);

        verticalLayout->addWidget(pushButtonSaveSession);


        horizontalLayout_12->addLayout(verticalLayout);

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
        QObject::connect(spinBoxFFT1End, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft1_end_slot(int)));
        QObject::connect(doubleSpinBoxRatio, SIGNAL(valueChanged(double)), MainWindow, SLOT(ratio_slot(double)));
        QObject::connect(sliderSynapses, SIGNAL(valueChanged(int)), spinBoxSynapses, SLOT(setValue(int)));
        QObject::connect(doubleSpinBoxTargetMix, SIGNAL(valueChanged(double)), MainWindow, SLOT(target_mix_slot(double)));
        QObject::connect(pushButtonGenerateTarget, SIGNAL(released()), MainWindow, SLOT(generate_target_blocks()));
        QObject::connect(spinBoxBlockSizeTarget, SIGNAL(valueChanged(int)), MainWindow, SLOT(target_block_size(int)));
        QObject::connect(pushButtonLoadTarget, SIGNAL(released()), MainWindow, SLOT(load_target()));
        QObject::connect(spinBoxFFT1Start, SIGNAL(valueChanged(int)), MainWindow, SLOT(fft1_start_slot(int)));
        QObject::connect(doubleSpinBoxBlockOverlapTarget, SIGNAL(valueChanged(double)), MainWindow, SLOT(target_block_overlap(double)));
        QObject::connect(spinBoxSynapses, SIGNAL(valueChanged(int)), sliderSynapses, SLOT(setValue(int)));
        QObject::connect(spinBoxSynapses, SIGNAL(valueChanged(int)), MainWindow, SLOT(synapses(int)));
        QObject::connect(sliderRatio, SIGNAL(valueChanged(int)), MainWindow, SLOT(ratio_slot(int)));
        QObject::connect(sliderNRatio, SIGNAL(valueChanged(int)), MainWindow, SLOT(n_ratio_slot(int)));
        QObject::connect(doubleSpinBoxNRatio, SIGNAL(valueChanged(double)), MainWindow, SLOT(n_ratio_slot(double)));
        QObject::connect(sliderTargetMix, SIGNAL(valueChanged(int)), MainWindow, SLOT(target_mix_slot(int)));
        QObject::connect(sliderNMix, SIGNAL(valueChanged(int)), MainWindow, SLOT(n_mix_slot(int)));
        QObject::connect(doubleSpinBoxNMix, SIGNAL(valueChanged(double)), MainWindow, SLOT(n_mix_slot(double)));
        QObject::connect(pushButtonLoadBrain, SIGNAL(released()), MainWindow, SLOT(load_brain()));
        QObject::connect(doubleSpinBoxBoredom, SIGNAL(valueChanged(double)), MainWindow, SLOT(boredom_slot(double)));
        QObject::connect(doubleSpinBoxNovelty, SIGNAL(valueChanged(double)), MainWindow, SLOT(novelty_slot(double)));
        QObject::connect(sliderNovelty, SIGNAL(valueChanged(int)), MainWindow, SLOT(novelty_slot(int)));
        QObject::connect(sliderBoredom, SIGNAL(valueChanged(int)), MainWindow, SLOT(boredom_slot(int)));
        QObject::connect(sliderSynapses, SIGNAL(valueChanged(int)), MainWindow, SLOT(synapses(int)));
        QObject::connect(spinBoxBlockSize, SIGNAL(valueChanged(int)), MainWindow, SLOT(block_size(int)));
        QObject::connect(doubleSpinBoxBlockOverlap, SIGNAL(valueChanged(double)), MainWindow, SLOT(block_overlap(double)));
        QObject::connect(pushButtonSaveBrain, SIGNAL(released()), MainWindow, SLOT(save_brain()));
        QObject::connect(pushButtonClearBrain, SIGNAL(released()), MainWindow, SLOT(clear_brain()));
        QObject::connect(pushButtonGenerate, SIGNAL(released()), MainWindow, SLOT(generate()));
        QObject::connect(pushButtonLoadSound, SIGNAL(released()), MainWindow, SLOT(load_sound()));
        QObject::connect(sliderSearchStretch, SIGNAL(valueChanged(int)), spinBoxSearchStretch, SLOT(setValue(int)));
        QObject::connect(spinBoxSearchStretch, SIGNAL(valueChanged(int)), sliderSearchStretch, SLOT(setValue(int)));
        QObject::connect(sliderSearchStretch, SIGNAL(valueChanged(int)), MainWindow, SLOT(search_stretch(int)));
        QObject::connect(sliderSlideError, SIGNAL(valueChanged(int)), spinBoxSlideError, SLOT(setValue(int)));
        QObject::connect(spinBoxSlideError, SIGNAL(valueChanged(int)), sliderSlideError, SLOT(setValue(int)));
        QObject::connect(sliderSlideError, SIGNAL(valueChanged(int)), MainWindow, SLOT(slide_error(int)));
        QObject::connect(doubleSpinBoxStickyness, SIGNAL(valueChanged(double)), MainWindow, SLOT(stickyness_slot(double)));
        QObject::connect(sliderStickyness, SIGNAL(valueChanged(int)), MainWindow, SLOT(stickyness_slot(int)));
        QObject::connect(sliderAutotune, SIGNAL(sliderMoved(int)), MainWindow, SLOT(autotune(int)));
        QObject::connect(doubleSpinBoxAutotune, SIGNAL(valueChanged(double)), MainWindow, SLOT(autotune(double)));
        QObject::connect(pushButtonLoadSession, SIGNAL(released()), MainWindow, SLOT(load_session()));
        QObject::connect(pushButtonSaveSession, SIGNAL(released()), MainWindow, SLOT(save_session()));
        QObject::connect(checkBoxStereo, SIGNAL(clicked(bool)), MainWindow, SLOT(stereo_mode(bool)));
        QObject::connect(comboBoxAlgorithm, SIGNAL(currentIndexChanged(int)), MainWindow, SLOT(algo(int)));
        QObject::connect(comboBoxTargetShape, SIGNAL(currentIndexChanged(int)), MainWindow, SLOT(target_shape(int)));
        QObject::connect(comboBoxBrainShape, SIGNAL(currentIndexChanged(int)), MainWindow, SLOT(brain_shape(int)));
        QObject::connect(pushButtonLoadSounds, SIGNAL(released()), MainWindow, SLOT(load_sounds()));
        QObject::connect(toolButtonAll, SIGNAL(released()), MainWindow, SLOT(select_all()));
        QObject::connect(toolButtonNone, SIGNAL(released()), MainWindow, SLOT(select_none()));
        QObject::connect(mic, SIGNAL(clicked(bool)), MainWindow, SLOT(mic(bool)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "samplebrain 0.18", nullptr));
        label_19->setText(QApplication::translate("MainWindow", "brain tweaks", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "fft / mfcc", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderRatio->setToolTip(QApplication::translate("MainWindow", "plain fft match vs mfcc values ", nullptr));
#endif // QT_NO_TOOLTIP
        label_20->setText(QApplication::translate("MainWindow", "freq & dynamics / freq only", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderNRatio->setToolTip(QApplication::translate("MainWindow", "match original or normalised blocks", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_7->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("MainWindow", "fft subsection", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Start", nullptr));
#ifndef QT_NO_TOOLTIP
        spinBoxFFT1Start->setToolTip(QApplication::translate("MainWindow", "start frequency to use for fft match", nullptr));
#endif // QT_NO_TOOLTIP
        label_10->setText(QApplication::translate("MainWindow", "End", nullptr));
#ifndef QT_NO_TOOLTIP
        spinBoxFFT1End->setToolTip(QApplication::translate("MainWindow", "end frequency to use for fft match", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_24->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_24->setText(QApplication::translate("MainWindow", "novelty", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderNovelty->setToolTip(QApplication::translate("MainWindow", "use new blocks rather than similar ones", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_25->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_25->setText(QApplication::translate("MainWindow", "boredom", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderBoredom->setToolTip(QApplication::translate("MainWindow", "how long it takes for the novelty to wear off", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_30->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_30->setText(QApplication::translate("MainWindow", "stickyness", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderStickyness->setToolTip(QApplication::translate("MainWindow", "how long it takes for the novelty to wear off", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_28->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_28->setText(QApplication::translate("MainWindow", "search stretch", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderSearchStretch->setToolTip(QApplication::translate("MainWindow", "repeat search (set novelty to 0 for dodgy jungle timessssstretch)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        spinBoxSearchStretch->setToolTip(QApplication::translate("MainWindow", "how many connections to search (ordered in closeness)", nullptr));
#endif // QT_NO_TOOLTIP
        label_32->setText(QApplication::translate("MainWindow", "algorithm", nullptr));
        comboBoxAlgorithm->setItemText(0, QApplication::translate("MainWindow", "basic", nullptr));
        comboBoxAlgorithm->setItemText(1, QApplication::translate("MainWindow", "reversed", nullptr));
        comboBoxAlgorithm->setItemText(2, QApplication::translate("MainWindow", "synaptic", nullptr));
        comboBoxAlgorithm->setItemText(3, QApplication::translate("MainWindow", "slide", nullptr));

#ifndef QT_NO_TOOLTIP
        label_26->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_26->setText(QApplication::translate("MainWindow", "num synpases", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderSynapses->setToolTip(QApplication::translate("MainWindow", "how many connections to search (ordered in closeness)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        spinBoxSynapses->setToolTip(QApplication::translate("MainWindow", "how many connections to search (ordered in closeness)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_29->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_29->setText(QApplication::translate("MainWindow", "synaptic slide error", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderSlideError->setToolTip(QApplication::translate("MainWindow", "block difference higher than this causes a new search, skipping the target", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        spinBoxSlideError->setToolTip(QApplication::translate("MainWindow", "how many connections to search (ordered in closeness)", nullptr));
#endif // QT_NO_TOOLTIP
        label_16->setText(QApplication::translate("MainWindow", "target sound", nullptr));
        pushButtonLoadTarget->setText(QApplication::translate("MainWindow", "load target", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "block size", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "block overlap", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "window shape", nullptr));
        comboBoxTargetShape->setItemText(0, QApplication::translate("MainWindow", "dodgy", nullptr));
        comboBoxTargetShape->setItemText(1, QApplication::translate("MainWindow", "bartlett", nullptr));
        comboBoxTargetShape->setItemText(2, QApplication::translate("MainWindow", "blackman", nullptr));
        comboBoxTargetShape->setItemText(3, QApplication::translate("MainWindow", "flat top", nullptr));
        comboBoxTargetShape->setItemText(4, QApplication::translate("MainWindow", "gaussian", nullptr));
        comboBoxTargetShape->setItemText(5, QApplication::translate("MainWindow", "hamming", nullptr));
        comboBoxTargetShape->setItemText(6, QApplication::translate("MainWindow", "hann", nullptr));
        comboBoxTargetShape->setItemText(7, QApplication::translate("MainWindow", "rectangle", nullptr));

        pushButtonGenerateTarget->setText(QApplication::translate("MainWindow", "(re)generate blocks", nullptr));
        mic->setText(QApplication::translate("MainWindow", "use mic input", nullptr));
        label_23->setText(QApplication::translate("MainWindow", "mix", nullptr));
        label_31->setText(QApplication::translate("MainWindow", "autotune", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderAutotune->setToolTip(QApplication::translate("MainWindow", "amount to match the frequency", nullptr));
#endif // QT_NO_TOOLTIP
        label_21->setText(QApplication::translate("MainWindow", "normalised ", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderNMix->setToolTip(QApplication::translate("MainWindow", "mix in the normalised blocks", nullptr));
#endif // QT_NO_TOOLTIP
        label_22->setText(QApplication::translate("MainWindow", "brain / target", nullptr));
#ifndef QT_NO_TOOLTIP
        sliderTargetMix->setToolTip(QApplication::translate("MainWindow", "mix in the original blocks", nullptr));
#endif // QT_NO_TOOLTIP
        checkBoxStereo->setText(QApplication::translate("MainWindow", "stereo mode", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "brain contents", nullptr));
        toolButtonAll->setText(QApplication::translate("MainWindow", "all", nullptr));
        toolButtonNone->setText(QApplication::translate("MainWindow", "none", nullptr));
        pushButtonLoadSound->setText(QApplication::translate("MainWindow", "load sound", nullptr));
        pushButtonLoadSounds->setText(QApplication::translate("MainWindow", "directory", nullptr));
        pushButtonClearBrain->setText(QApplication::translate("MainWindow", "clear", nullptr));
        label->setText(QApplication::translate("MainWindow", "block size", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "block overlap", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "window shape", nullptr));
        comboBoxBrainShape->setItemText(0, QApplication::translate("MainWindow", "dodgy", nullptr));
        comboBoxBrainShape->setItemText(1, QApplication::translate("MainWindow", "bartlett", nullptr));
        comboBoxBrainShape->setItemText(2, QApplication::translate("MainWindow", "blackman", nullptr));
        comboBoxBrainShape->setItemText(3, QApplication::translate("MainWindow", "flat top", nullptr));
        comboBoxBrainShape->setItemText(4, QApplication::translate("MainWindow", "gaussian", nullptr));
        comboBoxBrainShape->setItemText(5, QApplication::translate("MainWindow", "hamming", nullptr));
        comboBoxBrainShape->setItemText(6, QApplication::translate("MainWindow", "hann", nullptr));
        comboBoxBrainShape->setItemText(7, QApplication::translate("MainWindow", "rectangle", nullptr));

        pushButtonGenerate->setText(QApplication::translate("MainWindow", "(re)generate brain", nullptr));
        pushButtonLoadBrain->setText(QApplication::translate("MainWindow", "load brain", nullptr));
        pushButtonSaveBrain->setText(QApplication::translate("MainWindow", "save brain", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(controlTab), QApplication::translate("MainWindow", "search", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p>This program is free software made in Cornwall by Dave Griffiths at <a href=\"https://thentrythis.org\"><span style=\" text-decoration: underline; color:#0000ff;\">Then Try This</span></a></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(netTab), QApplication::translate("MainWindow", "net", nullptr));
        pushButtonPlay->setText(QString());
        pushButtonStop->setText(QString());
        pushButtonRecord->setText(QString());
        pushButtonStopRecord->setText(QString());
        pushButtonLoadSession->setText(QApplication::translate("MainWindow", "load session", nullptr));
        pushButtonSaveSession->setText(QApplication::translate("MainWindow", "save session", nullptr));
        label_13->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SAMPLEBRAINQYBMGJ_H
