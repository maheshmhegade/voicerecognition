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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->durationlineEdit->setText((QString)"2");
    ui->frequencylineEdit->setText((QString)"1000");
    ui->voltagelineEdit->setText((QString)"4");
    wave = new outputWave();
    allwaveObject = new alsaSoundcard(); //= alsaSoundcard();
    connect(this,SIGNAL(wave_plotted()),this,SLOT(play_sound()));

}

MainWindow::~MainWindow()
{
    delete wave;
    delete allwaveObject;
    delete ui;
}

void MainWindow::on_applypushButton_clicked()
{

    wave->samplingFrequency = 44100;
    wave->waveDuration = ui->durationlineEdit->text().toInt();
    wave->waveFrequency = ui->frequencylineEdit->text().toInt();
    wave->waveAmplitude = ui->voltagelineEdit->text().toFloat();
    switch (ui->wavecomboBox->currentIndex())
    {
    case 0:
    {
        allwaveObject->generateSin(wave);
        break;
    }
    case 1:
    {
        allwaveObject->generateCos(wave);
        break;
    }
    case 2:
    {
        allwaveObject->generateTriangular(wave);
        break;
    }
    case 3:
    {
        allwaveObject->generateSquare(wave);
        break;
    }
    case 4:
    {
        allwaveObject->generateRamp(wave);
        break;
    }
    }
    QVector<double> x(5000), y(5000);
    ui->widget->addGraph();
    // create graph and assign data to it:
    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(0, 5000);
    ui->widget->yAxis->setRange(-35000,35000);
    for (int i=0; i<5000; ++i)
    {
        x[i] = (double)i; // x goes from -1 to 1
        y[i] = wave->waveSamples[i];//*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x,y);
    ui->widget->replot();

    emit wave_plotted();
}

void MainWindow::play_sound()
{
    allwaveObject->playBack(wave);
}
