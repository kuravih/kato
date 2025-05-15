#ifndef __KATO_SERIALLINK_H__
#define __KATO_SERIALLINK_H__

#pragma once

#include "kato/log.h"

#include <stdint.h>
#include <unordered_map>
#include <functional> // for std::function
#include <termios.h>

namespace kato
{
    // Define the orders that can be sent and received
    enum class _order : uint8_t
    {
        HELLO = 0,
        ALREADY_CONNECTED = 1,
        SCAN = 2,
        READ = 3,
        START = 4,
        STOP = 5,
        ERROR = 255,
    };
    typedef enum _order order_t;

    class SerialLink
    {
    private:
        speed_t m_baudrate;
        std::function<void()> m_error_callback;

    public:
        int fd = -1;
        bool is_connected;
        SerialLink(const char *, const speed_t, std::function<void()>);
        ~SerialLink();
        int configure();
        bool is_data_available();
        // ------------------------------------------------------------------------------------------------------------
        void write_object(const void *, const size_t);
        void write_order(const order_t);
        void write_uint8(const uint8_t);
        void write_uint64(const uint64_t);
        // ------------------------------------------------------------------------------------------------------------
        void read_object(void *, const size_t);
        order_t read_order();
        uint8_t read_uint8();
        uint64_t read_uint64();
        // ------------------------------------------------------------------------------------------------------------
        void read_and_respond();
    };
}
#endif //__KATO_SERIALLINK_H__
