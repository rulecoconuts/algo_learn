/**
 * TODO: Find an alternative implementation that uses less shared_pointers
 */
#include <memory>
#include <list>
#include <unordered_map>
#include <stdio.h>

class Node
{
private:
    int value = 0;
    using pointer = std::shared_ptr<Node>;
    using weakPointer = std::weak_ptr<Node>;
    weakPointer prev;
    pointer next;

public:
    Node() {}
    Node(int value, weakPointer prev, pointer next = nullptr) : value(value), prev(prev), next(next) {}
    void setValue(int value)
    {
        this->value = value;
    }

    int getValue()
    {
        return value;
    }

    void setPrev(weakPointer prev)
    {
        this->prev = prev;
    }

    weakPointer getPrev()
    {
        return prev;
    }

    bool hasPrev()
    {
        return !prev.expired();
    }

    void setNext(pointer next)
    {
        this->next = next;
    }

    pointer getNext()
    {
        return next;
    }

    bool hasNext()
    {
        return next != nullptr;
    }
};

class LRUCache
{
private:
    std::shared_ptr<Node> head = nullptr;
    std::shared_ptr<Node> tail = nullptr;
    int capacity;
    using NodeMap = std::unordered_map<int, std::weak_ptr<Node>>;
    NodeMap nodeMap;
    int size = 0;

    void pushToEnd(std::shared_ptr<Node> newTail)
    {
        std::shared_ptr<Node> tailPtr = tail;

        if (tailPtr == nullptr)
        {
            // Tail ptr is null
            head = newTail;
            tail = newTail;
            newTail->setPrev(std::weak_ptr<Node>());
        }
        else if (head == tail)
        {
            // Head and tail are equal.
            // Make head point to newTail
            newTail->setPrev(std::weak_ptr(head));
            head->setNext(newTail);
            tail = newTail;
        }
        else
        {
            newTail->setPrev(std::weak_ptr(tailPtr));
            tailPtr->setNext(newTail);
            tail = newTail;
        }
        newTail->setNext(nullptr);
    }

    void removeHead()
    {

        if (head == tail)
        {
            // Head is equal to tail
            // Remove both
            head.reset();
            head = nullptr;

            tail.reset();
            tail = nullptr;
        }
        else if (size == 0)
        {
            return;
        }
        else
        {
            // Make head->next the new head
            std::shared_ptr<Node> newHead = std::shared_ptr(head->getNext());
            head.reset();
            head = newHead;

            head->setPrev(std::weak_ptr<Node>());
        }
    }

    /// @brief Move node to tail. Assuming that the cache is not empty
    /// @param node
    void moveToTail(std::shared_ptr<Node> node)
    {
        if (head == node)
        {
            // Node is the head
            if (size != 1)
            {
                removeHead();
                pushToEnd(node);
            }
        }
        else if (tail == node)
        {
            return;
        }
        else
        {
            std::weak_ptr<Node> prev = node->getPrev();
            std::shared_ptr<Node> next = node->getNext();
            prev.lock()->setNext(next);
            next->setPrev(prev);
            pushToEnd(node);
        }
    }

public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
        nodeMap.reserve(capacity);
    }

    int get(int key)
    {
        NodeMap::iterator iter = nodeMap.find(key);

        if (iter == nodeMap.end())
        {
            return -1;
        }
        else if (iter->second.expired())
        {
            return -1;
        }
        else
        {
            std::shared_ptr<Node> node = iter->second.lock();
            int value = node->getValue();

            moveToTail(node);

            return value;
        }
    }

    void put(int key, int value)
    {
        // Try to retrieve key Node from hash map
        NodeMap::iterator iter = nodeMap.find(key);

        if (iter == nodeMap.end() || iter->second.expired())
        {
            // Not found
            std::shared_ptr<Node> node = std::make_shared<Node>(value, std::weak_ptr<Node>(tail));
            pushToEnd(node);
            nodeMap[key] = std::weak_ptr(node);

            if (size == capacity)
            {
                // Cache is full.
                // Remove least-used node. i.e head
                removeHead();
            }
            else
            {
                size++;
            }
        }
        else
        {
            // Found
            // Replace in hashMap
            std::shared_ptr<Node> node = iter->second.lock();
            node->setValue(value);

            // Move node to most recent (tail)
            moveToTail(node);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */