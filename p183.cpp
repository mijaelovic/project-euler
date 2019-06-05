#include<iostream>
#include<cmath>
#include "math/terdecimal.hpp"

/**
 * The maximum product of parts is reached when N / k == e == 2.78...
 **/
int main() {
    const int N = 10000;
    const double E = std::exp(1);
    int64_t total = 0;
    for (int i=5; i<=N; ++i) {
        int parts = std::round( i / E );
        if (terdecimal(i, parts))
            total -= i;
        else
            total += i;
    }
    std::cout << total << std::endl;
    return 0;
}
