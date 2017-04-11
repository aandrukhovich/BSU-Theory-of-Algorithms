#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip> 

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
    size_t n;
    std::cin >> n;

    Heap<long long> heap;
    for (size_t i = 0; i < n; ++i) {
        long long x;
        std::cin >> x;
        heap.add(x);
    }

    long long answer = 0;
    while (!heap.empty()) {
        long long x = heap.get_min();
        heap.remove_min();
        if (heap.empty()) {
            break;
        }
        long long y = heap.get_min();
        heap.remove_min();

        heap.add(x + y);
        answer += x + y;
    }

    long double ans = (long double)(answer * 1.0 / 20);
    std::cout << std::fixed << std::setprecision(2) <<  ans;

    return 0;
}