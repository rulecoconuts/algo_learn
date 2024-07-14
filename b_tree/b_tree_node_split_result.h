
#pragma once
#include <memory>
template <typename T>
class BTreeNode;

template <typename T>
class BTreeNodeSplitResult
{
private:
    T rootKey;
    std::shared_ptr<BTreeNode<T>> node;

public:
    BTreeNodeSplitResult(T newRootKey, std::shared_ptr<BTreeNode<T>> newNode) : rootKey(newRootKey), node(newNode)
    {
    }

    T getRootKey() const
    {
        return rootKey;
    }

    std::shared_ptr<BTreeNode<T>> getNode() const
    {
        return node;
    }
};