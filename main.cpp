#include <iostream>

#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree<int> bst;

    bst.insert(5);
    bst.insert(6);
    bst.insert(7);
    bst.insert(4);
    bst.insert(3);

    std::cout << bst.contains(1) << std::endl;
    std::cout << bst.contains(3) << std::endl;
    std::cout << bst.contains(6) << std::endl;
    std::cout << bst.elements() << std::endl;
    std::cout << bst.max() << std::endl;
    std::cout << bst.min() << std::endl;
}
