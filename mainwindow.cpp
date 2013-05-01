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

    static const arg_t cont_args_def[] =
    {
        POCKETSPHINX_OPTIONS,
        /* Argument file. */
        { "-argfile",
          ARG_STRING,
          NULL,
          "Argument file giving extra arguments." },
        { "-adcdev",
          ARG_STRING,
          NULL,
          "Name of audio device to use for input." },
        { "-infile",
          ARG_STRING,
          NULL,
          "Audio file to transcribe." },
        { "-time",
          ARG_BOOLEAN,
          "no",
          "Print word times in file transcription." },
        CMDLN_EMPTY_OPTION
    };

    static jmp_buf jbuf;

    longjmp(jbuf, 1);

    char **argv;

    argv[0] = "mylm.lm";
    argv[1] = "mydict.dic";
    int argc = 2;

    if (argc == 2)
    {
        config = cmd_ln_parse_file_r(NULL, cont_args_def,argv[1] , TRUE);
    }
    else
    {
        config = cmd_ln_parse_r(NULL, cont_args_def, argc, argv, FALSE);
    }

    if (config == NULL)
        return;

    ps = ps_init(config);
    if (ps == NULL)
        return;

    if (setjmp(jbuf) == 0)
    {
        recognize_from_microphone();
    }

    ps_free(ps);
    return;

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

void MainWindow::sleep_msec(int32 ms)
{
    struct timeval tmo;

    tmo.tv_sec = 0;
    tmo.tv_usec = ms * 1000;

    select(0, NULL, NULL, NULL, &tmo);
}

void MainWindow::recognize_from_microphone()
{
    ad_rec_t *ad;
    int16 adbuf[4096], count = 0;
    int32 k, ts, rem;
    char const *hyp;
    char const *uttid;
    cont_ad_t *cont;

    if ((ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"),
                          (int)cmd_ln_float32_r(config, "-samprate"))) == NULL)
        E_FATAL("Failed to open audio device\n");

    /* Initialize continuous listening module */
    if ((cont = cont_ad_init(ad, ad_read)) == NULL)
        E_FATAL("Failed to initialize voice activity detection\n");
    if (ad_start_rec(ad) < 0)
        E_FATAL("Failed to start recording\n");
    if (cont_ad_calib(cont) < 0)
        E_FATAL("Failed to calibrate voice activity detection\n");

    for (;;)
    {
        /* Indicate listening for next utterance */
        printf("READY....\n");
        fflush(stdout);
        fflush(stderr);

        /* Wait data for next utterance */
        while ((k = cont_ad_read(cont, adbuf, 4096)) == 0)
            sleep_msec(100);

        if (k < 0)
            E_FATAL("Failed to read audio\n");

        /*
         * Non-zero amount of data received; start recognition of new utterance.
         * NULL argument to uttproc_begin_utt => automatic generation of utterance-id.
         */
        if (ps_start_utt(ps, NULL) < 0)
            E_FATAL("Failed to start utterance\n");
        ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        printf("Listening...\n");
        fflush(stdout);

        /* Note timestamp for this first block of data */
        ts = cont->read_ts;

        /* Decode utterance until end (marked by a "long" silence, >1sec) */
        for (;;)
        {
            /* Read non-silence audio data, if any, from continuous listening module */
            if ((k = cont_ad_read(cont, adbuf, 4096)) < 0)
                E_FATAL("Failed to read audio\n");
            if (k == 0) {
                /*
                 * No speech data available; check current timestamp with most recent
                 * speech to see if more than 1 sec elapsed.  If so, end of utterance.
                 */
                if ((cont->read_ts - ts) > DEFAULT_SAMPLES_PER_SEC)
                    break;
            }
            else {
                /* New speech data received; note current timestamp */
                ts = cont->read_ts;
            }

            /*
             * Decode whatever data was read above.
             */
            rem = ps_process_raw(ps, adbuf, k, FALSE, FALSE);

            /* If no work to be done, sleep a bit */
            if ((rem == 0) && (k == 0))
                sleep_msec(20);
        }

        /*
         * Utterance ended; flush any accumulated, unprocessed A/D data and stop
         * listening until current utterance completely decoded
         */
        ad_stop_rec(ad);
        while (ad_read(ad, adbuf, 4096) >= 0);
        cont_ad_reset(cont);

        printf("Stopped listening, please wait...\n");
        fflush(stdout);
        /* Finish decoding, obtain and print result */
        ps_end_utt(ps);
        hyp = ps_get_hyp(ps, NULL, &uttid);
        printf("%s: %s\n", uttid, hyp);

        fflush(stdout);

        Dictionary *myDictionary = Dictionary();

        if (hyp)
        {
            if (trackIndex == 0)
            {
                recognIndex = myDictionary->recognizeWave(hyp);
                if (recognIndex < 5)
                {
                    trackIndex++;
                }
            }
            else if (trackIndex == 2)
            {
                recognIndex = myDictionary->recognizeNumber(hyp);
                if (recognIndex < 10)
                {
                    trackIndex++;
                }
            }
            else if (trackIndex == 4)
            {
                recognIndex = myDictionary->recognizeNumber(hyp);
                if (recognIndex < 4)
                {
                    trackIndex++;
                }
            }
            else if (trackIndex == 1 || trackIndex == 3 || trackIndex == 5)
            {
                recognIndex = myDictionary->recognizeNext(hyp);
                if (recognIndex == 0)
                {
                    trackIndex++;
                }
                else if(recognIndex == 1)
                {

                }
            }
            else
            {
                playSound = myDictionary->recognizePlay(hyp);
            }

        }

        /* Resume A/D recording for next utterance */
        if (ad_start_rec(ad) < 0)
            E_FATAL("Failed to start recording\n");
    }

    cont_ad_close(cont);
    ad_close(ad);
}
