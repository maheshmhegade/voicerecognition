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

#include <QVector>
#ifndef ALSASOUNDCARD_H
#define ALSASOUNDCARD_H
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <alsa/asoundlib.h>

using namespace std;

class outputWave {
public:
    outputWave()
    {
    }
    QVector<double> waveSamples;
    int samplingFrequency;
    int waveFrequency;
    int waveDuration;
    int waveAmplitude;
    ~outputWave();
};

class alsaSoundcard
{
public:
    snd_pcm_t *playback_handle;
    alsaSoundcard();
    int initSoundcard();
    void  generateSin(outputWave *wave);
    void  generateCos(outputWave *wave);
    void  generateTriangular(outputWave *wave);
    void  generateRamp(outputWave *wave);
    void  generateSquare(outputWave *wave);
    void  playBack(outputWave *wave);
};

#endif // ALSASOUNDCARD_H
