#include <b_tree_node.h>
#include <cmath>

template <typename T>
std::vector<T> &BTreeNode<T>::getKeys() const
{
    return keys
}

template <typename T>
std::weak_ptr<BTreeNode<T>> BTreeNode<T>::getParent() const
{
    return parent;
}

template <typename T>
void BTreeNode<T>::setParent(std::weak_ptr<BTreeNode<T>> parent)
{
    this->parent = parent;
}

template <typename T>
bool BTreeNode<T>::hasParent() const
{
    return parent != nullptr;
}

template <typename T>
int BTreeNode<T>::nChildren() const
{
    return children.size();
}

template <typename T>
int BTreeNode<T>::nKeys() const
{
    return keys.size();
}

template <typename T>
BTreeNodeSplitResult<T> BTreeNode<T>::split(int maxNKeys)
{
    int minNKeys = floor((double)maxNKeys / 2.0);
    int nImmediateChildren = minNKeys + 1;
    std::vector<std::shared_ptr<BTreeNode<T>>> newChildren;
    std::vector<T> newKeys;

    for (int i = 0; i < minNKeys; i++)
    {
        newKeys.push_back(keys.front());
        keys.erase(keys.begin());
    }

    for (int i = 0; i < nImmediateChildren; i++)
    {
        newChildren.push_back(children.front());
        children.erase(children.begin());
    }

    std::shared_ptr<BTreeNode<T>> newNode = std::make_shared(newKeys, newChildren);

    T newRootKey = keys.front();
    keys.erase(keys.begin());

    return BTreeNodeSplitResult<T>(newRootKey, newNode);
}
