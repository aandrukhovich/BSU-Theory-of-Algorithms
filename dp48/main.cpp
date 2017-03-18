#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>



std::vector<std::vector<size_t>> e;

std::vector<bool> used;
std::vector<size_t> yes;
std::vector<size_t> no;

void dfs(size_t first = 1) {
    std::stack<std::pair<size_t, size_t>> s;
    s.push(std::make_pair(first, 0));
    used[first] = true;
    while (!s.empty()) {
        auto temp = s.top();
        size_t v = temp.first, i = temp.second;
        if (i > 0) {
            no[v] += yes[e[v][i - 1]];
            yes[v] += std::min(no[e[v][i - 1]], yes[e[v][i - 1]]);
        }
        if (i == e[v].size()) {
            yes[v] += 1;
            s.pop();
            continue;
        }
        s.pop();
        s.push(std::make_pair(v, i + 1));
        if (!used[e[v][i]]) {
            used[e[v][i]] = true;
            s.push(std::make_pair(e[v][i], 0));
        }
    }  
}

size_t ans = 0;
void answer(size_t first = 1) {

    std::stack<std::tuple<size_t, size_t, size_t>> s;
    used[first] = false;
    s.push(std::make_tuple(first, 0, 0));

    while (!s.empty()) {
        auto temp = s.top();
        size_t v, i, color;
        std::tie(v, i, color) = temp;

        if (i == 0) {
            if (yes[v] < no[v]) {
                color = 1;
            }
            ans += color;
        }

        if (i == e[v].size()) {
            s.pop();
            continue;
        }
        s.pop();
        s.push(std::make_tuple(v, i + 1, color));
        if (used[e[v][i]]) {
            used[e[v][i]] = false;
            s.push(std::make_tuple(e[v][i], 0, color ^ 1));
        }
    } 
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    size_t n;
    std::cin >> n;
    e.resize(n + 1);
    yes.resize(n + 1, 0);
    no.resize(n + 1, 0);
    used.resize(n + 1, false);

    for (size_t i = 1; i <= n; ++i) {
        size_t cnt;
        std::cin >> cnt;
        e[i].resize(cnt);
        for (size_t j = 0; j < cnt; ++j) {
            std::cin >> e[i][j];
        }
    }

    dfs();
    answer();

    // std::cerr <<"\nyes\n";
    // for (auto i : yes) {
    //     std::cerr << i << " ";
    // }

    // std::cerr <<"\nno\n";
    // for (auto i : no) {
    //     std::cerr << i << " ";
    // }

    std::cout << ans;
    return 0;
}