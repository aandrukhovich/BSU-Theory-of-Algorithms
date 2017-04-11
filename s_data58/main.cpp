#include <iostream>
#include <vector>
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


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    std::ios_base::sync_with_stdio(0);
    size_t n, m;
    std::cin >> m >> n;

    std::vector<std::vector<int>> data(m);
    for (size_t i = 0; i < m; ++i) {
        data[i].resize(n);
        for (size_t j = 0; j < n; ++j) {
            std::cin >> data[i][j];
        }
        std::reverse(data[i].begin(), data[i].end());
    }

    Heap<std::pair<int, size_t>> heap;
    for (size_t i = 0; i < m; ++i) {
        heap.add(std::make_pair(data[i].back(), i));
    }
    std::vector<int> answer;
    while (!heap.empty()) {
        auto p = heap.get_min();
        heap.remove_min();

        answer.push_back(p.first);
        size_t index = p.second;
        data[index].pop_back();
        if (!data[index].empty()) {
            heap.add(std::make_pair(data[index].back(), index));
        }
    }

    for (size_t i = 0; i < answer.size() - 1; ++i) {
        std::cout << answer[i] << ' ';
    }
    std::cout << answer.back() << '\n';

    return 0;
}