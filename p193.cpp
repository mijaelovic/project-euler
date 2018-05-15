#include <iostream>
#include "math/mobius.hpp"

int main()
{
    const int64_t MAXN = 1125899906842624L;
    const int64_t SQRT = 33554432;
    Mobius mu(SQRT);
    uint64_t total = 0;
    for (int64_t i=1; i < SQRT; ++i)
        total += mu[i] * (MAXN / (i * i));
    std::cout << total << std::endl;
    return 0;
}
