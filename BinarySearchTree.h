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
};

#endif // BINARYSEARCHTREE_H
