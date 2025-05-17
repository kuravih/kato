#include "kato/log.h"
#include "kato/function.h"
#include "kato/CCfits_addons.h"

int main()
{
    kato::log::cout << kato::function::CCfitsTypeToString(FLOAT_IMG) << std::endl;
    return 0;
}