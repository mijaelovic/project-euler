#pragma once

#include "invmod.hpp"

/**
 * Chinese remainder theorem
 * Given pairwise coprime positive integers n1, n2,..., nk and arbitrary integers a1, a2,..., ak, the system of simultaneous congruences
 * x = a1 (mod n1)
 * x = a2 (mod n2)
 * . . .
 * x = ak (mod nk)
 * has a solution, and the solution is unique modulo N = n1 n2 ... nk.
 **/
uint64_t crt(const std::vector<uint64_t>& a, const std::vector<uint64_t>& n)
{
    uint64_t N = 1;
    for (size_t i=0; i<n.size(); ++i)
        N *= n[i];

    int64_t x = 0;
    for (size_t i=0; i<n.size(); ++i)
    {
        int64_t y = N / n[i];
        int64_t z = invmod(y, n[i]);
        x += (a[i] * y * z);
    }

    if (x < 0)
        x += N;

    return x % N;
}
