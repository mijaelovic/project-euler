#pragma once

#include<vector>

/**
 * Mobius sieve
 **/
class Mobius {
private:
    std::vector<int32_t> mu;
public:
    Mobius(size_t n) : mu(n+1, -1)
    {
        mu[1] = 1;
        for (size_t i=2; i<=n; ++i)
            if (mu[i] != 0)
                for (size_t j=2*i; j<=n; j+=i)
                    mu[j] -= mu[i];
    }
    int operator[](size_t idx) const {
        return mu[idx];    
    }
};
