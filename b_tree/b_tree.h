#pragma once
#include <memory>
#include <b_tree_node.h>

template <typename T>
class BTree
{
private:
    std::shared_ptr<BTreeNode<T>> root;
    int maxNKeys;

public:
    BTree(int maxKeys) : maxNKeys(maxKeys), root(nullptr)
    {
    }

    int getMaxNKeys() const;
    int getMinNKeys() const;

    /// @brief Insert a key into tree
    /// @param key
    void insert(const T &key);

    /// @brief Insert a key into a particular node
    /// @param key
    /// @param node
    void insertInto(const T &key, BTreeNode<T> &node);

    /// @brief Remove a key
    /// @param key
    void remove(const T &key);

    /// @brief Find a key
    /// @param key
    /// @return The key if it was found; nullptr if it does not exist in the tree
    T *find(const T &key);

    BTreeNode<T> &findOptimalInsertionNode(const T &key);

    void makeNewRoot(BTreeNodeSplitResult<T> splitResult, BTreeNode<T> root);
};