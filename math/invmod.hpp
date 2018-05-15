#pragma once

/**
 * Calculate the modular inverse.
 * @param a The number to calculate the inverse.
 * @param n The modulo base
 * @return The modulo inverse or 0 if it does not exist.
 **/
uint64_t invmod(uint64_t a, uint64_t n)
{
    int64_t t = 0;
    int64_t r = n;
    int64_t newt = 1;
    int64_t newr = a;
    int64_t u;
    int64_t v;

    while (newr != 0)
    {
        int64_t q = r / newr;

        u = newt;
        v = t - q * newt;
        t = u;
        newt = v;

        u = newr;
        v = r - q * newr;
        r = u;
        newr = v;
    }
    if (r > 1)
        return 0; // no inverse
    if (t < 0)
        t += n;
    return t;
}
