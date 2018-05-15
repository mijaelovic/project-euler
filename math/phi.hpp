#pragma once

/**
 * Calculate the Euler PHI function.
 * @param n The number to compute
 * @return the PHI of n.
 **/
uint64_t phi(uint64_t n)
{
    uint64_t ret = 1;
    uint64_t num = n;
    for (uint64_t i=2; i*i <= n; ++i)
        if (num % i == 0)
        {
            uint64_t pow = 1;
            while (num % i == 0)
            {
                num /= i;
                pow *= i;
            }
            ret *= (pow - pow/i);
        }
    if (num != 1)
        ret *= (num - 1);
    return ret;
}
