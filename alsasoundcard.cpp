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
    const char *audio_device;
    snd_pcm_hw_params_t *hw_params;
    unsigned int rate = 8000;        // adjust to vary sampling rate
    int numChannels = 1;    // adjust for mono or stereo
    audio_device = "default";

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

void  alsaSoundcard::generateSin(outputWave *wave)
{
    (wave->waveSamples).reserve(wave->waveDuration*wave->samplingFrequency*sizeof(double));
    double angle,increment;
    int x=0;
    angle=0;
    increment=((2*M_PI*wave->waveFrequency)/wave->samplingFrequency);
    while (angle<=(2*M_PI*wave->waveFrequency*wave->waveDuration))
    {
        (wave->waveSamples)[x]=(double) ((wave->waveAmplitude * sin(angle))*32768/5);
        angle=angle+increment;
        x++;
    }
}

void  alsaSoundcard::generateCos(outputWave *wave)
{
    (wave->waveSamples).reserve(wave->waveDuration*wave->samplingFrequency*sizeof(double));
    double angle,increment;
    int x=0;
    angle=0;
    increment=((2*M_PI*wave->waveFrequency)/wave->samplingFrequency);
    while (angle<=(2*M_PI*wave->waveFrequency*wave->waveDuration))
    {
        (wave->waveSamples)[x]=(double) ((wave->waveAmplitude * cos(angle))*32768/5);
        angle=angle+increment;
        x++;
    }
}

void  alsaSoundcard::generateTriangular(outputWave *wave)
{
    (wave->waveSamples).reserve(wave->waveDuration*wave->samplingFrequency*sizeof(double));
    float step;
    int c = 0, x = 1,size;
    size = wave->samplingFrequency*wave->waveDuration;
    step = (float)2*((wave->waveAmplitude*65535*wave->waveFrequency)/(wave->samplingFrequency*5));
    while(c < (wave->waveFrequency*wave->waveDuration))
    {

        (wave->waveSamples)[x-1] = (double)wave->waveAmplitude*(-32767/5);
        for (float i = 0; i < (float)((1/(2*(float)wave->waveFrequency))-(1/(float)wave->samplingFrequency)) ; i += (float)(1/(float)wave->samplingFrequency))
        {
            (wave->waveSamples)[x] = (wave->waveSamples)[x-1] + step;
            x++;
        }
        for (float i = 0.0; i < (float)((1/(2*(float)wave->waveFrequency)) - (1/(float)wave->samplingFrequency)); i += (float)(1/(float)wave->samplingFrequency))
        {
            (wave->waveSamples)[x] = (wave->waveSamples)[x-1] - step;
            x++;
        }
        c++;
    }
}

void  alsaSoundcard::generateRamp(outputWave * wave )
{
    (wave->waveSamples).reserve(wave->waveDuration*wave->samplingFrequency*sizeof(double));
    float i,step;
    int c = 0, x = 1;
    step = (float)((float)wave->waveAmplitude * (65535/5)) *(float)((float)wave->waveFrequency/(float)wave->samplingFrequency);
    while(c < (wave->waveFrequency * wave->waveDuration))
    {
        (wave->waveSamples)[x-1]=(double)wave->waveAmplitude*(-32767/5);
        for (i = 0 ; i < (float)((1/(float)wave->waveFrequency) - (float)(1/(float)wave->samplingFrequency)); i = i + (float)(1/(float)wave->samplingFrequency))
        {
            (wave->waveSamples)[x]=(double)(wave->waveSamples)[x-1] + step;
            x++;
        }
        c++;
    }
}

void  alsaSoundcard::generateSquare(outputWave *wave)
{
    (wave->waveSamples).reserve(wave->waveDuration*wave->samplingFrequency*sizeof(double));
    int x=0;
    float i;
    float limit = 1.0/(float)(2*(float)wave->waveFrequency);
    while(x < (wave->samplingFrequency*wave->waveDuration))
    {
        for(i = 0;i < limit; i = i +(float) (1/(float)wave->samplingFrequency))
        {

            (wave->waveSamples)[x]=(double)wave->waveAmplitude*(32767/5);
            x++;
        }
        for(i = 0 ; i < limit ; i = i + (1/(float)wave->samplingFrequency))
        {

            (wave->waveSamples)[x]=(double)wave->waveAmplitude*(-32767/5);
            x++;
        }
    }
}

void alsaSoundcard::playBack(outputWave *wave)
{
    initSoundcard();
    short int *allSamples = (short int *) malloc(wave->waveDuration*wave->samplingFrequency*sizeof(short int));
    for(int i=0 ;i < wave->waveDuration*wave->samplingFrequency ; i++)
    {
        allSamples[i] = (short int )wave->waveSamples[i];
    }
    int err;
    err = snd_pcm_set_params(playback_handle,SND_PCM_FORMAT_S16,SND_PCM_ACCESS_RW_INTERLEAVED,1,wave->samplingFrequency,1,500000);
    err = snd_pcm_writei(playback_handle,allSamples,wave->waveDuration*wave->samplingFrequency);
    snd_pcm_close(playback_handle);
    delete allSamples;
}

outputWave::~outputWave()
{

}
