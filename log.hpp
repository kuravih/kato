#ifndef __KATO_LOG_HPP__
#define __KATO_LOG_HPP__

#pragma once

#include <iostream>
#include <sstream>

#include "kato/function.hpp"

#define KATO_BLACK "\u001b[30m"
#define KATO_RED "\u001b[31m"
#define KATO_GREEN "\u001b[32m"
#define KATO_YELLOW "\u001b[33m"
#define KATO_BLUE "\u001b[34m"
#define KATO_MAGENTA "\u001b[35m"
#define KATO_CYAN "\u001b[36m"
#define KATO_WHITE "\u001b[37m"
#define KATO_RESET "\u001b[0m"

namespace kato::log
{
    inline const char *spinner()
    {
        static uint cursor = 0;
        const char *indicator[] = {"⣼", "⣹", "⢻", "⠿", "⡟", "⣏", "⣧", "⣶"};
        constexpr unsigned int count = sizeof(indicator) / sizeof(indicator[0]);
        return indicator[(cursor++) % count];
    }

    class Logger
    {
    private:
        std::ostream &output;
        bool newLine;

    public:
        Logger(std::ostream &out) : output(out), newLine(true) {}

        template <typename T>
        Logger &operator<<(const T &value)
        {
            if (newLine)
            {
                output << "[" << kato::function::TimeStampString() << "] ";
                newLine = false;
            }
            output << value;
            return *this;
        }

        // Handle manipulators like std::endl
        Logger &operator<<(std::ostream &(*manip)(std::ostream &))
        {
            manip(output);  // Apply the manipulator (e.g., std::endl)
            newLine = true; // Mark the next line for prefixing
            return *this;
        }
    };

    inline Logger cout(std::cout);
    inline Logger cerr(std::cerr);
} // namespace log

#endif //__KATO_LOG_HPP__