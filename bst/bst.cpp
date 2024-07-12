#include "bst.h"

std::shared_ptr<Node> search(int key, std::shared_ptr<Node> root)
{
    if (root == nullptr)
        return 0;
    if (key == root->getKey())
        return root;

    if (key < root->getKey())
        return search(key, root->getLeft());
    else
        return search(key, root->getRight());
}

void insert(int key, std::shared_ptr<Node> root)
{
    if (root == nullptr)
        return;

    if (key == root->getKey())
        return;

    if (key < root->getKey())
    {
        if (root->hasLeft())
        {
            insert(key, root->getLeft());
        }
        else
        {
            root->setLeft(std::make_shared<Node>(key));
        }
    }
    else
    {
        if (root->hasRight())
        {
            insert(key, root->getLeft());
        }
        else
        {
            root->setRight(std::make_shared<Node>(key));
        }
    }
}

std::shared_ptr<Node> deleteKey(int key, std::shared_ptr<Node> root)
{
    if (root == nullptr)
        return;

    if (root->getKey() == key)
    {
        // key is at root.
        std::shared_ptr<Node> newHead = nullptr;

        if (root->hasLeft())
        {
            // New head will be the greatest node in the range of left node (inclusive) and right node (exclusive)
            // i.e smack dab in the middle, more or less
            if (root->getLeft()->hasRight())
            {

                newHead = popLargest(root->getLeft());
                newHead->setLeft(root->getLeft());
                newHead->setRight(root->getRight());
            }
            else
            {
                newHead = root->getLeft();
            }
        }
        else
        {
            // right is the only candidate
            newHead = std::shared_ptr(root->getRight());
        }

        root->setLeft(nullptr);
        root->setRight(nullptr);

        return newHead;
    }

    if (key < root->getKey())
    {
        // Search for key to be deleted in left
        root->setLeft(deleteKey(key, root->getLeft()));
    }
    else
    {
        // Search for key to be deleted in right
        root->setRight(deleteKey(key, root->getRight()));
    }

    return root;
}

void replaceLeft(std::shared_ptr<Node> newLeft, std::shared_ptr<Node> root)
{
    std::shared_ptr<Node> currentLeft = std::shared_ptr(root->getLeft());
    root->setLeft(newLeft);

    if (currentLeft != nullptr)
    {
        replaceLeft(currentLeft, root->getRight());
    }
}

std::shared_ptr<Node> popLargest(std::shared_ptr<Node> root)
{
    if (root == nullptr)
        return nullptr;

    std::shared_ptr<Node> parentToRightMost = root;

    while (parentToRightMost->hasRight() && parentToRightMost->getRight()->hasRight())
    {
        parentToRightMost = parentToRightMost->getRight();
    }

    std::shared_ptr<Node> rightMost = parentToRightMost->getRight();

    if (rightMost->hasLeft())
    {
        parentToRightMost->setRight(rightMost->getLeft());
        rightMost->setLeft(nullptr);
    }
    else
    {
        parentToRightMost->setRight(nullptr);
    }

    return rightMost;
}

/// @brief Insert into an AVL tree. Perform self-balancing rotations
/// @param key
/// @param root
/// @param noPathCountsArg The number of path absences encountered before this root. [0] = left path absence, [1] = right path absence
void insertAVL(int key, std::shared_ptr<Node> root, int *noPathCountsArg = nullptr)
{
    if (root == nullptr)
        return;

    if (key == root->getKey())
        return;

    int *noPathsCount = noPathCountsArg;
    if (noPathsCount == nullptr)
    {
        // Initialize no paths count array in heap. All values are 0
        noPathCountsArg = new int[2]{};
    }

    try
    {

        if (key < root->getKey())
        {
            if (root->hasLeft())
            {
                recordPathAbsence(noPathsCount, true, root);
                insertAVL(key, root->getLeft(), noPathsCount);
            }
            else
            {
                root->setLeft(std::make_shared<Node>(key));
            }
        }
        else
        {
            if (root->hasRight())
            {
                recordPathAbsence(noPathsCount, false, root);
                insertAVL(key, root->getLeft(), noPathsCount);
            }
            else
            {
                root->setRight(std::make_shared<Node>(key));
            }
        }

        if (noPathCountsArg == nullptr)
        {
            delete[] noPathsCount;
        }
    }
    catch (std::exception &e)
    {
        if (noPathCountsArg == nullptr)
        {
            delete[] noPathsCount;
        }
        throw e;
    }
    catch (...)
    {
        if (noPathCountsArg == nullptr)
        {
            delete[] noPathsCount;
        }
    }
}

void recordPathAbsence(int *noPathsCount, bool movingLeft, std::shared_ptr<Node> root)
{
    if (movingLeft)
    {
        if (root->hasRight())
        {
            noPathsCount[1] = 0;
        }
        else
        {
            noPathsCount[1]++;
        }

        // Reset count for left
        noPathsCount[0] = 0;
    }
    else
    {
        if (root->hasLeft())
        {
            noPathsCount[0] = 0;
        }
        else
        {
            noPathsCount[0]++;
        }

        // Reset count for right
        noPathsCount[1] = 0;
    }
}

bool shouldRotateBasedOnPathAbsence(int *noPathsCount, std::shared_ptr<Node> root)
{
    return noPathsCount[0] > 0 || noPathsCount[1] > 0;
}

int main()
{
}