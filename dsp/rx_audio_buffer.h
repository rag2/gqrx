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
#ifndef RX_AUDIO_BUFFER_H
#define RX_AUDIO_BUFFER_H

#include <gr_sync_block.h>
#include <boost/circular_buffer.hpp>


class rx_audio_buffer;

typedef boost::shared_ptr<rx_audio_buffer> rx_audio_buffer_sptr;

rx_audio_buffer_sptr make_rx_audio_buffer (int buffer_size=4096);


/*! \brief Audio output buffer
 *  \ingroup DSP
 *
 * This class implements an audio sink that will accumulate audio
 * samples in a circular buffer. This is to allow the GNU Radio audio
 * sink block and the QAudioOutput to run in separate threads without
 * conflicting with each other.
 *
 */
class rx_audio_buffer : public gr_sync_block
{
    friend rx_audio_buffer_sptr make_rx_audio_buffer(int buffer_size);

public:
    rx_audio_buffer(int buffer_size);
    ~rx_audio_buffer();

    virtual int work (int noutput_items,
                      gr_vector_const_void_star &input_items,
                      gr_vector_void_star &output_items);

private:
    boost::circular_buffer<float> buffer;

};

#endif /* RX_AUDIO_BUFFER_H */
