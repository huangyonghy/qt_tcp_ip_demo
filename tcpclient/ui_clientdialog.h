/*

   Copyright (c) 2006-2007, Johan Thelin
   
   All rights reserved.
   
   Redistribution and use in source and binary forms, with or without modification, 
   are permitted provided that the following conditions are met:
   
       * Redistributions of source code must retain the above copyright notice, 
         this list of conditions and the following disclaimer.
       * Redistributions in binary form must reproduce the above copyright notice,  
         this list of conditions and the following disclaimer in the documentation 
         and/or other materials provided with the distribution.
       * Neither the name of APress nor the names of its contributors 
         may be used to endorse or promote products derived from this software 
         without specific prior written permission.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
*/

/********************************************************************************
** Form generated from reading UI file 'clientdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTDIALOG_H
#define UI_CLIENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ClientDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *ipLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *pnLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *choosePushButton;
    QLineEdit *fileLineEdit;
    QPushButton *filePushButton;

    void setupUi(QDialog *ClientDialog)
    {
        if (ClientDialog->objectName().isEmpty())
            ClientDialog->setObjectName(QStringLiteral("ClientDialog"));
        ClientDialog->resize(563, 192);
        ClientDialog->setStyleSheet(QStringLiteral("QHBoxLayout {background-color: rgb(255, 251, 248)}"));
        verticalLayout_2 = new QVBoxLayout(ClientDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(ClientDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setStyleSheet(QStringLiteral("QLabel{font: 75 18pt \"Arial\"; color: rgb(0, 170, 255)}"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        comboBox = new QComboBox(ClientDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(ClientDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        ipLineEdit = new QLineEdit(ClientDialog);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));

        horizontalLayout_3->addWidget(ipLineEdit);


        horizontalLayout_9->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(ClientDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        pnLineEdit = new QLineEdit(ClientDialog);
        pnLineEdit->setObjectName(QStringLiteral("pnLineEdit"));

        horizontalLayout_4->addWidget(pnLineEdit);


        horizontalLayout_9->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        choosePushButton = new QPushButton(ClientDialog);
        choosePushButton->setObjectName(QStringLiteral("choosePushButton"));

        horizontalLayout->addWidget(choosePushButton);

        fileLineEdit = new QLineEdit(ClientDialog);
        fileLineEdit->setObjectName(QStringLiteral("fileLineEdit"));

        horizontalLayout->addWidget(fileLineEdit);

        filePushButton = new QPushButton(ClientDialog);
        filePushButton->setObjectName(QStringLiteral("filePushButton"));
        filePushButton->setCheckable(false);

        horizontalLayout->addWidget(filePushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 1);

        retranslateUi(ClientDialog);

        QMetaObject::connectSlotsByName(ClientDialog);
    } // setupUi

    void retranslateUi(QDialog *ClientDialog)
    {
        ClientDialog->setWindowTitle(QApplication::translate("ClientDialog", "TCP Client", 0));
        label_3->setText(QApplication::translate("ClientDialog", "Client Side", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("ClientDialog", "Upload File", 0)
         << QApplication::translate("ClientDialog", "Calculation and Feedback Result", 0)
        );
        label->setText(QApplication::translate("ClientDialog", "IP", 0));
        ipLineEdit->setText(QApplication::translate("ClientDialog", "192.168.1.210", 0));
        label_2->setText(QApplication::translate("ClientDialog", "PN", 0));
        pnLineEdit->setText(QApplication::translate("ClientDialog", "9876", 0));
        choosePushButton->setText(QApplication::translate("ClientDialog", "Choose", 0));
        fileLineEdit->setText(QString());
        filePushButton->setText(QApplication::translate("ClientDialog", "commit", 0));
    } // retranslateUi

};

namespace Ui {
    class ClientDialog: public Ui_ClientDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTDIALOG_H
