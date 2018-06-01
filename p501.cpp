#include"math/pi.hpp"
#include"math/icbrt.hpp"
#include<iostream>
#include<cmath>

/**
 * The numbers of divisors of a number can be found by factorization of its number, say n = p^a q^b, the factors would be (a+1)*(b+1).
 * For the particular case of 8:
 * 2 * 2 * 2 = 8
 * 2 * 4 = 8
 * 8 = 8
 * Meaning:
 * p ^ 1 q ^ 1 r ^ 1 = N
 * p ^ 3 q ^ 1 = N
 * p ^ 7 = N
 * Now, the major problem is to to compute the first case, having p = 2, q = 3, r is maximum value of 10 ^ 12 / 6. To calculate the number of
 * prime numbers on such huge range we use Lehmer algorithm to compute pi.
 **/
int main()
{
    const uint64_t MAXN = 1000000000000L;
    const uint64_t SQRT = std::sqrt(MAXN);

    Eratosthenes flag(SQRT);
    std::vector<uint64_t> prime;
    prime.push_back(2);
    for (uint64_t i=3; i<=SQRT; i+=2)
        if (flag[i])
            prime.push_back(i);

    uint64_t total = 0;
    Lehmer pi(MAXN);
    for (size_t i=0; i < prime.size(); ++i)
        for (size_t j=i+1; j < prime.size(); ++j)
        {
            uint64_t primes = pi(MAXN / (prime[i] * prime[j]));
            if (primes <= j + 1)
                break;
            total += primes - (j + 1);
        }

    uint64_t sqrt3 = icbrt(MAXN);
    for (size_t i=0; prime[i] <= sqrt3; ++i)
    {
        uint64_t q = MAXN / (prime[i] * prime[i] * prime[i]);

        if (q <= 1)
            break;
        
        uint64_t primes = pi(q);
        if (q >= prime[i])
            --primes;

        total += primes;
    }

    total += pi(std::pow(MAXN, 1./7.));

    std::cout << total << std::endl;

    return 0;
}
