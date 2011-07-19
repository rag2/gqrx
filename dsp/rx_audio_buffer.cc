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
#include <dsp/rx_audio_buffer.h>
#include <gr_io_signature.h>
#include <iostream>

rx_audio_buffer_sptr make_rx_audio_buffer(int buffer_size)
{
    return gnuradio::get_initial_sptr (new rx_audio_buffer(buffer_size));
}


rx_audio_buffer::rx_audio_buffer(int buffer_size)
  : gr_sync_block ("null_sink",
        gr_make_io_signature (1, 1, sizeof(float)),
        gr_make_io_signature (0, 0, 0))
{

    buffer.set_capacity(buffer_size);

}


rx_audio_buffer::~rx_audio_buffer()
{

}


int rx_audio_buffer::work (int noutput_items,
                           gr_vector_const_void_star &input_items,
                           gr_vector_void_star &output_items)
{
    const float *in = (const float *) input_items[0];
    int i;

    boost::mutex::scoped_lock lock(d_mutex);

    for (i = 0; i < noutput_items; i++) {
        buffer.push_back(in[i]);
    }

    //std::cout << "Buffer: " << buffer.size() << std::endl;

    return noutput_items;
}


/*! \brief Get audio data from the buffer.
 *  \param data The data buffer.
 *  \param num The The desired number of samples.
 *  \param scale Numer used to scale the data.
 *  \return The actual number of samples copied into data
 *
 */
int rx_audio_buffer::get_data(float *data, int num, float scale)
{
    int len;
    int i;

    boost::mutex::scoped_lock lock(d_mutex);

    if (num > buffer.size()) {
        len = buffer.size();
    }
    else {
        len = num;
    }

    for (i = 0; i < len; i++) {
        data[i] = buffer[0] * scale;
        buffer.pop_front();
    }

    return len;
}
