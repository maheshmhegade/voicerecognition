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
    const char * wavevoltage = "voltage";
    const char * wavefrquency = "frequency";
    const char * waveduration = "duration";
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

int Dictionary::recognizeWave(const char * inputString)
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

int Dictionary::recognizeNumber(const char* inputString)
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
    else return 10;
}

bool Dictionary::recognizeNext(const char* inputString)
{
    if (inputString == waveNext)
        return true;
    else
        return false;
}

bool Dictionary::recognizePlay(const char* inputString)
{
    if (inputString == wavePlay)
        return true;
    else
        return false;
}

}//namespace voicerecognition
