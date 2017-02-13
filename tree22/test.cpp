#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <set>
#include <fstream>
#include "bst.h"



void test_build() {
    srand(42);
    int i = 0;
    int n = 10220;
    int M = 12220;

    while (i < 100) {
        std::set<int> s;
        BST<int> bst;
        for (int i = 0; i < n; ++i) {
            s.insert(rand() % M);
        }
        std::vector<int> v(s.size());
        std::copy(s.begin(), s.end(), v.begin());
        std::random_shuffle(v.begin(), v.end());

        int N = v.size();
        for (auto i : v) {
            bst.insert(i);
        }
        bst.print_sort();

        std::sort(v.begin(), v.end());

        freopen("out.txt", "r", stdin);
        std::vector<int> test(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> test[i];
        }

        for (int i = 0; i < N; ++i) {
            if (v[i] != test[i]) {
                std::cout << "error";
                std::cout << v[i] << " " << test[i] << std::endl;
                return;
            }
        }
        std::cout << i++ << " :ok" << std::endl;
    }
}

std::vector<int> add_to_bst(BST<int> &bst) {
    std::ifstream out("in.txt");
    srand(12);

    int n = 100;
    int M = 121;

    std::set<int> s;
    for (int i = 0; i < n; ++i) {
        s.insert(rand() % M);
    }
    std::vector<int> v(s.size());
    std::copy(s.begin(), s.end(), v.begin());
    std::random_shuffle(v.begin(), v.end());


    int N = v.size();
    for (auto i : v) {
        bst.insert(i);
    }
    std::sort(v.begin(), v.end());
    return v;
}

void test_remove() {

    int i = 0;
    while (1) {


        BST<int> bst;
        std::vector<int> v = add_to_bst(bst);

        size_t size = v.size();
        std::ifstream in("out.txt");
        while (v.size() + v.size() > size) {
            int r = v[rand() % v.size()];
            v.erase(std::find(v.begin(), v.end(), r));
            bst.remove(r);
            bst.print_sort();

            std::vector<int> test(v.size());
            for (int i = 0; i < v.size(); ++i) {
                in >> test[i];
            }

            for (int i = 0; i < v.size(); ++i) {
                if (v[i] != test[i]) {
                    std::cout << "error";
                    for (auto i : v) {
                        std::cout << i << " ";
                    }
                    return;
                }
            }
        }
        std::cout << i++ << " : ok" << std::endl;
    }
}


void test_task() {
    int i = 0;
    while (1) {

        BST<int> bst;
        std::vector<int> v = add_to_bst(bst);
        bst.task1();

        size_t size = v.size();
        std::ifstream in("out.txt");

        int x;
        std::vector<int> bad;
        while (in >> x) {
            bad.push_back(x);
        }
        bst.task2();

        if (bad.size() % 2) {
            bad.erase(std::find(bad.begin(), bad.end(), bad[bad.size() / 2]));
        }

        int j = 0;
        while (in >> x) {
            if (x != bad[j]) {
                std::cout << "error";
                return;
            }
        }
        i++;
        std::cout << i << " : ok" << std::endl;

    }
}
int main() {
    // test_build();
    // test_remove();
    test_task();
}