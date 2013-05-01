/** ===========================================================
 * @file
 *
 * This file is a part of pcro project
 * <a href="https://github.com/maheshmhegade/pcro">https://github.com/maheshmhegade/pcro</a>
 *
 * @date    2010-04-01
 * @brief   pcro using pc as signal generator.
 * @section DESCRIPTION
 *
 * Using ALSA to output digital data as analogue sound which is standard a mathematical function.
 *
 * @author Copyright (C) 2013 by Mahesh Hegde
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

#include <QString>
#include <iostream>
#include "stdio.h"

#include <pocketsphinx/pocketsphinx.h>

using namespace std;

namespace voicerecognition
{

class Dictionary
{
public:

    //char * variable for comaprision
    /**
     * @brief  Select typeof wave
     */
    const char * waveSine;
    const char * waveCos;
    const char * waveRectangular;
    const char * waveTriangular;
    const char * waveRamp;
    /**
     * @brief  next ==>accept recognition
     *         cancel ==>reject previous recognition
     */
    const char * waveNext;
    const char * waveCancel;
    /**
     * @brief  nubers :common to voltage and frequency
     */
    const char * waveZero;
    const char * waveOne;
    const char * waveTwo;
    const char * waveThree;
    const char * waveFour;
    const char * waveFive;
    const char * waveSix;
    const char * waveSeven;
    const char * waveEight;
    const char * waveNine;
    /**
     * @brief wavePlay::play sound
     */
    const char * wavePlay;

    //methods for recognition decision
public:
    Dictionary();
    int recognizeWave(char);
    int recognizeNumber(char);
    int recognizeNext(const char *);
    bool recognizePlay(const char *);

};

}//namespace voicerecognition
