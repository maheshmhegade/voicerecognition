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

#include "voicerecognition.h"

namespace voicerecognition
{

Dictionary::Dictionary()
{
    const char * waveSine = "sine";
    const char * waveCos = "cos";
    const char * waveRectangular = "rectangular";
    const char * wavetriangular = "triangular";
    const char * waveRamp = "ramp";
    const char * waveNext = "next";
    const char * waveCancel = "cancel";
    const char * waceZero = "zero";
    const char * waveOne = "one";
    const char * waveTwo = "two";
    const char * waveThree = "three";
    const char * waveFour = "four";
    const char * waveFive = "five";
    const char * waveSix = "six";
    const char * waveSeven = "seven";
    const char * waveEight = "eight";
    const char * waveNine = "nine";
    const char * wavePlay = "play";
}

int Dictionary::recognizeWave(char inputString)
{
    if(inputString == waveSine)
        return 0;
    else if(inputString == waveCos)
        return 1;
    else if(inputString == waveTriangular)
        return 2;
    else if(inputString == waveRectangular)
        return 3;
    else if(inputString == waveRamp)
        return 4;
    else
        return 5;
}

int Dictionary::recognizeNumber(char inputString)
{
    if (inputString == waveZero)
        return 0;
    else if (inputString == waveOne)
        return 1;
    else if (inputString == waveTwo)
        return 2;
    else if (inputString == waveThree)
        return 3;
    else if (inputString == waveFour)
        return 4;
    else if(inputString == waveFive)
        return 5;
    else if (inputString == waveSix)
        return 6;
    else if (inputString == waveSeven)
        return 7;
    else if (inputString == waveEight)
        return 8;
    else if (inputString == waveNine)
        return 9;
    else if (inputString == waveCancel)
        return 10;
    else return 11;
}

int Dictionary::recognizeNext(const char* inputString)
{
    if (inputString == waveNext)
        return 0;
    else if (inputString == waveCancel)
        return 1;
    else
        return 2;
}

bool Dictionary::recognizePlay(const char* inputString)
{
    if (inputString == wavePlay)
        return true;
    else
        return false;
}

}//namespace voicerecognition
