#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>

template<typename T>
class Heap {
public:
    Heap() {};

    T get_min() {
        return data_.front();
    }

    void remove_min() {
        std::swap(data_[0], data_[size() - 1]);
        data_.pop_back();
        sift_down(0);
    }

    void add(T elem) {
        data_.push_back(elem);
        sift_up(size() - 1);
    }

    bool empty() {
        return (size() == 0);
    }

    size_t size() {
        return data_.size();
    }

private:
    std::vector<T> data_;

    void sift_down(size_t i) {
        size_t left = i + i + 1;
        size_t right = i + i + 2;
        size_t largest = i;
        if (left < size() && data_[left] < data_[largest]) {
            largest = left;
        }
        if (right < size() && data_[right] < data_[largest]) {
            largest = right;
        }
        if (largest != i) {
            std::swap(data_[largest], data_[i]);
            sift_down(largest);
        }
    }

    void sift_up(size_t i) {
        size_t parent = (i - 1) / 2;
        if (i != 0 && data_[parent] > data_[i]) {
            std::swap(data_[parent], data_[i]);
            sift_up(parent);
        }
    }
};

bool correct(int x, int y, int n, int m,
            const std::vector<std::vector<int>> &board) {

    return x >= 0 && y >= 0 && x < n && y < m && board[x][y] != -1;
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    std::ios_base::sync_with_stdio(0);
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> board(n);
    for (size_t i = 0; i < n; ++i) {
        board[i].resize(m);
        for (size_t j = 0; j < m; ++j) {
            std::cin >> board[i][j];
        }
    }

    int start_x, start_y, finish_x, finish_y;
    std::cin >> start_x >> start_y >> finish_x >> finish_y;
    start_x--;
    start_y--;
    finish_x--;
    finish_y--;


    Heap<std::pair<int, std::pair<int, int>>> heap;
    heap.add(std::make_pair(0, std::make_pair(start_x, start_y)));

    std::vector<std::vector<unsigned int>> dist(n);
    std::vector<std::vector<bool>> used(n);
    for (size_t i = 0; i < n; ++i) {
        dist[i].resize(m, 2e9);
        used[i].resize(m, false);
    }
    dist[start_x][start_y] = 0;
    
    constexpr int dx[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
    constexpr int dy[8] = {2, 2, 1, -1, -2, -2, -1, 1};
    while (!heap.empty()) {
        auto p = heap.get_min();
        heap.remove_min();
        int d = p.first, x = p.second.first, y = p.second.second;
        if (x == finish_x && y == finish_y) {
            std::cout << d;
            return 0;
        }

        if (dist[x][y] < d || used[x][y]) {
            continue;
        }
        used[x][y] = true;

        for (auto i = 0; i < 8; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (correct(nx, ny, n, m, board) && 
                dist[nx][ny] > dist[x][y] + board[nx][ny] + 1) {
                dist[nx][ny] = dist[x][y] + board[nx][ny] + 1;
                heap.add(std::make_pair(dist[nx][ny], 
                    std::make_pair(nx, ny)));
            }
        }
    }

    std::cout << "No";

    return 0;
}