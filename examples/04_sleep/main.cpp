#include "kato/function.h"

int main()
{
    kato::function::InterruptibleSleep(std::chrono::seconds(10));
    return 0;
}