#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm>


int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t n, m;
    in >> n >> m;

    std::vector<bool> used(n, false);
    std::vector<std::vector<int>> edges(n);

    for (size_t i = 0; i < m; ++i) {
        int x, y;
        in >> x >> y;
        x--, y--;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    int answer = 0;
    for (size_t i = 0; i < n; ++i)  {
        if (!used[i]) {
            std::queue<int> q;
            q.push(i);
            answer ++;

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (const auto& u : edges[v]) {
                    if (!used[u]) {
                        used[u] = true;
                        q.push(u);
                    }
                }

            }

        }
    }

    out << answer - 1;

    return 0;
}