/* -*- c++ -*- */
/*
 * Copyright 2011 Alexandru Csete OZ9AEC.
 *
 * Gqrx is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * Gqrx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Gqrx; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#include "pa_sink.h"
#include <gr_io_signature.h>
#include <stdio.h>
//#include <iostream>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>



/*! \brief Create a new pulseaudio sink object.
 *  \param audio_rate The sample rate of the audio stream.
 *  \param app_name Applciation name.
 *  \param stream_name The audio stream name.
 *
 * This is effectively the public constructor for pa_sink.
 */
pa_sink_sptr make_pa_sink(int audio_rate, const char *app_name, const char *stream_name)
{
    return gnuradio::get_initial_sptr(new pa_sink(audio_rate, app_name, stream_name));
}


pa_sink::pa_sink(int audio_rate, const char *app_name, const char *stream_name)
  : gr_sync_block ("pa_sink",
        gr_make_io_signature (1, 1, sizeof(float)),
        gr_make_io_signature (0, 0, 0))
{
    int error;

    /* The sample type to use */
    pa_sample_spec ss;
    ss.format = PA_SAMPLE_FLOAT32LE;
    ss.rate = audio_rate;
    ss.channels = 1;

    d_pasink = pa_simple_new(NULL,
                             app_name,
                             PA_STREAM_PLAYBACK,
                             NULL,
                             stream_name,
                             &ss,
                             NULL,
                             NULL,
                             &error);

    if (!d_pasink) {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
    }

}


pa_sink::~pa_sink()
{
    if (d_pasink) {
        pa_simple_free(d_pasink);
    }
}


int pa_sink::work (int noutput_items,
                   gr_vector_const_void_star &input_items,
                   gr_vector_void_star &output_items)
{
    const void *data = (const void *) input_items[0];
    int error;

    if (pa_simple_write(d_pasink, data, noutput_items*sizeof(float), &error) < 0) {
        fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
    }


    return noutput_items;
}

