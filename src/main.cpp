#include <iostream>
#include "b_tree.h"

int main(int argc, char **argv)
{
    std::shared_ptr<BTreeNodeSearcher<int>> nodeSearcher = std::make_shared<IterativeBTreeNodeSearcher<int>>();
    std::shared_ptr<BTreeNodeValidator<int>> nodeValidator = std::make_shared<DefaultBTreeNodeValidator<int>>();
    int maxKeys = 5;
    BTree<int> tree = BTree<int>(maxKeys, nodeValidator, nodeSearcher);

    tree.insert(40);
    tree.insert(20);
    tree.insert(2);
    tree.insert(1);
    int key = 55;
    tree.insert(key);
    int *foundKey = tree.find(key);

    std::cout << maxKeys << std::endl;
    return 0;
}