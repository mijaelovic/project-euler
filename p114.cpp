#include<iostream>
#include<vector>

/**
 * Dynamic programming:
 * ways of N blocks ending at gray = ways of N - 1 blocks ending at red (we add gray at end) + 
 *                                   ways of N - 1 blocks ending at gray (we add extra gray)
 * ways of N blocks ending at red = ways of K block ending at gray (we add red at end), 0 <= K <= N - M
 * The last condition is basically a cumulative sum of grays from 0 <= K <= N - M, we can reuse this sum for the next step 
 * and add the differential making our algorithm effectively linear.
 **/
uint64_t f(int m, int n) {
    const int GRAY = 0;
    const int RED = 1;
    std::vector<std::vector<uint64_t>> count(n + 1, std::vector<uint64_t>(2, 0));
    for (int i=0; i < m; ++i) {
        count[i][RED] = 0;
        count[i][GRAY] = 1;
    }
    count[m][RED] = 1;
    count[m][GRAY] = 1;
    for (int i = m + 1; i <= n; ++i) {
        count[i][RED] = count[i - 1][RED] + count[i - m][GRAY];
        count[i][GRAY] = count[i - 1][RED] + count[i - 1][GRAY];
    }
    return count[n][RED] + count[n][GRAY];
}

int main() {
    std::cout << f(3, 50) << std::endl;
    return 0;
}
