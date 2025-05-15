#ifndef __KATO_FUNCTION_H__
#define __KATO_FUNCTION_H__

#pragma once

#include <string>
#include <ctime>
#include <vector>
#include <chrono>

#define KATO_SHORT_SLEEP_US 1000 // 0.01 s

namespace kato::function
{
    const std::string TimeStampString(const int ms = 0, const std::string &format = "%Y%m%d.%H%M%S", const char *separator = ".", const std::chrono::system_clock::time_point &time = std::chrono::system_clock::now());
    const struct timespec time_point_to_timespec(const std::chrono::system_clock::time_point &time = std::chrono::system_clock::now());
    const std::chrono::system_clock::time_point timespec_to_time_point(const struct timespec &time);
    float delta_timespec_to_framerate(const struct timespec &t1, const struct timespec &t2);
    const std::string IndexStampString(const int, const std::string &format = "%04d");
    void InterruptibleUSleep(const int, const bool skip = true);

    const std::string StringPrintf(const char *format, ...);

    template <typename T>
    const std::string VecToString(const char *format, const std::vector<T> &_values)
    {
        if (_values.empty())
            return "[]"; // Handle empty vector case
        std::string out = "[" + StringPrintf(format, _values[0]);
        for (size_t iVal = 1; iVal < _values.size(); iVal++)
            out += "," + StringPrintf(format, _values[iVal]);
        return out + "]";
    }
};

#endif //__KATO_FUNCTION_H__