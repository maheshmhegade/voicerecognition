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
    char const * waveSine;
    char const * waveCos;
    char const * waveRectangular;
    char const * waveTriangular;
    char const * waveRamp;
    /**
     * @brief  next ==>accept recognition
     *         cancel ==>reject previous recognition
     */
    char const * waveNext;
    char const * waveCancel;
    /**
     * @brief  nubers :common to voltage and frequency
     */
    char const * waveZero;
    char const * waveOne;
    char const * waveTwo;
    char const * waveThree;
    char const * waveFour;
    char const * waveFive;
    char const * waveSix;
    char const * waveSeven;
    char const * waveEight;
    char const * waveNine;
    /**
     * @brief wavePlay::play sound
     */
    char const * wavePlay;

    //methods for recognition decision
public:
    Dictionary();
    int recognizeWave(char const *);
    int recognizeNumber(char const *);
    int recognizeNext(char const *);
    bool recognizePlay(char const *);

};

}//namespace voicerecognition
