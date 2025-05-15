#ifndef __KATO_FUNCTION_GST_ADDONS_H__
#define __KATO_FUNCTION_GST_ADDONS_H__

#pragma once

#include <chrono>
#include <gst/gst.h>

namespace kato::function
{
    const std::chrono::system_clock::time_point TimeStamp(const GstClockTime &);
}

// pkg-config --cflags --libs gstreamer-1.0

#endif //__KATO_FUNCTION_GST_ADDONS_H__