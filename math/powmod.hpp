#pragma once

/**
 * Computes a ^ b (mod n) in O(log b) time.
 * @param a The base.
 * @param b The exponent.
 * @param n The modulo base.
 **/
uint64_t powmod(int64_t a, int64_t b, int64_t n)
{
    if (b == 0)
        return 1 % n;
    if (b == 1)
        return a % n;

    uint64_t half = powmod(a, b/2, n);
    uint64_t total = (half * half) % n;
    if (b % 2 == 0)
        return total;
    else
        return (total * a) % n;
}
