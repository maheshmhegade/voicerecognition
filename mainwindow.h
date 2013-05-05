/** ===========================================================
 * @file
 *
 * This file is a part of pcro project
 * <a href="https://github.com/maheshmhegade/pcro">https://github.com/maheshmhegade/pcro</a>
 *
 * @date    2010-03-03
 * @brief   pcro using pc as signal generator.
 * @section DESCRIPTION
 *
 * Using ALSA to output digital data as analogue sound which is standard a mathematical function.
 *
 * @author Copyright (C) 2012-2013 by Mahesh Hegde
 *         <a href="mailto:maheshmhegade at gmail dot com">maheshmhegade at gmail dot com</a>
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrentRun>
#include <boost/bind.hpp>
//plot
#include "qcustomplot.h"
#include "alsasoundcard.h"

#include <stdio.h>
#include <string.h>

#include "voicerecognition.h"
#include "ui_mainwindow.h"

using namespace voicerecognition;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void generateWave();
    void plotWave();
    void recognizeVoice();
    outputWave *wave;
    alsaSoundcard *allwaveObject;
    ~MainWindow();

signals:
    void allValuesSet(VoiceRecognition *);
    void wave_plotted();
    void plotAndPlayNow();
private slots:
    void on_applypushButton_clicked();
    void plotAndPlay();

public slots:
    void play_sound();
    void setWaveValues(VoiceRecognition *);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
