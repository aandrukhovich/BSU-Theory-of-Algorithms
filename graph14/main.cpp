#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm>


int main() {

    std::ifstream in("input.in");
    std::ofstream out("output.out");

    size_t n, m;
    in >> n >> m;

    std::vector<int> from(m);
    std::vector<int> to(m);
    std::vector<long long> cost(m);


    std::vector<std::vector<size_t>> own_edges(n);
    std::vector<std::vector<size_t>> own_redges(n);

    for (size_t i = 0; i < m; ++i) {
        in >> from[i] >> to[i] >> cost[i];
        from[i]--;
        to[i]--;

        own_edges[from[i]].push_back(i);
        own_redges[to[i]].push_back(i);
    }

    int start, finish;
    in >> start >> finish;
    start--;
    finish--;

    std::vector<long long> dist(n, 1e9);
    dist[start] = 0;

    std::vector<bool> used(n, false);

    std::priority_queue<std::pair<long long, int>,
        std::vector<std::pair<long long, int>>,
        std::greater<std::pair<long long, int>>> pq;
    pq.push(std::make_pair(0, start));

    std::vector<size_t> parent(n);
    parent[start] = 0;

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int vertex = top.second;

        if (used[vertex]) {
            continue;
        }

        used[vertex] = true;

        for (const auto& edge : own_edges[vertex]) {
            if (dist[to[edge]] > dist[vertex] + cost[edge]) {
                dist[to[edge]] = dist[vertex] + cost[edge];
                pq.push(std::make_pair(dist[to[edge]], to[edge]));
                parent[to[edge]] = edge;
            }
        }
    }

    int vertex = finish;
    long long second_path = 1e18;
    long long dist_from_finish = 0;
    int left_vertex = -1, right_vertex = -1;

    while (true) {
        for (const auto& edge : own_redges[vertex]) {
            if (edge == parent[vertex]) {
                continue;
            }

            if (second_path > dist[from[edge]] + cost[edge] + dist_from_finish) {
                second_path = dist[from[edge]] + cost[edge] + dist_from_finish;
                left_vertex = from[edge];
                right_vertex = to[edge];
            }
        }
        dist_from_finish += cost[parent[vertex]];
        if (vertex == start) {
            break;
        }
        vertex = from[parent[vertex]];
    }

    std::vector<int> answer;
    vertex = finish;
    bool jump = false;

    while (vertex != start || !jump) {
        answer.push_back(vertex);
        if (vertex == right_vertex && !jump) {
            vertex = left_vertex;
            jump = true;
        } else {
            vertex = from[parent[vertex]];
        }
    }
    answer.push_back(start);
    std::reverse(answer.begin(), answer.end());

    out << second_path << std::endl;

    for (size_t i = 0; i < answer.size() - 1; ++i) {
        out << answer[i] + 1 << ' ';
    }
    out << answer.back() + 1;

    return 0;
}