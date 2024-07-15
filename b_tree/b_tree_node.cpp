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

    std::shared_ptr<BTreeNode<T>> newNode = std::make_shared(newKeys, newChildren);

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
BTreeNodeSplitResult<T> BTreeNode<T>::splitChild(int pos, int maxNKeys)
{
    std::shared_ptr<BTreeNode<T>> nodeToBeSplit = children[pos];
    BTreeNodeSplitResult<T> splitResult = nodeToBeSplit->split(maxNKeys);
    children.insert(children.begin() + pos, splitResult.getNode());
    keys.insert(keys.begin() + pos, splitResult.getRootKey());

    return splitResult;
}

template <typename T>
BTreeNodeSplitResult<T> BTreeNode<T>::splitChild(BTreeNode<T> &node, int maxNKeys)
{
    return splitChild(indexOfChild(node), maxNKeys);
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
void BTreeNode<T>::insertChildAtBack(BTreeNode<T> &child)
{
    children.push_back(std::make_shared(child));
}