#include <iostream>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <cmath>
#include <cstdarg>

#include "kato/function.h"
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
const std::string kato::function::TimeStampString(const int ms, const std::string &format, const char *separator, const std::chrono::system_clock::time_point &time)
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
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
const struct timespec kato::function::time_point_to_timespec(const std::chrono::system_clock::time_point &time)
{
    std::chrono::nanoseconds nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(time.time_since_epoch()); // Get the total time in nanoseconds since the epoch
    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(nanoseconds);
    std::chrono::nanoseconds fractional_seconds = nanoseconds % std::chrono::seconds(1);

    timespec ts;
    ts.tv_sec = seconds.count();
    ts.tv_nsec = fractional_seconds.count();
    return ts;
}
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
float kato::function::delta_timespec_to_framerate(const struct timespec &t1, const struct timespec &t2)
{
    // Calculate the difference in seconds
    double startTime = t1.tv_sec + t1.tv_nsec / 1e9; // Convert to seconds
    double endTime = t2.tv_sec + t2.tv_nsec / 1e9;   // Convert to seconds
    double deltaTime = endTime - startTime;          // Time difference

    // Avoid division by zero
    if (deltaTime <= 0)
        return 0.0; // Or handle error

    // Calculate frame rate
    return 1.0 / deltaTime;
}
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
const std::chrono::system_clock::time_point kato::function::timespec_to_time_point(const struct timespec &time)
{
    std::chrono::seconds sec(time.tv_sec);                           // Convert tv_sec (seconds) to std::chrono::seconds
    std::chrono::nanoseconds nsec(time.tv_nsec);                     // Convert tv_nsec (nanoseconds) to std::chrono::nanoseconds
    std::chrono::system_clock::duration total_duration = sec + nsec; // Combine seconds and nanoseconds into a duration
    return std::chrono::system_clock::time_point(total_duration);    // Create and return the time_point
}
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
const std::string kato::function::IndexStampString(const int _index, const std::string &format)
{
    static char tempIndexStampString[32];
    sprintf(tempIndexStampString, format.c_str(), _index);
    return std::string(tempIndexStampString);
}
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
void kato::function::InterruptibleUSleep(const int _sleepTime_us, const bool skip)
{
    int timer_us = 0;
    while (skip)
    {
        timer_us += KATO_SHORT_SLEEP_US;
        if (timer_us > _sleepTime_us)
            break;
        usleep(KATO_SHORT_SLEEP_US);
    }
}
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
const std::string kato::function::StringPrintf(const char *format, ...)
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
// --------------------------------------------------------------------------------------------------------------------