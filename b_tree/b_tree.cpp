#include <b_tree.h>
#include <cmath>
#include <stdexcept>

template <typename T>
int BTree<T>::getMaxNKeys() const
{
    return maxNKeys;
}

template <typename T>
int BTree<T>::getMinNKeys() const
{
    return floor((double)getMaxNKeys() / 2.0);
}

template <typename T>
void BTree<T>::insert(const T &key)
{
    // If there is no root. Create a root node
    if (root == nullptr)
    {
        root = std::make_shared({key});
        return;
    }

    // There is a root. find optimal node to insert into
    BTreeNode nodeToInsertInto = findOptimalInsertionNode(key);

    // Insert into node
    insertInto(key, nodeToInsertInto);
}

template <typename T>
void BTree<T>::insertInto(const T &key, BTreeNode<T> &node)
{
    node.insertKey(key);

    BTreeNode<T> *currentNode = &node;

    // Continue splitting and moving up the tree until we find a valid node
    while (currentNode->nKeys() > getMaxNKeys())
    {
        // Number of keys is invalid after insertion. Split the node
        if (!currentNode->hasParent())
        {
            // Node is root
            splitRoot(*currentNode);
            return;
        }

        BTreeNode<T> parent = *(currentNode->getParent().lock());

        parent.splitChild(*currentNode);
        currentNode = &parent;
    }
}

template <typename T>
void BTree<T>::splitRoot(BTreeNode<T> &root)
{
    BTreeNodeSplitResult<T> splitResult = root.split();
    std::shared_ptr<BTreeNode<T>> newRoot = std::make_shared({splitResult.getRootKey()});
    newRoot->insertChildAtBack(splitResult.getNode());
    newRoot->insertChildAtBack(root);
    this->root = newRoot;
}

template <typename T>
BTreeNode<T> &BTree<T>::findOptimalInsertionNode(const T &key)
{
    BTreeNode<T> *currentNode = &(*root);

    while (currentNode->nChildren() > 0)
    {
        currentNode = &(currentNode->findNextNode(key));
    }

    return *currentNode;
}

template <typename T>
T *BTree<T>::find(const T &key)
{
    BTreeNode<T> *currentNode = &(*root);
    T *keyInTree = nullptr;

    // Keep searching until we find the key or there are no more levels to search
    while ((keyInTree = currentNode->findKey(key)) == nullptr && currentNode->nChildren() > 0)
    {
        currentNode = &(currentNode->findNextNode(key));
    }

    return keyInTree;
}

template <typename T>
void BTree<T>::remove(const T &key)
{
    BTreeNode<T> *currentNode = &(*root);
    T *keyInTree = nullptr;

    // Keep searching until we find the key or there are no more levels to search
    while ((keyInTree = currentNode->findKey(key)) == nullptr && currentNode->nChildren() > 0)
    {
        currentNode = &(currentNode->findNextNode(key));
    }

    if (keyInTree == nullptr)
        return;

    if (currentNode->nChildren() > 0)
    {
        // Remove key and replace it with a key from one of the children
        removeFromNonLeafNode(key, *currentNode);
        return;
    }

    currentNode->removeKey(key);

    // If node is root and it still has keys, ignore minimum number of keys requirement
    if (!currentNode->hasParent() && currentNode->nKeys() > 0)
    {
        return;
    }
    else if (!currentNode->hasParent())
    {
        // Node is root and it has run out of keys. Destroy root
        root = nullptr;
        return;
    }

    // Node is not root and it does not have any children

    // Fix invalid node key count
    fixLessThanMinInvalidity(*currentNode);
}

template <typename T>
void BTree<T>::fixLessThanMinInvalidity(BTreeNode<T> &node)
{
    int minNKeys = getMinNKeys();
    BTreeNode<T> *currentNode = &node;

    while (currentNode->nKeys() < minNKeys && currentNode->hasParent())
    {
        // Assume there is a parent for now
        BTreeNode<T> parent = &(currentNode->getParent().lock());
        int index = parent.indexOfChild(*currentNode);
        bool borrowed = parent.borrowFromSibling(index, getMaxNKeys());

        if (!borrowed)
        {
            // Merge instead
            parent.merge(index);
        }

        currentNode = &parent;
    }
}

template <typename T>
void BTree<T>::removeFromNonLeafNode(const T &key, BTreeNode<T> &node)
{
    // We cannot simply remove the key, so we must replace it with a key from one of its children
    BTreeNode<T> &childNodeThatReplacementKeyWasFrom = replaceNodeKeyFromSubTree(key, node);

    fixLessThanMinInvalidity(childNodeThatReplacementKeyWasFrom);
}

template <typename T>
BTreeNode<T> &BTree<T>::replaceNodeKeyFromSubTree(const T &key, BTreeNode<T> &node)
{
    BTreeNode<T> &leafNodeThatReplacementKeyWasFrom;

    // We will start by only considering the valid node on the left subtree
    BTreeNode<T> &validLeftNode = findRightmostLeafOfLeftSubtree(key, node);

    // If the left leaf node has just the minimum number of keys, taking any keys from it would make it invalid.
    // The right leaf node could either have the minimum or more number of keys. This gives us a chance to avoid
    // the cost of fixing a node with an invalid number of keys
    T replacementKey;

    if (validLeftNode.nKeys() > getMinNKeys())
    {
        // The left leaf node can afford to get a key taken from it.
        leafNodeThatReplacementKeyWasFrom = validLeftNode;
        replacementKey = validLeftNode.popLastKey();
    }
    else
    {
        // The left leaf node can afford to get a key taken from it.
        // Try the right leaf node
        BTreeNode<T> &validRightNode = findLeftmostLeafOfRightSubtree(key, node);
        leafNodeThatReplacementKeyWasFrom = validRightNode;
        replacementKey = validRightNode.popFirstKey();
    }

    node.removeKey(key);
    node.insertKey(replacementKey);

    return leafNodeThatReplacementKeyWasFrom;
}

template <typename T>
BTreeNode<T> &BTree<T>::findRightmostLeafOfLeftSubtree(const T &key, BTreeNode<T> startNode)
{
    BTreeNode<T> currentNode = startNode.getLeftChild(key);

    while (currentNode.nChildren() > 0)
    {
        currentNode = currentNode.lastChild();
    }

    return currentNode;
}

template <typename T>
BTreeNode<T> &BTree<T>::findLeftmostLeafOfRightSubtree(const T &key, BTreeNode<T> startNode)
{
    BTreeNode<T> currentNode = startNode.getRightChild(key);

    while (currentNode.nChildren() > 0)
    {
        currentNode = currentNode.firstChild();
    }

    return currentNode;
}