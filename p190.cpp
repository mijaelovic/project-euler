#include<iostream>
#include<cmath>

/**
 * Let Sm = (x1, x2, ... , xm) be the m-tuple of positive real numbers with x1 + x2 + ... + xm = m for which Pm = x1^1 * x2^2 * ... * xm^m is maximised.
 * For example, it can be verified that [P10] = 4112 ([ ] is the integer part function).
 * Find Σ[Pm] for 2 ≤ m ≤ 15.
 *
 * Solution:
 * Using Lagrange multiplier, we have for m = 2.
 * f(x1, x2) = x1 * x2 ^ 2
 * g(x1, x2) = x1 + x2 - 2
 * L(x1, x2, λ) = x1 * x2 ^ 2 - λ*(x1 + x2 - 2)
 * ∇ L(x1, x2, λ) = (x2^2 - λ, 2*x1*x2 - λ, x1 + x2 - 2)
 * 1) x2^2 - λ = 0
 * 2) 2*x1*x2 - λ = 0
 * 3) x1 + x2 - 2 = 0
 * Plugin 1 and 2:
 * x2 = 2*x1
 * Solving using 3:
 * x1 = 2/3, x2 = 4/3
 *
 * For m = 3
 * L(x1, x2, λ) = x1 * x2^2*x3^3 - λ*(x1 + x2 + x3 - 3)
 * ∇L(x1, x2, λ) = (x2^2*x3^3 - λ, 2*x1*x2*x3^3 - λ, 3*x1*x2^2*x3^2 - λ, x1 + x2 + x3 - 3)
 * 1) x2^2*x3^3 - λ = 0
 * 2) 2*x1*x2*x3^3 - λ = 0
 * 3) 3*x1*x2^2*x3^2 - λ = 0
 * 4) x1 + x2 + x3 - 3 = 0
 * By mixing 1 and 2:
 * x2 = 2*x1
 * By mixing 1 and 3:
 * x3 = 3*x1
 * By mixing 2 and 3:
 * 2*x3 = 3*x2
 * Pluging for x1:
 * x1  + x2 + x3 = 3
 * x1 + 2*x1 + 3*x1 = 3
 * x1 * (1 + 2 + 3) = 3
 * x1 = 3 / 6
 * Solving for x2:
 * x2 = 1 = 6/6
 * Solving for x3:
 * x3 = 9 / 6
 * In general, for m
 * x1 = 1 * m / (m * (m + 1) / 2)
 * x2 = 2 * m / (m * (m + 1) / 2)
 * .. And so on.
 **/
int main()
{
    uint64_t total = 0;
    for (int m=2; m<=15; ++m)
    {
        double den = (m * (m + 1)) / 2;
        double p = 1;
        for (int i=1; i<=m; ++i)
            p *= std::pow( (i * m) / den, i);
        std::cout << p << std::endl;
        total += p;
    }
    std::cout << total << std::endl;
    return 0;
}
