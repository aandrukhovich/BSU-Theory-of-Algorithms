#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <random>

template<typename T>
class DSU {
  public:
    DSU() : parents_(1) {
    };

    void make_set(T elem) {
        parents_.push_back(elem);
    }

    void union_sets(T first, T second) {
        if (rd_() % 2) {
            parents_[first] = second;
        } else {
            parents_[second] = first;
        }
    }

    T find_set(T elem) {
        if (parents_[elem] == elem) {
            return elem;
        }
        return parents_[elem] = find_set(parents_[elem]);
    }
  private:
    std::vector<size_t> parents_;
    std::random_device rd_;
};

std::tuple<size_t, bool, size_t> read() {
    char c;
    std::cin >> c;
    size_t x;
    std::cin >> x;

    std::string s;
    std::cin >> s;

    std::cin >> c;
    size_t y;
    std::cin >> y;
    return std::make_tuple(x, s == "==", y);
}

int main() {
    freopen("equal-not-equal.in", "r", stdin);
    freopen("equal-not-equal.out", "w", stdout);
    std::ios_base::sync_with_stdio(0);
    DSU<size_t> dsu;

    size_t n, m;
    std::cin >> n >> m;

    for (size_t i = 0; i < n; ++i) {
        dsu.make_set(i + 1);
    }

    std::vector<std::tuple<size_t, bool, size_t>> requests;

    for (size_t i = 0; i < m; ++i) {
        auto p = read();
        requests.push_back(p);
        if (std::get<1>(p)) {
            dsu.union_sets(dsu.find_set(std::get<0>(p)), dsu.find_set(std::get<2>(p)));
        }
    }

    for (auto p : requests) {
        if (std::get<1>(p) == false) {
            if (dsu.find_set(std::get<0>(p)) == dsu.find_set(std::get<2>(p))) {
                std::cout << "No";
                return 0;
            }
        }
    }
    std::cout << "Yes";
    return 0;
}