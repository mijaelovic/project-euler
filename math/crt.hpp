#pragma once

#include "invmod.hpp"

/**
 * Chinese remainder theorem
 * Given pairwise coprime positive integers n1, n2,..., nk and arbitrary integers a1, a2,..., ak, the system of simultaneous congruences
 *  x = a1 (mod n1)
 *  x = a2 (mod n2)
 *  . . .
 *  x = ak (mod nk)
 * has a solution, and the solution is unique modulo N = n1 n2 ... nk.
 *
 * The following is a general construction to find a solution to a system of congruences using the Chinese remainder theorem:
 * 1. Compute N = n1 x n2 x ... x nk.
 * 2. For each i = 1, 2, ..., k compute yi = N / ni = n1 n2..ni-1 ni+1..nk.
 * 3. For each i = 1, 2, ..., k, compute zi = yi-1 mod ni (zi exists since n1, n2, ..., nk are pairwise coprime).
 * 4. The integer x = Sum{i=1 to K}{ai yi zi} is a solution to the system of congruences, and  is the unique solution modulo N.
 *
 * To see why x is a solution, for each i=1,2,..., k, we have
 *  x (mod ni) = (a1 y1 z1 + a2 y2 z2 + ... + ak yk zk) (mod ni)
 *             = ai yi zi (mod ni)  => Since yj = 0 (mod ni) for j != i
 *             = a (mod ni)         => Since yi zi = 1 (mod ni)
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
