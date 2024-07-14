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

    bool hasParent() const;

    int nChildren() const;
    int nKeys() const;
    BTreeNodeSplitResult<T> split();
    BTreeNodeSplitResult<T> splitChild(int pos);
    BTreeNodeSplitResult<T> splitChild(BTreeNode<T> &node);
    void merge(int pos, bool chooseLeft);
    void insertKey(const T &key);
};