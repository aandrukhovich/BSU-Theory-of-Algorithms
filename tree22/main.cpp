#include <iostream>
#include <memory>

template <class T>
class BST {
  public:
    class Node;
    typedef std::unique_ptr<Node> upNode;

    class Node {
      public:
        Node(const T& d, Node* p = nullptr) :
            data{d}, parent(p), left{nullptr}, right{nullptr},
            size{1}, height{0}, count_bad{0}, bad{false} {
        }

        T data;
        Node* parent;
        upNode left;
        upNode right;
        size_t size;
        size_t height;

        size_t count_bad;
        bool bad;

        void swap_data(Node* node) {
            std::swap(data, node->data);
            std::swap(size, node->size);
            std::swap(height, node->height);
            std::swap(count_bad, node->count_bad);
            std::swap(bad, node->bad);
        }

        void calc() {
            size_t left_height = (left ? left->height : -1);
            size_t right_height = (right ? right->height : -1);
            size_t left_size = (left ? left->size : 0);
            size_t right_size = (right ? right->size : 0);

            height = std::max(left_height, right_height) + 1;
            size = left_size + right_size + 1;

            bad = (left_size == right_size && left_height != right_height);
            count_bad = (left ? left->count_bad : 0) +
                        (right ? right->count_bad : 0) +
                        (bad ? 1 : 0);
        }
    };

    BST(const T& data) : _root{std::make_unique<Node>(data)} {
    };

    BST() : _root(nullptr) {
    };

    //  return true, if data is not unique key
    //         false, else
    bool insert(const T& data) {
        if (_root == nullptr) {
            _root = std::make_unique<Node>(data, nullptr);
            return true;
        }

        Node* node = _find(_root.get(), data);
        if (node->data == data) {
            return false;
        }

        if (data < node->data) {
            node->left = std::make_unique<Node>(data, node);
        } else {
            node->right = std::make_unique<Node>(data, node);
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
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);

        T x;
        while (std::cin >> x) {
            insert(x);
        }
    }

    void task22() {
        read();
        calc(_root.get());
        if (_root == nullptr) {
            return;
        }

        size_t count_bad = _root->count_bad;
        if (count_bad % 2 == 1) {
            remove_bad(_root.get(), count_bad / 2);
        }
        print();
    }

    void remove_bad(Node* node, size_t index) {
        size_t left_bad = (node->left ? node->left->count_bad : 0);
        if (left_bad == index && node->bad) {
            _remove(node);
            return;
        }

        if (index < left_bad) {
            remove_bad(node->left.get(), index);
        } else {
            remove_bad(node->right.get(), index - left_bad - (node->bad ? 1 : 0));
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


    void _print(Node* node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->data << std::endl;
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
        if (node->left.get() == nullptr && node->right.get() == nullptr) {
            if (node == _root.get()) {
                _root = nullptr;
            } else if (_is_left_son(node)) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else if (node->right.get() == nullptr) {
            node->left.get()->parent = parent;
            if (node == _root.get()) {
                _root = std::move(node->left);
            } else if (_is_left_son(node)) {
                parent->left = (std::move(node->left));
            } else {
                parent->right = (std::move(node->left));
            }
        } else if (node->left.get() == nullptr) {
            node->right.get()->parent = (parent);
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
            } else {
                node->swap_data(min_node);
                _remove(min_node);

            }
        }
    }
    Node* _find_min(Node * root) {
        while (root->left.get() != nullptr) {
            root = root->left.get();
        }
        return root;
    }

};

int main() {

    BST<long long> bst;
    bst.task22();

    return 0;
}
