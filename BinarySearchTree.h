#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <memory>

template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree() = default;
    ~BinarySearchTree() = default;

    void insert(T &&value)
    {
        std::unique_ptr<Node> *slot = &head;

        while (*slot) {
            if (value < (*slot)->value) {
                slot = &(*slot)->left;
            } else {
                slot = &(*slot)->right;
            }
        }

        *slot = std::make_unique<Node>(std::move(value));
    }

    int elements() const { return countNodes(head.get()); }

    bool remove(const T &value)
    {
        std::unique_ptr<Node> *slot = &head;
        while (*slot) {
            if (value < (*slot)->value) {
                slot = &(*slot)->left;
            } else if (value > (*slot)->value) {
                slot = &(*slot)->right;
            } else {
                break;
            }
        }

        if (!*slot) {
            return false;
        }

        Node *node = slot->get();
        if (!node->left) {
            *slot = std::move(node->right);
        } else if (!node->right) {
            *slot = std::move(node->left);
        } else {
            std::unique_ptr<Node> *succ = &node->right;
            while ((*succ)->left) {
                succ = &(*succ)->left;
            }
            node->value = std::move((*succ)->value);
            *succ = std::move((*succ)->right);
        }
    }

    T max() const
    {
        if (!head) {
            return T{};
        }
        Node *ptr = head.get();
        while (ptr->right) {
            ptr = ptr->right.get();
        }
        return ptr->value;
    }

    T min() const
    {
        if (!head) {
            return T{};
        }
        Node *ptr = head.get();
        while (ptr->left) {
            ptr = ptr->left.get();
        }
        return ptr->value;
    }

    bool contains(const T &value) const
    {
        Node *ptr = head.get();

        if (!ptr) {
            return false;
        }

        bool result = false;

        while (ptr != nullptr) {
            if (ptr->value == value) {
                return true;
            }

            if (ptr->value <= value) {
                ptr = ptr->right.get();
            } else if (ptr->value > value) {
                ptr = ptr->left.get();
            }
        }

        return result;
    }

private:
    struct Node
    {
        T value;
        std::unique_ptr<Node> left{nullptr};
        std::unique_ptr<Node> right{nullptr};
    };

    std::unique_ptr<Node> head;

    auto createNode(T &&value)
    {
        std::unique_ptr<Node> newNode = std::make_unique<Node>();
        newNode->value = std::forward<T>(value);
        return newNode;
    }

    int countNodes(Node *n) const
    {
        if (!n) {
            return 0;
        }
        return 1 + countNodes(n->left.get()) + countNodes(n->right.get());
    }
    T valueOf(Node *ptr) { return ptr->value; }
    template<typename F>
    static void preOrder(const Node *n, F &visit)
    {
        if (!n)
            return;
        visit(n->value);                 // 1. сам узел
        preOrder(n->left.get(), visit);  // 2. левое
        preOrder(n->right.get(), visit); // 3. правое
    }

    template<typename F>
    static void inOrder(const Node *n, F &visit)
    {
        if (!n)
            return;
        inOrder(n->left.get(), visit);  // 1. левое
        visit(n->value);                // 2. сам узел
        inOrder(n->right.get(), visit); // 3. правое
    }

    template<typename F>
    static void postOrder(const Node *n, F &visit)
    {
        if (!n)
            return;
        postOrder(n->left.get(), visit);  // 1. левое
        postOrder(n->right.get(), visit); // 2. правое
        visit(n->value);                  // 3. сам узел
    }
};

#endif // BINARYSEARCHTREE_H
