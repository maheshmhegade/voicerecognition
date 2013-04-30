/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Mar 27 22:51:26 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    QCustomPlot *widget;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *durationlineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *wavecomboBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *frequencylabel;
    QLineEdit *frequencylineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *voltagelabel;
    QLineEdit *voltagelineEdit;
    QPushButton *applypushButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(908, 522);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget = new QCustomPlot(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(500, 500));
        widget->setMaximumSize(QSize(900, 900));
        splitter->addWidget(widget);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        durationlineEdit = new QLineEdit(widget1);
        durationlineEdit->setObjectName(QString::fromUtf8("durationlineEdit"));

        horizontalLayout->addWidget(durationlineEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        wavecomboBox = new QComboBox(widget1);
        wavecomboBox->setObjectName(QString::fromUtf8("wavecomboBox"));

        horizontalLayout_2->addWidget(wavecomboBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        frequencylabel = new QLabel(widget1);
        frequencylabel->setObjectName(QString::fromUtf8("frequencylabel"));

        horizontalLayout_3->addWidget(frequencylabel);

        frequencylineEdit = new QLineEdit(widget1);
        frequencylineEdit->setObjectName(QString::fromUtf8("frequencylineEdit"));

        horizontalLayout_3->addWidget(frequencylineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        voltagelabel = new QLabel(widget1);
        voltagelabel->setObjectName(QString::fromUtf8("voltagelabel"));

        horizontalLayout_4->addWidget(voltagelabel);

        voltagelineEdit = new QLineEdit(widget1);
        voltagelineEdit->setObjectName(QString::fromUtf8("voltagelineEdit"));

        horizontalLayout_4->addWidget(voltagelineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        applypushButton = new QPushButton(widget1);
        applypushButton->setObjectName(QString::fromUtf8("applypushButton"));

        verticalLayout->addWidget(applypushButton);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(118, 248, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        splitter->addWidget(widget1);

        verticalLayout_4->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        widget->raise();
        label->raise();
        durationlineEdit->raise();
        wavecomboBox->raise();
        label_2->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 908, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Duration", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "waveform", 0, QApplication::UnicodeUTF8));
        wavecomboBox->clear();
        wavecomboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Sin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Cos", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Sinc", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Triangular", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Square", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Ramp", 0, QApplication::UnicodeUTF8)
        );
        frequencylabel->setText(QApplication::translate("MainWindow", "Frequency", 0, QApplication::UnicodeUTF8));
        voltagelabel->setText(QApplication::translate("MainWindow", "Voltage", 0, QApplication::UnicodeUTF8));
        applypushButton->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
