#pragma once
#include <memory>
#include "b_tree_node.h"

template <typename T>
class BTree
{
private:
    std::shared_ptr<BTreeNode<T>> root;
    int maxNKeys;

    /// @brief Insert a key into a particular node
    /// @param key
    /// @param node
    void insertInto(const T &key, BTreeNode<T> &node);

    /// @brief Find the best leaf node to insert the given key into
    /// @param key
    /// @return
    BTreeNode<T> &findOptimalInsertionNode(const T &key);

    /// @brief Split root into two nodes and a new root
    /// @param root
    void splitRoot(BTreeNode<T> &root);

    /// @brief Fix a node which has less keys than the minimum number of keys
    /// @param node
    void fixLessThanMinInvalidity(BTreeNode<T> &node);

    /// @brief Remove key from a non-leaf node. i.e a node with children
    /// @param key
    /// @param node
    void removeFromNonLeafNode(const T &key, BTreeNode<T> &node);

    /// @brief Replace a key, K, in a nodes, with a valid key, R, from a leaf node of the subtrees of K.
    ///
    /// R is either the closest leaf node less than the K in the left subtree or the closest leaf node greater than K in the
    /// right subtree
    /// @param key
    /// @param node
    /// @return
    BTreeNode<T> &replaceNodeKeyFromSubTree(const T &key, BTreeNode<T> &node);

    /// @brief Get the rightmost leaf node of the left subtree with some key in a start node as the root
    /// @param key
    /// @param startNode
    /// @return
    BTreeNode<T> &findRightmostLeafOfLeftSubtree(const T &key, BTreeNode<T> startNode);

    /// @brief Get the leftmost leaf node of the right subtree with some key in a start node as the root
    /// @param key
    /// @param startNode
    /// @return
    BTreeNode<T> &findLeftmostLeafOfRightSubtree(const T &key, BTreeNode<T> startNode);

public:
    BTree(int maxKeys) : maxNKeys(maxKeys), root(nullptr)
    {
    }

    int getMaxNKeys() const;
    int getMinNKeys() const;

    /// @brief Insert a key into tree
    /// @param key
    void insert(const T &key);

    /// @brief Remove a key
    /// @param key
    void remove(const T &key);

    /// @brief Find a key
    /// @param key
    /// @return The key if it was found; nullptr if it does not exist in the tree
    T *find(const T &key);

    /// @brief Check if tree is in a valid state
    /// @return
    bool isValid() const;
};