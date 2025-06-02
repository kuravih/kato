#ifndef __KATO_FUNCTION_GST_ADDONS_HPP__
#define __KATO_FUNCTION_GST_ADDONS_HPP__

#pragma once

#include <chrono>
#include <gst/gst.h>

namespace kato::function
{
    inline const std::chrono::system_clock::time_point TimeStamp(const GstClockTime &_gstClockTime)
    {
        std::chrono::nanoseconds ns(_gstClockTime);             // Convert GstClockTime (nanoseconds) to std::chrono::nanoseconds
        auto epoch = std::chrono::system_clock::from_time_t(0); // Get the system clock time at the epoch
        return epoch + ns;                                      // Add the nanoseconds duration to the epoch to get the desired time_point
    }
}

// pkg-config --cflags --libs gstreamer-1.0

#endif //__KATO_FUNCTION_GST_ADDONS_HPP__