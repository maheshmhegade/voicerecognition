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
    waveSine = "sine";
    waveCos = "cos";
    waveRectangular = "rectangular";
    waveTriangular = "triangular";
    waveRamp = "ramp";
    waveNext = "next";
    waveCancel = "cancel";
    waveZero = "zero";
    waveOne = "one";
    waveTwo = "two";
    waveThree = "three";
    waveFour = "four";
    waveFive = "five";
    waveSix = "six";
    waveSeven = "seven";
    waveEight = "eight";
    waveNine = "nine";
    wavePlay = "play";
}

int Dictionary::recognizeWave(char const *inputString)
{
    if(strcmp(inputString,"sine") == 0)
        return 0;
    else if(strcmp(inputString,"cos") == 0)
        return 1;
    else if(strcmp(inputString,"triangular") == 0)
        return 2;
    else if(strcmp(inputString,"rectangular") == 0)
        return 3;
    else if(strcmp(inputString,"ramp") == 0)
        return 4;
    else
        return 5;
}

int Dictionary::recognizeNumber(char const* inputString)
{
    if (strcmp(inputString,"zero") == 0)
        return 0;
    else if (strcmp(inputString,"one") == 0)
        return 1;
    else if (strcmp(inputString,"two") == 0)
        return 2;
    else if (strcmp(inputString,"three") == 0)
        return 3;
    else if (strcmp(inputString,"four") == 0)
        return 4;
    else if(strcmp(inputString,"five") == 0)
        return 5;
    else if (strcmp(inputString,"six") == 0)
        return 6;
    else if (strcmp(inputString,"seven") == 0)
        return 7;
    else if (strcmp(inputString,"eight") == 0)
        return 8;
    else if (strcmp(inputString,"nine") == 0)
        return 9;
    else if (strcmp(inputString,"cancel") == 0)
        return 10;
    else return 11;
}

int Dictionary::recognizeNext(char const* inputString)
{
    if (strcmp(inputString,"next") == 0)
        return 0;
    else if (strcmp(inputString,"cancel") == 0)
        return 1;
    else
        return 2;
}

bool Dictionary::recognizePlay(char const* inputString)
{
    if (strcmp(inputString,"play") == 0)
        return true;
    else
        return false;
}

}//namespace voicerecognition
