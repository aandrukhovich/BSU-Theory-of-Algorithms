#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm>


int main() {

    std::ifstream in("in.txt");
    std::ofstream out("out.txt");

    size_t n;
    in >> n;

    std::vector<std::vector<int>> edges(n);

    for (size_t i = 0; i < n; ++i) {
        size_t s;
        in >> s;
        edges[i].resize(s);
        for (size_t j = 0; j < s; ++j) {
            in >> edges[i][j];
            edges[i][j]--;
        }
    }

    int ans = -1;
    int ansv = -1;

    for (size_t i = 0; i < n; ++i) {
        std::queue<int> q;
        q.push(i);
        std::vector<int> used(n, 1e9);
        used[i] = 0;    

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (const auto& u : edges[v]) {
                if (used[u] > used[v] + 1) {
                    q.push(u);
                    used[u] = used[v] + 1;
                }
            }
        }
        int mx = -1;
        for (const auto& d : used) {
            mx = std::max(d, mx);
        }

        if (mx != 1e9 && mx >= ans) {
            ans = mx;
            ansv = i + 1;
        }
    }


    if (ans == -1) {
        out << "impossible";
    } else {
        out << ans << '\n' << ansv;
    }

    return 0;
}