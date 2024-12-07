#pragma once
#include "b_tree_node_searcher.h"
#include "b_tree_node.h"

/// @brief Default implementation of a component to search for a key through the nodes of a BTree
/// @tparam T
template <typename T>
class IterativeBTreeNodeSearcher : public BTreeNodeSearcher<T>
{
public:
    T *find(const T &key, const BTreeNode<T> &root);
};

// DEFINITION

#include "iterative_b_tree_node_searcher.h"
template <typename T>
T *IterativeBTreeNodeSearcher<T>::find(const T &key, const BTreeNode<T> &root)
{
    BTreeNode<T> *currentNode = (BTreeNode<T> *)&(root);
    T *keyInTree = nullptr;

    // Keep searching until we find the key or there are no more levels to search
    while ((keyInTree = currentNode->findKey(key)) == nullptr && currentNode->nChildren() > 0)
    {
        currentNode = &(currentNode->findNextNode(key));
    }

    return keyInTree;
}