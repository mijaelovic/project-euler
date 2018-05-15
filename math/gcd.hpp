#pragma once

/**
 * Computes the greatest common denominator of both u and v.
 * @param u A number
 * @param v A number
 **/
uint64_t gcd(uint64_t u, uint64_t v)
{
    while (u > 0)
    {
        if (u < v)
        {
            uint64_t h = u;
            u = v;
            v = h;
        }
        u %= v;
    }
    return v;
}
