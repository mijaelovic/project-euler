#pragma once

#include<vector>
#include<cmath>
#include<map>
#include "mobius.hpp"

/**
 * Mertens function is the cumulative function of Mobius:
 *  M(x) = \sum_{i = 1}^{x} μ(i)
 * By applying the Mobius inversion formula we can get a recursion for the Mertens function:
 *  M(x) = 1 - \sum{d >= 2} M(x/d)
 * Here, an important observation is that having all values M(x/d) for d >= 2, we are able to calculate M(x) in time O(Sqrt(x)). 
 * This is because there are at most 2 sqrt(x) different integers of the form ceil(x/d), since x/d < sqrt(x) for d > sqrt(x).
 **/
class Mertens {
private:
    size_t SQRT;
    std::vector<int64_t> M;

    int64_t calculate(int64_t n, std::map<int64_t, int64_t>& cache)
    {
        if (n <= SQRT)
            return M[n];
        if (cache.find(n) != cache.end())
            return cache[n];
        const size_t NSQRT = std::sqrt(n);
        int64_t total, a, b;
        total = 0;
        {
            a = n;
            b = n / 2;
            if (b >= NSQRT)
                total += M[1] * (a - b);
        }
        for (size_t k=2; k<=NSQRT; ++k)
        {
            a = n / k;
            b = n / (k + 1);
            total += calculate(a, cache);
            if (b >= NSQRT)
                total += M[k] * (a - b);
        }
        cache[n] = 1 - total;
        return cache[n];
    }
public:
    Mertens(const uint64_t MAXN)
    {
        SQRT = std::sqrt(MAXN);
        Mobius miu(SQRT);

        M.resize(SQRT + 1, 0);
        for (size_t i=1; i<=SQRT; ++i)
            M[i] = M[i-1] + miu[i];
    }

    int64_t operator[](int64_t idx)
    {
        std::map<int64_t, int64_t> cache;
        return calculate(idx, cache);       
    }
};
