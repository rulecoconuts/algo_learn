#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include "b_tree_node_split_result.h"

template <typename T>
class BTreeNode
{
private:
    std::vector<T> keys;
    std::weak_ptr<BTreeNode<T>> parent;
    std::vector<std::shared_ptr<BTreeNode<T>>> children;

    void setParent(std::weak_ptr<BTreeNode<T>> parent);

public:
    BTreeNode(std::vector<T> initialKeys) : keys(initialKeys)
    {
        // parent = nullptr;
    }

    BTreeNode(std::vector<T> initialKeys, std::vector<std::shared_ptr<BTreeNode<T>>> initialChildren) : keys(initialKeys), children(initialChildren)
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

    /// @brief Get the first key
    /// @return
    T &firstKey();

    /// @brief Get the last key
    /// @return
    T &lastKey();

    /// @brief Remove and return the first key
    /// @return
    T popFirstKey();

    /// @brief Remove and return the last key
    /// @return
    T popLastKey();

    T *findKey(const T &key);

    /// @brief Get the first child
    /// @return
    BTreeNode<T> &firstChild();

    /// @brief Get the last child
    /// @return
    BTreeNode<T> &lastChild();

    /// @brief Return the next child node to follow when looking for a key
    /// @param key
    /// @return
    BTreeNode<T> &findNextNode(const T &key);

    /// @brief Return the left child node of a key
    /// @param key
    /// @return
    BTreeNode<T> &getLeftChild(const T &key);

    /// @brief Return the right child node of a key
    /// @param key
    /// @return
    BTreeNode<T> &getRightChild(const T &key);

    /// @brief Take a key from an immediate sibling/neighbour of a node
    /// @param pos Node position
    /// @param minNKeys
    /// @return true if a key was borrowed successfully. false if it is not possible to borrow a key
    bool borrowFromSibling(int pos, int minNKeys);

    /// @brief Replace the key in this node with a key from one of its immediate children
    /// @param key
    /// @return
    BTreeNode<T> &replaceKeyWithChildKey(const T &key);
};

// DEFINITION

template <typename T>
std::vector<T> &BTreeNode<T>::getKeys() const
{
    return keys;
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
    return (parent.lock()) != nullptr;
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
BTreeNodeSplitResult<T> BTreeNode<T>::split(int minNKeys)
{
    int nImmediateChildren = minNKeys + 1;
    std::vector<std::shared_ptr<BTreeNode<T>>> newChildren;
    std::vector<T> newKeys;

    // Take the minimum number of keys from the node
    for (int i = 0; i < minNKeys; i++)
    {
        newKeys.push_back(keys.front());
        keys.erase(keys.begin());
    }

    // Take the children of the keys along
    for (int i = 0; i < nImmediateChildren; i++)
    {
        newChildren.push_back(children.front());
        children.erase(children.begin());
    }

    std::shared_ptr<BTreeNode<T>> newNode = std::make_shared<BTreeNode<T>>(newKeys, newChildren);

    T newRootKey = keys.front();
    keys.erase(keys.begin());

    return BTreeNodeSplitResult<T>(newRootKey, newNode);
}

template <typename T>
int BTreeNode<T>::indexOfChild(BTreeNode<T> &node)
{
    BTreeNode<T> *pointer = &node;
    int pos = -1;
    int size = children.size();

    for (int i = 0; i < size; i++)
    {
        BTreeNode<T> child = *(children[i]);
        if ((&child) == pointer)
            return i;
    }

    return pos;
}

template <typename T>
BTreeNodeSplitResult<T> BTreeNode<T>::splitChild(int pos, int minNKeys)
{
    std::shared_ptr<BTreeNode<T>> nodeToBeSplit = children[pos];
    BTreeNodeSplitResult<T> splitResult = nodeToBeSplit->split(minNKeys);
    children.insert(children.begin() + pos, splitResult.getNode());
    keys.insert(keys.begin() + pos, splitResult.getRootKey());

    return splitResult;
}

template <typename T>
BTreeNodeSplitResult<T> BTreeNode<T>::splitChild(BTreeNode<T> &node, int minNKeys)
{
    return splitChild(indexOfChild(node), minNKeys);
}

template <typename T>
void BTreeNode<T>::merge(int pos)
{
    std::shared_ptr<BTreeNode<T>> pivotNodePtr = children[pos];
    BTreeNode<T> pivotNode = *pivotNodePtr;
    bool chooseLeft = pos != 0;
    int rootKeyPos = chooseLeft ? pos - 1 : pos + 1;
    int siblingPos = rootKeyPos;

    std::shared_ptr<BTreeNode<T>> siblingNodePtr = children[siblingPos];
    BTreeNode<T> siblingNode = *siblingNodePtr;

    // Make every child of the sibling point to the pivot node as the new parent
    for (std::shared_ptr<BTreeNode<T>> childPtr : siblingNode.children)
    {
        BTreeNode<T> child = *childPtr;
        child.parent = pivotNodePtr;
    }

    if (chooseLeft)
    {
        // Insert keys and children into pivot node from the left
        pivotNode.keys.insert(pivotNode.keys.begin(), keys[rootKeyPos]);
        pivotNode.keys.insert(pivotNode.keys.begin(), siblingNode.keys.begin(), siblingNode.keys.end());
        pivotNode.children.insert(pivotNode.children.begin(), siblingNode.children.begin(), siblingNode.children.end());
    }
    else
    {
        // Insert keys and children into pivot node from the right
        pivotNode.keys.insert(pivotNode.keys.end(), keys[rootKeyPos]);
        pivotNode.keys.insert(pivotNode.keys.end(), siblingNode.keys.begin(), siblingNode.keys.end());
        pivotNode.children.insert(pivotNode.children.end(), siblingNode.children.begin(), siblingNode.children.end());
    }

    // Remove key from root and sibling node
    keys.erase(keys.begin() + rootKeyPos);
    children.erase(children.begin() + siblingPos);
}

template <typename T>
void BTreeNode<T>::insertKey(const T &key)
{
    int indexToInsertAt = nKeys();

    for (int i = 0; i < nKeys(); i++)
    {
        if (keys[i] > key)
        {
            indexToInsertAt = i;
            break;
        }
    }

    keys.insert(keys.begin() + indexToInsertAt, key);
}

template <typename T>
int BTreeNode<T>::indexOfKey(const T &key)
{
    for (int i = 0; i < nKeys(); i++)
    {
        if (keys[i] == key)
        {
            return i;
        }
    }

    return -1;
}

template <typename T>
void BTreeNode<T>::removeKey(const T &key)
{
    int index = indexOfKey(key);

    if (index == -1)
        return;

    keys.erase(keys.begin() + index);
}

template <typename T>
T &BTreeNode<T>::firstKey()
{
    return keys.front();
}

template <typename T>
T &BTreeNode<T>::lastKey()
{
    return keys.back();
}

template <typename T>
T BTreeNode<T>::popFirstKey()
{
    T key = keys.front();
    keys.pop_front();

    return key;
}

template <typename T>
T BTreeNode<T>::popLastKey()
{
    T key = keys.back();
    keys.pop_back();

    return key;
}

template <typename T>
BTreeNode<T> &BTreeNode<T>::firstChild()
{
    return children.front();
}

template <typename T>
BTreeNode<T> &BTreeNode<T>::lastChild()
{
    return children.back();
}

template <typename T>
BTreeNode<T> &BTreeNode<T>::getLeftChild(const T &key)
{
    return children.at(indexOfKey(key));
}

template <typename T>
BTreeNode<T> &BTreeNode<T>::getRightChild(const T &key)
{
    return children.at(indexOfKey(key) + 1);
}

template <typename T>
void BTreeNode<T>::insertChildAtBack(BTreeNode<T> &child)
{
    child.parent = std::shared_ptr<BTreeNode<T>>(this);
    children.push_back(std::make_shared<BTreeNode<T>>(child));
}

template <typename T>
T *BTreeNode<T>::findKey(const T &key)
{
    int index = indexOfKey(key);
    if (index == -1)
        return nullptr;

    return &(keys[index]);
}

template <typename T>
BTreeNode<T> &BTreeNode<T>::findNextNode(const T &key)
{
    int indexOfFirstNodeKeyGreaterThanGivenKey = nKeys();

    for (int i = 0; i < nKeys(); i++)
    {
        if (keys[i] > key)
        {
            indexOfFirstNodeKeyGreaterThanGivenKey = i;
            break;
        }
    }

    return *(children[indexOfFirstNodeKeyGreaterThanGivenKey]);
}

template <typename T>
bool BTreeNode<T>::borrowFromSibling(int pos, int minNKeys)
{
    std::shared_ptr<BTreeNode<T>> pivotNodePtr = children[pos];
    BTreeNode<T> pivotNode = *pivotNodePtr;
    bool chooseLeft = pos != 0; // Only false when there is no left sibling
    int rootKeyPos = chooseLeft ? pos - 1 : pos + 1;
    int siblingPos = rootKeyPos;

    std::shared_ptr<BTreeNode<T>> siblingNodePtr = children[siblingPos];
    BTreeNode<T> siblingNode = *siblingNodePtr;

    // We cannot borrow from a sibling if it has the minimum number of keys.
    // Borrowing from it would make the sibling invalid
    if (siblingNode.nKeys() == minNKeys && (pos == 0 || pos == nChildren() - 1))
    {
        // Cannot borrow from sibling and cannot choose a different sibling because we are at
        // the edge of the list of children
        return false;
    }

    if (siblingNode.nKeys() == minNKeys)
    {
        // Switch sibling to borrow from.
        // Since we are not at the edge, we know that chooseLeft will be true. Make chooseLeft false i.e choose right
        chooseLeft = false;
        rootKeyPos = chooseLeft ? pos - 1 : pos + 1;
        siblingPos = rootKeyPos;
        siblingNodePtr = children[siblingPos];
        siblingNode = *siblingNodePtr;

        if (siblingNode.nKeys() == minNKeys)
            return false;
    }

    // If we are borrowing from the left we will take the largest key. From the right, the smallest key.
    // To maintain the properties of the tree, the root key will come down to our pivotNode, and the borrowed key will take
    // the previous position of the root key

    if (chooseLeft)
    {
        // insert root key of left sibling and pivot node at the beginning of pivot node
        pivotNode.keys.insert(pivotNode.keys.begin(), keys[rootKeyPos]);
        if (siblingNode.nChildren() > 0)
        {
            std::shared_ptr<BTreeNode<T>> siblingChild = siblingNode.children.back();
            siblingChild->parent = pivotNodePtr;
            pivotNode.children.insert(pivotNode.children.begin(), siblingChild);
            siblingNode.children.pop_back();
        }
        keys.erase(keys.begin() + rootKeyPos);
        keys.insert(keys.begin() + rootKeyPos, siblingNode.keys.back());
        siblingNode.keys.pop_back();
    }
    else
    {
        // insert root key of pivot node and right sibling at the end of pivot node
        pivotNode.keys.insert(pivotNode.keys.end(), keys[rootKeyPos]);
        if (siblingNode.nChildren() > 0)
        {
            std::shared_ptr<BTreeNode<T>> siblingChild = siblingNode.children.front();
            siblingChild->parent = pivotNodePtr;
            pivotNode.children.insert(pivotNode.children.end(), siblingChild);
            siblingNode.children.erase(siblingNode.children.begin());
        }
        keys.erase(keys.begin() + rootKeyPos);
        keys.insert(keys.begin() + rootKeyPos, siblingNode.keys.front());
        siblingNode.keys.erase(siblingNode.keys.begin());
    }

    return true;
}

template <typename T>
BTreeNode<T> &BTreeNode<T>::replaceKeyWithChildKey(const T &key)
{
    int keyIndex = indexOfKey(key);
    // The children of a root key given its index are at index and index+1 in the list of children

    // Try to see if you can replace with
    std::shared_ptr<BTreeNode<T>> borrowerNodePtr = children[keyIndex];
    BTreeNode<T> borrowerNode = *borrowerNodePtr;
}