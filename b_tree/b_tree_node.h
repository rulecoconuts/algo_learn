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

public:
    BTreeNode(std::vector<T> initialKeys) : keys(initialKeys), parent(nullptr)
    {
    }

    BTreeNode(std::weak_ptr<BTreeNode<T>> initialParent) : parent(initialParent)
    {
    }

    BTreeNode(std::vector<T> initialKeys, std::weak_ptr<BTreeNode<T>> initialParent) : keys(initialKeys), parent(initialParent)
    {
    }

    std::vector<T> getKeys() const;

    std::weak_ptr<BTreeNode<T>> getParent() const;

    void setParent(std::weak_ptr<BTreeNode<T>> parent);

    bool hasParent() const;

    int nChildren() const;
    int nKeys() const;
    BTreeNodeSplitResult<T> split();
    BTreeNodeSplitResult<T> splitChild(int pos);
    BTreeNodeSplitResult<T> splitChild(BTreeNode<T> &node);
    int indexOfChild(BTreeNode<T> &node);
    void merge(int pos);
    void insertKey(const T &key);
    void removeKey(const T &key);

    void insertChildAtBack(BTreeNode<T> &child);

    /// @brief Return the next child node to follow when looking for a key
    /// @param key
    /// @return
    BTreeNode<T> &findNextNode(T &key);

    T *findKey(const T &key);

    /// @brief Take a key from an immediate sibling/neighbour of a node
    /// @param pos Node position
    /// @return true if a key was borrowed successfully. false if it is not possible to borrow a key
    bool borrowFromSibling(int pos);

    /// @brief Replace the key in this node with a key from one of its immediate children
    /// @param key
    /// @return
    BTreeNode<T> &replaceKeyWithChildKey(T &key);
};