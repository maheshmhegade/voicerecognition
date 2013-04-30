#include <QString>
#include <iostream>
#include "stdio.h"
using namespace std;

namespace voicerecognition
{

class Dictionary
{
public:

    //char * variable for comaprision
    const char * waveSine;
    const char * waveCos;
    const char * waveRectangular;
    const char * waveTriangular;
    const char * waveRamp;
    const char * waveNext;
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
    const char * wavePlay;

    //methods for recognition decision
public:
    Dictionary();
    int recognizeWave(const char *);
    int recognizeNumber(const char *);
    bool recognizeNext(const char *);
    bool recognizePlay(const char *);

};

}//namespace voicerecognition
