#pragma once

#include "gcd.hpp"

/**
 * Returns true if the fraction is decimal terminating.
 * A fraction that can be expressed as P/2^u 5^v is decimal terminating.
 * @param num The numerator
 * @param den The denominator
 * @return true if the fraction is decimal terminating, false otherwise. 
 **/
bool terdecimal(uint64_t num, uint64_t den) {
    uint64_t d = gcd(num, den);
    den /= d;
    while (den % 2 == 0)
        den /= 2;
    while (den % 5 == 0)
        den /= 5;
    return den == 1;
}
