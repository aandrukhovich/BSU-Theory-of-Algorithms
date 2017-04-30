#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm>


int main() {

    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t n, m, start;
    in >> n >> m >> start;

    std::vector<int> from;
    std::vector<int> to;
    std::vector<long long> cost;


    std::vector<std::vector<size_t>> own_edges(n);
    std::vector<std::vector<size_t>> own_redges(n);

    for (size_t i = 0; i < m; ++i) {
        int x, y;
        long long z;
        in >> x >> y >> z;

        from.push_back(x);
        to.push_back(y);
        cost.push_back(z);
        own_edges[from.back()].push_back(from.size() - 1);

        from.push_back(y);
        to.push_back(x);
        cost.push_back(z);
        own_edges[from.back()].push_back(from.size() - 1);

    }


    std::vector<long long> dist(n, 2009000999);
    dist[start] = 0;

    std::vector<bool> used(n, false);

    std::priority_queue<std::pair<long long, int>,
        std::vector<std::pair<long long, int>>,
        std::greater<std::pair<long long, int>>> pq;
    pq.push(std::make_pair(0, start));


    std::vector<size_t> parent(n);
    parent[start] = start;

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

    for (const auto& d : dist) {
        out << d << ' ';
    }
    return 0;


    // int vertex = finish;
    // long long second_path = 1e18;
    // long long dist_from_finish = 0;
    // int left_vertex = -1, right_vertex = -1; 


    // while (true) {
    //     for (const auto& edge : own_redges[vertex]) {
    //         if (edge == parent[vertex]) {
    //             continue;
    //         }

    //         if (second_path > dist[from[edge]] + cost[edge] + dist_from_finish) {
    //             second_path = dist[from[edge]] + cost[edge] + dist_from_finish;
    //             left_vertex = from[edge];
    //             right_vertex = to[edge];
    //         }
    //     }
    //     dist_from_finish += cost[parent[vertex]];
    //     if (vertex == start) {
    //         break;
    //     }
    //     vertex = from[parent[vertex]];
    // }

    // std::vector<int> answer;
    // vertex = finish;
    // bool jump = false;

    // while (vertex != start || !jump) {
    //     answer.push_back(vertex);
    //     if (vertex == right_vertex) {
    //         vertex = left_vertex;
    //         jump = true;
    //     } else {
    //         vertex = from[parent[vertex]];
    //     }
    // }
    // answer.push_back(start);
    // std::reverse(answer.begin(), answer.end());

    // out << second_path << std::endl;
    
    // for (size_t i = 0; i < answer.size() - 1; ++i) {
    //     out << answer[i] + 1 << ' ';
    // }
    // out << answer.back() << '\n';

    // return 0;
}