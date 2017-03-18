#include <iostream>
#include <vector>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    size_t n, m;
    unsigned long long s;
    std::cin >> n >> m >> s;
    size_t max_sum = 101 * 101;

    std::vector<bool> a(max_sum, false);
    std::vector<bool> b(max_sum, false);
        
    a[0] = b[0] = true;

    for (size_t i = 0; i < n; ++i) {
        size_t x;
        std::cin >> x;
        for (size_t j = max_sum - 1; j >= x; --j) {
            a[j] = a[j] || a[j - x];
        }
    }
    for (size_t i = 0; i < m; ++i) {
        size_t x;
        std::cin >> x;
        for (size_t j = max_sum - 1; j >= x; --j) {
            b[j] = b[j] || b[j - x];
        }   
    }

    for (size_t i = s; i < max_sum; ++i) {
        if (a[i] && b[i - s]) {
            std::cout << "Yes";
            return 0;
        }
    }

    std::cout << "No";
    return 0;
}