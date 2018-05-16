#include "math/bigint.hpp"
#include "math/mobius.hpp"
#include "math/mertens.hpp"

/**
 * Problem:
 * Consider all lattice points (a,b,c) with 0 ≤ a,b,c ≤ N.
 * From the origin O(0,0,0) all lines are drawn to the other lattice points.
 * Let D(N) be the number of distinct such lines.
 * 
 * Solution:
 * Let O = (0, 0, 0). Two equal lines can be O -> P(k, k, k) and O -> Q(2k, 2k, 2k).
 * Meaning that if Q is a "multiple" of P, Q must be discarded.
 *
 * We can think now that we count all lattice points, N^3, discard of multiples of 2, (N/2)^3, discard multiples of 3, (N/3)^3, 
 * add multiples of 6 (N/6)^3 and so on... We will end up couting unique lattice points, i.e. gcd(X, Y, Z) = 1. 
 * This can be basically be done with Mobius. Unfortunately for this problem N is too big to do a mindless Mobius sieve.
 *
 * As any (N/d) integer summation this can be done in sqrt(N) operations. For d < sqrt(N) we can use a Mobius sieve, for d > sqrt(N)
 * we can use Mertens (i.e. Mobius cumulative sum). Now all the must be done is compute Mertens in fast time, like in sqrt(N) operations.
 **/
int main()
{
    const uint64_t MAXN = 10000000000L;
    const uint32_t SQRT = 100000;

    Mobius miu(SQRT);
    Mertens M(MAXN);

    bigint_t total = 0;
    for (uint32_t k=1; k<=SQRT; ++k) {
        uint64_t a = MAXN / k;
        uint64_t b = MAXN / (k + 1);
        total += bigint_t(a) * a * a * miu[k];
        if (b >= SQRT)
            total += bigint_t(k) * k * k * (M[a] - M[b]);
    }

    for (uint32_t k=1; k<=SQRT; ++k) {
        uint64_t a = MAXN / k;
        uint64_t b = MAXN / (k + 1);
        total += bigint_t(a) * a * 3 * miu[k];
        if (b >= SQRT)
            total += bigint_t(k) * k * 3 * (M[a] - M[b]);
    }

    total += 3;
    std::cout << total << std::endl;
    return 0;
}
