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

#include "alsasoundcard.h"
#include <alsa/asoundlib.h>
#include "ui_mainwindow.h"
#include "mainwindow.h"

alsaSoundcard::alsaSoundcard()
{

}

int alsaSoundcard::initSoundcard()
{
    int err;
    snd_pcm_t *playback_handle;
    snd_pcm_hw_params_t *hw_params;
    const char *audio_device;
    unsigned int rate = 8000;        // adjust to vary sampling rate
    int numChannels = 1;    // adjust for mono or stereo
    audio_device = "plughw:0,0";

    if ((err = snd_pcm_open (&playback_handle, audio_device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        fprintf (stderr, "cannot open audio device %s (%s)\n", audio_device, snd_strerror (err));
        return 1;
    }

    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror (err));
        return 2;
    }

    if ((err = snd_pcm_hw_params_any (playback_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror (err));
        return 3;
    }

    if ((err = snd_pcm_hw_params_set_access (playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf (stderr, "cannot set access type (%s)\n", snd_strerror (err));
        return 4;
    }

    if ((err = snd_pcm_hw_params_set_format (playback_handle, hw_params, SND_PCM_FORMAT_S16)) < 0) {
        fprintf (stderr, "cannot set sample format (%s)\n", snd_strerror (err));
        return 5;
    }

    if ((err = snd_pcm_hw_params_set_rate_near (playback_handle, hw_params, &rate, 0)) < 0) {
        fprintf (stderr, "cannot set sample rate (%s)\n",
                 snd_strerror (err));
        return 6;
    }

    if ((err = snd_pcm_hw_params_set_channels (playback_handle, hw_params, numChannels)) < 0) {
        fprintf (stderr, "cannot set channel count (%s)\n",
                 snd_strerror (err));
        return 7;
    }

    if ((err = snd_pcm_hw_params (playback_handle, hw_params)) < 0) {
        fprintf (stderr, "cannot set parameters (%s)\n",
                 snd_strerror (err));
        return 8;
    }

    snd_pcm_hw_params_free (hw_params);

    if ((err = snd_pcm_prepare (playback_handle)) < 0) {
        fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
                 snd_strerror (err));
        return 9;
    }
    return 0;
}

void  alsaSoundcard::generateSin(int frequency,int duration,float amplitude,int samplingfrequency,QVector<double> *outWave)
{
    (*outWave).reserve(duration*samplingfrequency*sizeof(double));
    double angle,increment;
    int x=0;
    short int *allSamples = (short int *) malloc(duration*samplingfrequency*sizeof(short int));
    angle=0;
    increment=((2*M_PI*frequency)/samplingfrequency);
    while (angle<=(2*M_PI*frequency*duration))
    {
        (*outWave)[x]=(double) ((amplitude * sin(angle))*32768/5);
        (allSamples)[x] = (short int)(*outWave)[x];
        angle=angle+increment;
        x++;
    }
    playBack(allSamples,duration,samplingfrequency);
}

void  alsaSoundcard::generateCos(int frequency,int duration,float amplitude,int samplingfrequency,QVector<double> *outWave)
{
    (*outWave).reserve(duration*samplingfrequency*sizeof(double));
    double angle,increment;
    int x=0;
    short int *allSamples = (short int *) malloc(duration*samplingfrequency*sizeof(short int));
    angle=0;
    increment=((2*M_PI*frequency)/samplingfrequency);
    while (angle<=(2*M_PI*frequency*duration))
    {
        (*outWave)[x]=(double)((amplitude * cos(angle))*32768/5);
        (allSamples)[x] = (short int)(*outWave)[x];
        angle=angle+increment;
        x++;
    }
    playBack(allSamples,duration,samplingfrequency);
}

void  alsaSoundcard::generateTriangular(int frequency,int duration,float amplitude,int samplingfrequency,QVector<double> *outWave)
{
    (*outWave).reserve(duration*samplingfrequency*sizeof(double));
    float step;
    short int *allSamples = (short int *) malloc(duration*samplingfrequency*sizeof(short int));
    int c = 0, x = 1,size;
    size = samplingfrequency*duration;
    step = (float)2*((amplitude*65535*frequency)/(samplingfrequency*5));
    while(c < (frequency*duration))
    {

        (*outWave)[x-1] = (double)amplitude*(-32767/5);
        (allSamples)[x] = (short int)(*outWave)[x];
        for (float i = 0; i < (float)((1/(2*(float)frequency))-(1/(float)samplingfrequency)) ; i += (float)(1/(float)samplingfrequency))
        {
            (*outWave)[x] = (*outWave)[x-1] + step;
            (allSamples)[x] = (short int)(*outWave)[x];
            x++;
        }
        for (float i = 0.0; i < (float)((1/(2*(float)frequency)) - (1/(float)samplingfrequency)); i += (float)(1/(float)samplingfrequency))
        {
            (*outWave)[x] = (*outWave)[x-1] - step;
            (allSamples)[x] = (short int)(*outWave)[x];
            x++;
        }
        c++;
    }
    playBack(allSamples,duration,samplingfrequency);

}

void  alsaSoundcard::generateRamp(int frequency,int duration,float amplitude,int samplingfrequency,QVector<double> *outWave)
{
    (*outWave).reserve(duration*samplingfrequency*sizeof(double));
    float i,step;
    int c = 0, x = 1;
    short int *allSamples = (short int *) malloc(duration*samplingfrequency*sizeof(short int));
    step = (float)((float)amplitude * (65535/5)) *(float)((float)frequency/(float)samplingfrequency);
    while(c < (frequency * duration))
    {
        (*outWave)[x-1]=(double)amplitude*(-32767/5);
        (allSamples)[x] = (short int)(*outWave)[x];
        for (i = 0 ; i < (float)((1/(float)frequency) - (float)(1/(float)samplingfrequency)); i = i + (float)(1/(float)samplingfrequency))
        {
            (*outWave)[x]=(double)(*outWave)[x-1] + step;
            (allSamples)[x] = (short int)(*outWave)[x];
            x++;
        }
        c++;
    }
    playBack(allSamples,duration,samplingfrequency);
}

void  alsaSoundcard::generateSinc(int frequency,int duration,float amplitude,int samplingfrequency,QVector<double> *outWave)
{
    frequency = duration = amplitude = samplingfrequency = 0;
    (*outWave).reserve(duration*samplingfrequency*sizeof(double));
}

void  alsaSoundcard::generateSquare(int frequency,int duration,float amplitude,int samplingfrequency,QVector<double> *outWave)
{
    (*outWave).reserve(duration*samplingfrequency*sizeof(double));
    int x=0;
    float i;
    short int *allSamples = (short int *) malloc(duration*samplingfrequency*sizeof(short int));
    float limit = 1.0/(float)(2*(float)frequency);
    while(x < (samplingfrequency*duration))
    {
        for(i = 0;i < limit; i = i +(float) (1/(float)samplingfrequency))
        {

            (*outWave)[x]=(double)amplitude*(32767/5);
            (allSamples)[x] = (short int)(*outWave)[x];
            x++;
        }
        for(i = 0 ; i < limit ; i = i + (1/(float)samplingfrequency))
        {

            (*outWave)[x]=(double)amplitude*(-32767/5);
            (allSamples)[x] = (short int)(*outWave)[x];
            x++;
        }
    }
    playBack(allSamples,duration,samplingfrequency);


}

void alsaSoundcard::playBack(short int *allSamples,int duration,int samplingfrequency)
{
    const char *device = "default";
    snd_pcm_t *pcm;
    int err;

    err = snd_pcm_open(&pcm, device,SND_PCM_STREAM_PLAYBACK,0);
    err = snd_pcm_set_params(pcm,SND_PCM_FORMAT_S16,SND_PCM_ACCESS_RW_INTERLEAVED,1,samplingfrequency,1,500000);
    err = snd_pcm_writei(pcm,allSamples,duration*samplingfrequency);
    snd_pcm_close(pcm);

}
