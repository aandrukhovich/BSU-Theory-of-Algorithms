#include <iostream>
#include <vector>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    size_t n, m;
    std::cin >> n >> m;
    std::vector<unsigned long long > a(n + 1, 0);
    std::vector<unsigned long long > sum(n + 1, 0);
    std::vector<std::vector<unsigned long long >> psum(n + 1,
            std::vector<unsigned long long >(n + 1, 0));

    for (size_t i = 1; i <= n; ++i) {
        std::cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        for (size_t l = 1; l < i; ++l) {
            psum[l][i] = a[i] * (sum[i - 1] - sum[l - 1]) + psum[l][i - 1];
        }
    }

    std::vector<std::vector<unsigned long long >> f(n + 1,
            std::vector<unsigned long long >(m + 2, 0));
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m + 1; ++j) {
            if (j == 1) {
                f[i][j] = psum[1][i];
            } else {
                unsigned long long temp = 2e9;
                for (size_t k = 1; k < i; ++k) {
                    temp = std::min(temp, f[k][j - 1] + psum[k + 1][i]);
                }
                f[i][j] = temp;
            }
        }
    }
    unsigned long long answer = 2e9;
    for (size_t i = 1; i <= m + 1; ++i) {
        answer = std::min(answer, f[n][i]);
    }

    std::cout << answer;
    return 0;
}