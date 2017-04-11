#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>

template<typename T>
class DSU{ 
public:
    DSU(){};
    void make_set(T elem);
    void union_sets(T first, T second);
    T find_set(T elem);

};

int x = 1;
int f() {
    return x = 2;
}

int main() {

    f();
    std::cerr << x;

    return 0;

}