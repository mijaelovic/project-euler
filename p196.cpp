#include<iostream>
#include<vector>
#include<algorithm>
#include "math/eratosthenes.hpp"

uint64_t s(uint64_t r)
{
    uint64_t min_n = ((r - 2)*(r - 3)) / 2 + 1;
    uint64_t max_n = ((r + 2)*(r + 3)) / 2;
    Eratosthenes primes(min_n, max_n);

    std::vector<bool> triplet(max_n - min_n + 1, false);
    for (uint64_t i=r-1; i<=r+1; ++i)
    {
        uint64_t prev_min = ((i-1)*(i-2))/2+1;
        uint64_t prev_max = (i*(i-1))/2;
        uint64_t curr_min = (i*(i-1))/2+1;
        uint64_t curr_max = (i*(i+1))/2;
        uint64_t next_min = (i*(i+1))/2 + 1;
        uint64_t next_max = ((i+1)*(i+2))/2;

        uint64_t s, t, u;
        s = prev_min;
        u = next_min;

        for (uint64_t t=curr_min; t<=curr_max; ++t)
        {
            if (primes[t])
            {
                std::vector<uint64_t> around;
                around.push_back(s);
                around.push_back(u);

                if (s > prev_min)
                    around.push_back(s - 1);
                if (s < prev_max)
                    around.push_back(s + 1);
                if (t > curr_min)
                    around.push_back(t - 1);
                if (t < curr_max)
                    around.push_back(t + 1);
                if (u > next_min)
                    around.push_back(u - 1);
                if (u < next_max)
                    around.push_back(u + 1);

                size_t around_prime = 0;
                for (size_t j=0; j<around.size(); ++j)
                    if (primes[around[j]])
                        around_prime++;

                if (around_prime >= 2)
                {
                    triplet[t - min_n] = true;
                    for (size_t j=0; j<around.size(); ++j)
                        if (primes[around[j]])
                            triplet[around[j] - min_n] = true;
                }
            }
            if (s < prev_max)
                ++s;
            if (u < next_max)
                ++u;
        }
    }

    uint64_t total = 0;
    for (uint64_t i=(r*(r-1))/2+1; i<=(r*(r+1))/2; ++i)
        if (triplet[i - min_n])
            total += i;

    return total;
}

int main()
{
    std::cout << (s(5678027) + s(7208785)) << std::endl;
    return 0;
}
