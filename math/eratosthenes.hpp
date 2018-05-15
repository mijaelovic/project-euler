#pragma once

#include<vector>
#include<cmath>

/**
 * Eratosthenes sieve.
 * The famous eratosthenes sieve. It offers two constructor:
 * 1. N, sieve from 1 to N both inclusive of prime numbers. Complexity O(n log n log n)
 * 2. MINN, MAXN: Segmented sieve from MINN to MAXN both inclusive of prime numbers.
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
