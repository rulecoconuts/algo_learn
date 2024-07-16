#pragma once
#include <vector>
#include <memory>
#include <b_tree_node_split_result.h>

template <typename T>
class BTreeNode
{
private:
    std::vector<T> keys;
    std::weak_ptr<BTreeNode<T>> parent;
    std::vector<std::shared_ptr<BTreeNode<T>>> children;

    void setParent(std::weak_ptr<BTreeNode<T>> parent);

public:
    BTreeNode(std::vector<T> initialKeys) : keys(initialKeys), parent(nullptr)
    {
    }

    BTreeNode(std::vector<T> initialKeys, std::vector<std::shared_ptr<BTreeNode<T>>> initialChildren) : keys(initialKeys), children(initialChildren), parent(nullptr)
    {
    }

    BTreeNode(std::weak_ptr<BTreeNode<T>> initialParent) : parent(initialParent)
    {
    }

    BTreeNode(std::vector<T> initialKeys, std::weak_ptr<BTreeNode<T>> initialParent) : keys(initialKeys), parent(initialParent)
    {
    }

    std::vector<T> &getKeys() const;

    std::weak_ptr<BTreeNode<T>> getParent() const;

    bool hasParent() const;

    int nChildren() const;
    int nKeys() const;

    /// @brief Find the index of a child in the node
    /// @param node
    /// @return 0+ index if the child was found. -1 if it was not
    int indexOfChild(BTreeNode<T> &node);

    /// @brief Split the node into two
    /// @param maxNKeys
    /// @return
    BTreeNodeSplitResult<T> split(int maxNKeys);

    /// @brief Split child into two
    /// @param pos
    /// @param minNKeys
    /// @return
    BTreeNodeSplitResult<T> splitChild(int pos, int minNKeys);

    /// @brief Split child into two
    /// @param node
    /// @param minNKeys
    /// @return
    BTreeNodeSplitResult<T> splitChild(BTreeNode<T> &node, int minNKeys);

    /// @brief Merge child node with one of its siblings
    /// @param pos
    void merge(int pos);

    /// @brief Insert key into its correct sorted position
    /// @param key
    void insertKey(const T &key);

    /// @brief Find index of key
    /// @param key
    /// @return 0+ index if the child was found. -1 if it was not
    int indexOfKey(const T &key);

    /// @brief Remove key
    /// @param key
    void removeKey(const T &key);

    void insertChildAtBack(BTreeNode<T> &child);

    T *findKey(const T &key);

    /// @brief Return the next child node to follow when looking for a key
    /// @param key
    /// @return
    BTreeNode<T> &findNextNode(T &key);

    /// @brief Take a key from an immediate sibling/neighbour of a node
    /// @param pos Node position
    /// @param minNKeys
    /// @return true if a key was borrowed successfully. false if it is not possible to borrow a key
    bool borrowFromSibling(int pos, int minNKeys);

    /// @brief Replace the key in this node with a key from one of its immediate children
    /// @param key
    /// @return
    BTreeNode<T> &replaceKeyWithChildKey(T &key);
};