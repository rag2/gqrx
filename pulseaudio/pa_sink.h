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
#ifndef PA_SINK_H
#define PA_SINK_H

#include <gr_sync_block.h>
#include <pulse/simple.h>


class pa_sink;

typedef boost::shared_ptr<pa_sink> pa_sink_sptr;

pa_sink_sptr make_pa_sink(int audio_rate, const char *app_name="GNU Radio", const char *stream_name="SDR");


/*! \brief Pulseaudio sink
 *  \ingroup IO
 *
 * This block implements a one channel pulseaudio sink using the Pulseaudio simple API.
 * Note that unlike most other audio backends, this block does not provide the option
 * to select output device because according to pulseaudio philosophy that should be left
 * entirely to the user. (FIXME: How about server?)
 *
 */
class pa_sink : public gr_sync_block
{
    friend pa_sink_sptr make_pa_sink(int audio_rate, const char *app_name, const char *stream_name);

public:
    pa_sink(int audio_rate, const char *app_name="GNU Radio", const char *stream_name="SDR");
    ~pa_sink();

    int work (int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items);


private:
    pa_simple *d_pasink;  /*! The pulseaudio object. */

};

#endif /* PA_SINK_H */
