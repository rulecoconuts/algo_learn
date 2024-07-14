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
    BTreeNode(std::vector<T> initialKeys) : keys(initialKeys)
    {
    }
    std::vector<T> getKeys() const;

    std::weak_ptr<BTreeNode<T>> getParent() const;
    int nChildren() const;
    int nKeys() const;
    BTreeNodeSplitResult<T> split();
    void merge(int pos, bool chooseLeft);
};