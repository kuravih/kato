#include "kato/serial_link.h"

#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

kato::SerialLink::SerialLink(const char *_port, const speed_t _baudrate, std::function<void()> _error_callback) : m_baudrate(_baudrate), m_error_callback(_error_callback), is_connected(false)
{
    fd = open(_port, O_RDWR | O_NOCTTY);
    if (fd == -1)
    {
        kato::log::cout << KATO_RED << "Error opening serial port." << KATO_RESET << std::endl;
        exit(1);
    }
    if (configure() != 0)
    {
        close(fd);
        exit(1);
    }
}

kato::SerialLink::~SerialLink()
{
    close(fd);
}

int kato::SerialLink::configure()
{
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0)
    {
        kato::log::cout << KATO_RED << "Error getting attributes." << KATO_RESET << std::endl;
        return -1;
    }

    cfsetospeed(&tty, m_baudrate); // Set output baud rate
    cfsetispeed(&tty, m_baudrate); // Set input baud rate

    tty.c_cflag &= ~PARENB; // No parity
    tty.c_cflag &= ~CSTOPB; // One stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;            // 8 data bits
    tty.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem control lines

    tty.c_lflag &= ~ICANON; // Set raw mode
    tty.c_lflag &= ~(ECHO | ECHOE | ISIG);

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable flow control
    tty.c_iflag &= ~(ICRNL | INLCR | IGNCR);

    tty.c_oflag &= ~OPOST; // Disable output processing

    tcflush(fd, TCIFLUSH);

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        kato::log::cout << KATO_RED << "Error setting attributes." << KATO_RESET << std::endl;
        return -1;
    }
    return 0;
}

bool kato::SerialLink::is_data_available()
{
    int bytesAvailable;
    ioctl(fd, FIONREAD, &bytesAvailable);
    return bytesAvailable > 0;
}

void kato::SerialLink::read_and_respond()
{
    if (is_data_available())
    {
        order_t order = read_order(); // The first byte received is the instruction
        if (order == kato::order_t::HELLO)
        {
            // kato::log::cout << KATO_BLUE << "RX [HELLO]" << KATO_RESET << std::endl;
            if (!is_connected) // If the cards haven't say hello, check the connection
            {
                is_connected = true;
                write_order(kato::order_t::HELLO);
                // kato::log::cout << KATO_BLUE << "TX [HELLO]" << KATO_RESET << std::endl;
            }
            else
            {
                write_order(kato::order_t::ALREADY_CONNECTED); // If we are already connected do not send "hello" to avoid infinite loop
                // kato::log::cout << KATO_BLUE << "TX [ALREADY_CONNECTED]" << KATO_RESET << std::endl;
            }
        }
        else if (order == kato::order_t::ALREADY_CONNECTED)
        {
            // kato::log::cout << KATO_BLUE << "RX [ALREADY_CONNECTED]" << KATO_RESET << std::endl;
            is_connected = true;
        }
    }
}
// --------------------------------------------------------------------------------------------------------------------
void kato::SerialLink::write_object(const void *_object, const size_t _size)
{
    write(fd, _object, _size);
}
void kato::SerialLink::write_order(const kato::order_t _order)
{
    write_uint8((uint8_t)_order);
}
void kato::SerialLink::write_uint8(const uint8_t _value)
{
    write_object(&_value, sizeof(uint8_t));
}
void kato::SerialLink::write_uint64(const uint64_t _value)
{
    write_object(&_value, sizeof(uint64_t));
}
// --------------------------------------------------------------------------------------------------------------------
void kato::SerialLink::read_object(void *_object, const size_t _size)
{
    read(fd, _object, _size);
}
kato::order_t kato::SerialLink::read_order()
{
    return (kato::order_t)read_uint8();
}
uint8_t kato::SerialLink::read_uint8()
{
    uint8_t value;
    read_object(&value, sizeof(uint8_t));
    return value;
}
uint64_t kato::SerialLink::read_uint64()
{
    uint64_t value;
    read_object(&value, sizeof(uint64_t));
    return value;
}
// --------------------------------------------------------------------------------------------------------------------
