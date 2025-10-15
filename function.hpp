#ifndef __KATO_FUNCTION_HPP__
#define __KATO_FUNCTION_HPP__

#pragma once

#include <string>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <cmath>
#include <cstdarg>
#include <iterator>

#define KATO_SHORT_SLEEP_US 1000 // 0.01 s

namespace kato::function
{

    inline const std::string TimeStampString(const int ms = 0, const std::string &format = "%Y%m%d.%H%M%S", const char *separator = ".", const std::chrono::system_clock::time_point &time = std::chrono::system_clock::now())
    {
        std::time_t time_t = std::chrono::system_clock::to_time_t(time);
        std::tm tm_part = *std::localtime(&time_t);

        std::ostringstream oss;
        oss << std::put_time(&tm_part, format.c_str());
        if (ms)
        {
            std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()); // Get the total time in milliseconds since the epoch
            std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(milliseconds);
            std::chrono::milliseconds fractional_seconds = milliseconds - seconds;
            oss << separator << std::setw(ms) << std::setfill('0') << fractional_seconds.count();
        }
        return oss.str();
    }

    inline const struct timespec time_point_to_timespec(const std::chrono::system_clock::time_point &time = std::chrono::system_clock::now())
    {
        std::chrono::nanoseconds nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()); // Get the total time in nanoseconds since the epoch
        std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(nanoseconds);
        std::chrono::nanoseconds fractional_seconds = nanoseconds % std::chrono::seconds(1);

        timespec ts;
        ts.tv_sec = seconds.count();
        ts.tv_nsec = fractional_seconds.count();
        return ts;
    }

    inline const std::chrono::system_clock::time_point timespec_to_time_point(const struct timespec &time)
    {
        std::chrono::seconds sec(time.tv_sec);                           // Convert tv_sec (seconds) to std::chrono::seconds
        std::chrono::nanoseconds nsec(time.tv_nsec);                     // Convert tv_nsec (nanoseconds) to std::chrono::nanoseconds
        std::chrono::system_clock::duration total_duration = sec + nsec; // Combine seconds and nanoseconds into a duration
        return std::chrono::system_clock::time_point(total_duration);    // Create and return the time_point
    }

    inline float delta_timespec_to_framerate(const struct timespec &t1, const struct timespec &t2)
    {
        // Calculate the difference in seconds
        double startTime = t1.tv_sec + t1.tv_nsec / 1e9; // Convert to seconds
        double endTime = t2.tv_sec + t2.tv_nsec / 1e9;   // Convert to seconds
        double deltaTime = endTime - startTime;          // Time difference

        // Avoid division by zero
        if (deltaTime == 0)
            return 0.0; // Or handle error

        // Calculate frame rate
        return 1.0 / deltaTime;
    }

    inline const std::string IndexStampString(const int _index, const std::string &format = "%04d")
    {
        static char tempIndexStampString[32];
        sprintf(tempIndexStampString, format.c_str(), _index);
        return std::string(tempIndexStampString);
    }

    template <typename Duration>
    void InterruptibleSleep(const Duration &sleepTime, const bool skip = true)
    {
        std::chrono::microseconds timer_us(0);
        const std::chrono::microseconds short_sleep(KATO_SHORT_SLEEP_US);
        while (skip)
        {
            if (timer_us > std::chrono::duration_cast<std::chrono::microseconds>(sleepTime))
                break;
            std::this_thread::sleep_for(short_sleep);
            timer_us += short_sleep;
        }
    }

    inline const std::string StringPrintf(const char *format, ...)
    {
        constexpr size_t BUFFER_SIZE = 1024;
        char buffer[BUFFER_SIZE];
        va_list args;
        va_start(args, format);
        int length = std::vsnprintf(buffer, BUFFER_SIZE, format, args);
        va_end(args);
        if (length < 0)
            return "";
        return std::string(buffer);
    }

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

    inline std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        std::istringstream iss(s);
        std::string item;
        while (std::getline(iss, item, delim))
            elems.push_back(item);
        return elems;
    }

} // namespace function

#endif //__KATO_FUNCTION_HPP__