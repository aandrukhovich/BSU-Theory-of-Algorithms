#include <iostream>
#include <memory>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
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
            data{d}, parent(p), left{nullptr}, right{nullptr} {
        }
        T data;
        Node* parent;
        upNode left;
        upNode right;
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
        std::cout << std::endl;
    }
  private:
    std::unique_ptr<Node> _root;


    void _print(Node* node) {
        if (node == nullptr) {
            return;
        }
        _print(node->left.get());
        std::cout << node->data << " ";
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
                node->data = (right->data);
                node->right = (std::move(right->right));
            } else {
                node->data = (min_node->data);
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

    //freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    BST<int> bst;
    bst.insert(13);
    bst.find(13);
    bst.remove(13);
    bst.print();

    return 0;
}
