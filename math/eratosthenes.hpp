#pragma once

#include<vector>
#include<cmath>

/**
 * Eratosthenes sieve.
 * Sieve of Eratosthenes is a simple and ancient algorithm used to find the prime numbers up to any given limit. 
 * It is one of the most efficient ways to find small prime numbers.
 * For a given upper limit  the algorithm works by iteratively marking the multiples of primes as composite, starting from 2. 
 * Once all multiples of 2 have been marked composite, the muliples of next prime, ie 3 are marked composite. 
 * This process continues until p <= sqrt(N)  where p is a prime number.
 * 
 * This implementation offers the traditional sieve in O(N log N log N) and the segmented sieve in O(sqrt(N)).
 **/
class Eratosthenes {
private:
    uint64_t offset;
    std::vector<bool> flag;
public:
    Eratosthenes(size_t n) : 
        offset(0), flag(n + 1, true)
    {
        const size_t SQRT = std::sqrt(n);
        flag[1] = false;
        for (size_t i=2; i<=SQRT; ++i)
            if (flag[i])
                for (size_t j=i*i; j<=n; j+=i)
                    flag[j] = false;
    }

    Eratosthenes(uint64_t min_n, uint64_t max_n) : 
        offset(min_n), flag(max_n - min_n + 1, true)
    {
        const size_t SQRT = std::sqrt(max_n);
        Eratosthenes primes(SQRT);

        for (size_t i=2; i<=SQRT; ++i)
            if (primes[i])
            {
                uint64_t j = (min_n / i) * i;
                while (j < min_n)
                    j += i;
                for (; j<=max_n; j+=i)
                    flag[j - min_n] = false;
            }
    }

    bool operator[](size_t idx) const {
        return flag[idx - offset];
    }
};
