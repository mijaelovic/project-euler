#include<iostream>
#include<vector>

/**
 * Reuse the dynamic programming of 114. Add an exit condition.
 * Will find solution in linear time.
 **/
int bigger(int m, int n, uint64_t limit) {
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
        if (count[i][RED] + count[i][GRAY] > limit) {
            return i;
        }
    }
    return 0;
}

int main() {
    std::cout << bigger(50, 1000, 1000000) << std::endl;
    return 0;
}
