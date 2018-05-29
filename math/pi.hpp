#pragma once

#include<cmath>
#include<vector>
#include<map>
#include"eratosthenes.hpp"

class Lehmer {
private:
    uint32_t m_sqrt;
    std::vector<size_t> m_prime;

    uint64_t phi(uint64_t x, size_t a, std::map<std::pair<uint64_t, size_t>, uint64_t>& cache)
    {
        if (a == 1)
        {
            return (x + 1) / 2;
        }
        if (cache.find(std::make_pair(x, a)) != cache.end())
        {
            return cache[std::make_pair(x, a)];
        }
        uint64_t result = phi(x, a - 1, cache) - phi(x / m_prime[a - 1], a - 1, cache);
        cache[std::make_pair(x, a)] = result;
        return result;
    }

    uint64_t pi(uint64_t x, std::map<uint64_t, uint64_t>& pi_cache, std::map<std::pair<uint64_t, size_t>, uint64_t>& phi_cache)
    {
        if (x < m_sqrt)
        {
            std::vector<size_t>::iterator it = std::upper_bound(m_prime.begin(), m_prime.end(), x);
            return std::distance(m_prime.begin(), it);
        }
        if (pi_cache.find(x) != pi_cache.end())
        {
            return pi_cache[x];
        }
        uint64_t a = pi(std::pow(x, 1./4.), pi_cache, phi_cache);
        uint64_t b = pi(std::pow(x, 1./2.), pi_cache, phi_cache);
        uint64_t c = pi(std::pow(x, 1./3.), pi_cache, phi_cache);

        uint64_t result = phi(x, a, phi_cache) +  ((b + a - 2) * (b - a + 1)) / 2;
        for (uint64_t i=a+1; i<=b; ++i)
        {
            uint64_t w = x / m_prime[i - 1];
            uint64_t bi = pi(std::pow(w, 1./2.), pi_cache, phi_cache);
            result -= pi(w, pi_cache, phi_cache);
            if (i <= c)
                for (uint64_t j=i; j<=bi; ++j)
                    result -= pi(w / m_prime[j - 1], pi_cache, phi_cache) - j + 1;
        }
        pi_cache[x] = result;
        return result;
    }

public:
    Lehmer(uint64_t max_n)
    {
        m_sqrt = std::sqrt(max_n);
        Eratosthenes flag(m_sqrt);
        m_prime.push_back(2);
        for (size_t i=3; i<=m_sqrt; i+=2)
            if (flag[i])
                m_prime.push_back(i);
    }

    uint64_t pi(uint64_t x)
    {
        std::map<uint64_t, uint64_t> pi_cache;
        std::map<std::pair<uint64_t, size_t>, uint64_t> phi_cache;
        return pi(x, pi_cache, phi_cache);
    }
};
