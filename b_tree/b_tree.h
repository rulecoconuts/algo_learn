#include <vector>
#include <memory>

template <typename T>
class BTreeNode
{
private:
    std::vector<T> keys;
    std::weak_ptr<BTreeNode<T>> parent;
    std::vector<std::shared_ptr<BTreeNode<T>>> children;

public:
    std::vector<T> getKeys() const
    {
        return keys;
    }

    BTreeNode<T> getParent() const
    {
        return *parent;
    }
};

class BTree
{
};