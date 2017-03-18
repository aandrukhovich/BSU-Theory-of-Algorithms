#include <iostream>
#include <vector>

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    size_t n;
    std::cin >> n;
    n++;
    std::vector<unsigned long long> a(n), b(n), c(n), d(n), e(n), f(n);


    a[0] = 1;
    b[0] = c[0] = d[0] = e[0] = f[0] = 0;

    for (size_t i = 1; i < n; ++i) {
        a[i] = f[i - 1];
        b[i] = a[i - 1] + d[i - 1];
        c[i] = a[i - 1] + e[i - 1];
        d[i] = 2 * b[i - 1];
        e[i] = 2 * c[i - 1];
        f[i] = 3 * a[i - 1] + b[i] + c[i];

    }

    std::cout << a[n - 1];

    // std::cout << "\na : \n";
    // for (auto i : a) {
    //     std::cout << i << " ";
    // }

    // std::cout << "\nb : \n";
    // for (auto i : b) {
    //     std::cout << i << " ";
    // }

    // std::cout << "\nc : \n";
    // for (auto i : c) {
    //     std::cout << i << " ";
    // }

    // std::cout << "\nd : \n";
    // for (auto i : d) {
    //     std::cout << i << " ";
    // }

    // std::cout << "\ne : \n";
    // for (auto i : e) {
    //     std::cout << i << " ";
    // }

    // std::cout << "\nf : \n";
    // for (auto i : f) {
    //     std::cout << i << " ";
    // }


    return 0;
}