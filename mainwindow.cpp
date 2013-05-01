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

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/time.h>

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/cont_ad.h>

#include "pocketsphinx.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    static const arg_t cont_args_def[] = {
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

    static ps_decoder_t *ps;
    static cmd_ln_t *config;

    static void
    print_word_times(int32 start)
    {
        ps_seg_t *iter = ps_seg_iter(ps, NULL);
        while (iter != NULL) {
            int32 sf, ef, pprob;
            float conf;

            ps_seg_frames (iter, &sf, &ef);
            pprob = ps_seg_prob (iter, NULL, NULL, NULL);
            conf = logmath_exp(ps_get_logmath(ps), pprob);
            printf ("%s %f %f %f\n", ps_seg_word (iter), (sf + start) / 100.0, (ef + start) / 100.0, conf);
            iter = ps_seg_next (iter);
        }
    }

    /* Sleep for specified msec */
    static void
    sleep_msec(int32 ms)
    {
        struct timeval tmo;

        tmo.tv_sec = 0;
        tmo.tv_usec = ms * 1000;

        select(0, NULL, NULL, NULL, &tmo);
    }

    /*
     * Main utterance processing loop:
     *     for (;;) {
     * 	   wait for start of next utterance;
     * 	   decode utterance until silence of at least 1 sec observed;
     * 	   print utterance result;
     *     }
     */
    static void
    recognize_from_microphone()
    {
        ad_rec_t *ad;
        int16 adbuf[4096], count = 0;
        int32 k, ts, rem;
        char const *hyp;
        char const *uttid;
        cont_ad_t *cont;
        char word[256];
        char pre_word[256];

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

        for (;;) {
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
             */pocketsphinx sphinxbase
            if (ps_start_utt(ps, NULL) < 0)
                E_FATAL("Failed to start utterance\n");
            ps_process_raw(ps, adbuf, k, FALSE, FALSE);
            printf("Listening...\n");
            fflush(stdout);

            /* Note timestamp for this first block of data */
            ts = cont->read_ts;

            /* Decode utterance until end (marked by a "long" silence, >1sec) */
            for (;;) {
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

            if (hyp) {
                sscanf(hyp, "%s", word);
                if ((strcmp(word, "next") == 0) && (count = 0))
                {
                    count++;
                    ui->wavecomboBox->setText((QString) Dictionary::recognizeWave(pre_word));
                }
                else if ((strcmp(word, "next") == 0) && (count = 1))
                {
                    count++;
                    ui->durationlineEdit->setText((QString) Dictionary::recognizeNumber(pre_word));
                }
                else if ((strcmp(word, "next") == 0) && (count = 2))
                {
                    count++;
                    ui->frequencylineEdit->setText((QString) Dictionary::recognizeNumber(pre_word));
                }
                else if ((strcmp(word, "next") == 0) && (count = 3))
                    ui->voltagelineEdit->setText((QString) Dictionary::recognizeNumber(pre_word));

                else if (strcmp(word, "play") == 0)
                    break; /* Exit if the first word spoken was PLAY */

                else
                    sscanf(hyp, "%s", pre_word);
            }

            /* Resume A/D recording for next utterance */
            if (ad_start_rec(ad) < 0)
                E_FATAL("Failed to start recording\n");
        }

        cont_ad_close(cont);
        ad_close(ad);
    }

    static jmp_buf jbuf;
    static void
    sighandler(int signo)
    {
        longjmp(jbuf, 1);
    }

    char const *cfg;

        if (argc == 2) {
            config = cmd_ln_parse_file_r(NULL, cont_args_def, argv[1], TRUE);
        }
        else {
            config = cmd_ln_parse_r(NULL, cont_args_def, argc, argv, FALSE);
        }

        if (config == NULL)
            return 1;

        ps = ps_init(config);
        if (ps == NULL)
            return 1;

        if (setjmp(jbuf) == 0) {
        recognize_from_microphone();
        }

        ps_free(ps);
        return 0;

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
