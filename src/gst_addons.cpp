#include "kato/gst_addons.h"
// --------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
const std::chrono::system_clock::time_point kato::function::TimeStamp(const GstClockTime &_gstClockTime)
{
    std::chrono::nanoseconds ns(_gstClockTime);             // Convert GstClockTime (nanoseconds) to std::chrono::nanoseconds
    auto epoch = std::chrono::system_clock::from_time_t(0); // Get the system clock time at the epoch
    return epoch + ns;                                      // Add the nanoseconds duration to the epoch to get the desired time_point
}
// --------------------------------------------------------------------------------------------------------------------
