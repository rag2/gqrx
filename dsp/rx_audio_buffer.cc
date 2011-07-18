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


rx_audio_buffer_sptr make_rx_audio_buffer(int buffer_size)
{
    return gnuradio::get_initial_sptr (new rx_audio_buffer(buffer_size));
}


rx_audio_buffer::rx_audio_buffer(int buffer_size)
  : gr_sync_block ("null_sink",
        gr_make_io_signature (1, 1, sizeof(float)),
        gr_make_io_signature (0, 0, 0))
{

}


rx_audio_buffer::~rx_audio_buffer()
{

}


int rx_audio_buffer::work (int noutput_items,
                           gr_vector_const_void_star &input_items,
                           gr_vector_void_star &output_items)
{
    return noutput_items;
}
