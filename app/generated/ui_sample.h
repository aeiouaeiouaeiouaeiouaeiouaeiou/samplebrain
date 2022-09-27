/********************************************************************************
** Form generated from reading UI file 'sampleSy5241.ui'
**
** Created: Sat Jul 11 10:24:07 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SAMPLESY5241_H
#define SAMPLESY5241_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormSample
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QLabel *labelSampleName;
    QLabel *labelSampleInfo;
    QPushButton *pushButton;

    void setupUi(QWidget *FormSample)
    {
        if (FormSample->objectName().isEmpty())
            FormSample->setObjectName(QString::fromUtf8("FormSample"));
        FormSample->resize(400, 46);
        horizontalLayout = new QHBoxLayout(FormSample);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox = new QCheckBox(FormSample);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        QFont font;
        font.setFamily(QString::fromUtf8("Helvetica"));
        font.setBold(true);
        font.setWeight(75);
        checkBox->setFont(font);

        horizontalLayout->addWidget(checkBox);

        labelSampleName = new QLabel(FormSample);
        labelSampleName->setObjectName(QString::fromUtf8("labelSampleName"));
        labelSampleName->setFont(font);

        horizontalLayout->addWidget(labelSampleName);

        labelSampleInfo = new QLabel(FormSample);
        labelSampleInfo->setObjectName(QString::fromUtf8("labelSampleInfo"));
        labelSampleInfo->setFont(font);

        horizontalLayout->addWidget(labelSampleInfo);

        pushButton = new QPushButton(FormSample);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font);

        horizontalLayout->addWidget(pushButton);


        retranslateUi(FormSample);

        QMetaObject::connectSlotsByName(FormSample);
    } // setupUi

    void retranslateUi(QWidget *FormSample)
    {
        FormSample->setWindowTitle(QApplication::translate("FormSample", "Form", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("FormSample", "active", 0, QApplication::UnicodeUTF8));
        labelSampleName->setText(QApplication::translate("FormSample", "TextLabel", 0, QApplication::UnicodeUTF8));
        labelSampleInfo->setText(QApplication::translate("FormSample", "TextLabel", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("FormSample", "delete", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormSample: public Ui_FormSample {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SAMPLESY5241_H
