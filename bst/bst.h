#include <memory>
class Node
{
private:
    int value;
    using pointer = std::shared_ptr<Node>;
    pointer prev;
    pointer next;

public:
    Node(int key, pointer left = nullptr, pointer right = nullptr) : value(key), prev(left), next(right) {}
    void setKey(int key)
    {
        this->value = key;
    }

    int getKey()
    {
        return value;
    }

    void setLeft(pointer left)
    {
        this->prev = left;
    }

    pointer getLeft()
    {
        return prev;
    }

    bool hasLeft()
    {
        return prev != nullptr;
    }

    void setRight(pointer right)
    {
        this->next = right;
    }

    pointer getRight()
    {
        return next;
    }

    bool hasRight()
    {
        return next != nullptr;
    }
};