#include <iostream>
#include <memory>
#include <cstdio>
#include <algorithm>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
class BST {
  public:
    class Node;
    typedef std::unique_ptr<Node> upNode;

    class Node {
      public:
        Node(const T& d, Node* p = nullptr) :
            data{d}, parent(p) {
        }

        T data;
        Node* parent;
        upNode left = nullptr;
        upNode right = nullptr;
        int size = 1;
        int diff_size = 0;
        int max_diff = 0;

        void swap_data(Node* node) {
            std::swap(data, node->data);
            std::swap(size, node->size);
            std::swap(diff_size, node->diff_size);
            std::swap(max_diff, node->max_diff);
        }

        void calc() {
            int left_size = (left ? left->size : 0);
            int right_size = (right ? right->size : 0);
            int left_max = (left ? left->max_diff : 0);
            int right_max = (right ? right->max_diff : 0);

            size = left_size + right_size + 1;
            diff_size = abs(left_size - right_size);
            max_diff = std::max(std::max(left_max, right_max),
                                diff_size);
        }
    };

    BST(const T& data) : _root{make_unique<Node>(data)} {
    };

    BST() : _root(nullptr) {
    };

    //  return true, if data is not unique key
    //         false, else
    bool insert(const T& data) {
        if (_root == nullptr) {
            _root = make_unique<Node>(data, nullptr);
            return true;
        }

        Node* node = _find(_root.get(), data);
        if (node->data == data) {
            return false;
        }

        if (data < node->data) {
            node->left = make_unique<Node>(data, node);
        } else {
            node->right = make_unique<Node>(data, node);
        }
        return true;
    }
    bool remove(const T& data) {
        Node* node = _find(_root.get(),  data);
        if (node->data != data) {
            return false;
        } else {
            _remove(node);
            return true;
        }
    }

    bool find(const T& data) {
        Node* node = _find(_root.get(), data);
        return node->data == data;
    }

    void print() {
        _print(_root.get());
    }

    void read() {
        freopen("tst.in", "r", stdin);
        freopen("tst.out", "w", stdout);

        T x;
        while (std::cin >> x) {
            insert(x);
        }
    }

    void task26() {
        read();
        if (_root == nullptr) {
            return;
        }

        calc(_root.get());
        find_and_remove(_root.get());
        // std::cout << _root->size << " " << _root->left->size << " "
        //           << _root->right->size << std::endl;
        print();
    }

    void find_and_remove(Node* node) {
        if (node == nullptr) {
            return;
        }
        if (!find_max) {
            find_and_remove(node->right.get());
        }
        if (!find_max && node->diff_size == _root->max_diff) {
            _remove(node);
            find_max = true;
        }
        if (!find_max) {
            find_and_remove(node->left.get());
        }
    }

    void calc(Node* node) {
        if (node == nullptr) {
            return;
        }
        calc(node->left.get());
        calc(node->right.get());
        node->calc();
    }

  private:
    std::unique_ptr<Node> _root;

    bool find_max = false;

    void _print(Node* node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->data <<  std::endl;
        _print(node->left.get());
        _print(node->right.get());
    }

    // write comment
    Node* _find(Node* node, const T& data) {
        T node_data = node->data;
        if (data == node_data) {
            return node;
        }

        if (data < node_data) {
            if (node->left.get() == nullptr) {
                return node;
            } else {
                return _find(node->left.get(), data);
            }
        } else {
            if (node->right.get() == nullptr) {
                return node;
            } else {
                return _find(node->right.get(), data);
            }
        }
    }
    // node should not be _root
    bool _is_left_son(Node* node) {
        return (node->parent->left.get() == node);
    }

    void _remove(Node* node) {
        Node* parent = node->parent;
        if ((node->left == nullptr) && (node->right == nullptr)) {
            if (node == _root.get()) {
                _root = nullptr;
            } else if (_is_left_son(node)) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else if (node->right == nullptr) {
            node->left->parent = parent;
            if (node == _root.get()) {
                _root = std::move(node->left);
            } else if (_is_left_son(node)) {
                parent->left = (std::move(node->left));
            } else {
                parent->right = (std::move(node->left));
            }
        } else if (node->left == nullptr) {
            node->right->parent = parent;
            if (node == _root.get()) {
                _root = std::move(node->right);
            } else if (_is_left_son(node)) {
                parent->left = (std::move(node->right));
            } else {
                parent->right = (std::move(node->right));
            }
        } else {
            Node* right = node->right.get();
            Node* min_node = _find_min(right);
            if (min_node == right) {
                node->swap_data(right);
                node->right = (std::move(right->right));
                if (node->right) {
                    node->right->parent = node;
                }
            } else {
                node->swap_data(min_node);
                _remove(min_node);
            }
        }
    }
    Node* _find_min(Node* root) {
        while (root->left != nullptr) {
            root = root->left.get();
        }
        return root;
    }

};

int main() {

    BST<long long> bst;
    bst.task26();

    return 0;
}