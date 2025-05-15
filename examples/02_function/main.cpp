#include "kato/log.h"
#include "kato/function.h"

int main(int argc, char const *argv[])
{

    (void)argc;
    (void)argv;

    kato::log::cout << "StringPrintf : " << kato::function::StringPrintf("%f", 314.15926535) << std::endl;
    kato::log::cout << "StringPrintf : " << kato::function::StringPrintf("%+09.4f", 31.415926535) << std::endl;
    kato::log::cout << "StringPrintf : " << kato::function::StringPrintf("0X%016llX", 0x0123456789ABCDEF) << std::endl;

    std::vector<unsigned int> uintVec = {1, 2, 3, 42, 100};
    std::vector<double> doubleVec = {3.1415, 2.718, 1.414};

    kato::log::cout << "StringPrintf : " << kato::function::VecToString("%03u", uintVec) << std::endl;     // Output: [1,2,3,42,100]
    kato::log::cout << "StringPrintf : " << kato::function::VecToString("%+06.2f", doubleVec) << std::endl; // Output: [3.14,2.72,1.41]

    return 0;
}