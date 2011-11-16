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
#ifndef PA_DEVICE_LIST_H
#define PA_DEVICE_LIST_H
#include <string>
#include <vector>
#include <pulse/pulseaudio.h>

using namespace std;

/*! \brief Simple class to represent pulseaudio devices.
 *
 * This class represents a pulseaudio device. The device can be either source
 * or sink, this class does not differentiate between them.
 */
class PaDevice
{
public:
    PaDevice(unsigned int idx=0, string name="", string desc="");
    ~PaDevice();

    void set_index(unsigned int idx) { d_index = idx; }
    void set_name(string name) { d_name = name; }
    void set_description(string desc) { d_description = desc; }

    unsigned int get_index() { return d_index; }
    string  get_name()  { return d_name; }
    string  get_description() { return d_description; }

private:
    unsigned int d_index;    /*! The index of the audio device (unique for each source/sink). */
    string  d_name;          /*! The name of the audio device. Used when creating souces/sinks. */
    string  d_description;   /*! The description of the audio device. */
};


/*! \brief Class for storing and retrieving a list of pulseaudio sinks and sources. */
class PaDeviceList
{
public:
    PaDeviceList();
    ~PaDeviceList();

private:
    vector<PaDevice> d_sources;   /*! List of pulseaudio sources. */
    vector<PaDevice> d_sinks;  /*! List of pulseaudio sinks. */

    int populate_device_list();

    // pulseaudio callbacks
    static void pa_state_cb(pa_context *c, void *userdata);
    static void pa_sinklist_cb(pa_context *ctx, const pa_sink_info *info, int eol, void *userdata);
    static void pa_sourcelist_cb(pa_context *ctx, const pa_source_info *info, int eol, void *userdata);
};

#endif // PA_DEVICE_LIST_H