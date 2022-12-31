#include "Settlement.h"

bool Settlement::operator==(const Settlement& settlement1, const Settlement& settlement2)
{
    return (settlement1.getName() == settlement2.getName());
}
