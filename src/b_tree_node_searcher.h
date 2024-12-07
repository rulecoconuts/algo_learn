#pragma once
/// @brief A component to search for a key through the nodes of a BTree
/// @tparam T
template <typename T>
class BTreeNodeSearcher
{
public:
    virtual T *find(const T &key, const BTreeNode<T> &root) = 0;
};