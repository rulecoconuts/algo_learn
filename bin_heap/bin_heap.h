#include <vector>
#include <cmath>

class BinHeap
{
private:
    std::vector<int> content;
    bool isMaxInternal = true;

    int parentIndexOf(int index)
    {
        return floor((index - 1) / 2);
    }

    int leftIndexOf(int index)
    {
        return index * 2 + 1;
    }

    int rightIndexOf(int index)
    {
        return index * 2 + 2;
    }

    void maxHeapify(int parentIndex, int size)
    {
        int leftIndex = leftIndexOf(parentIndex);
        int rightIndex = rightIndexOf(parentIndex);
        int largestIndex = parentIndex;

        if (leftIndex < size && content[leftIndex] > content[parentIndex])
        {
            largestIndex = leftIndex;
        }

        if (rightIndex < size && content[rightIndex] > content[largestIndex])
        {
            largestIndex = rightIndex;
        }

        if (largestIndex != parentIndex)
        {
            // Swap the value of parent with the value of its largest child
            exchange(parentIndex, largestIndex);

            // Proceed to heapify from the largest child's position, that now contains the parent's value
            maxHeapify(largestIndex, size);
        }
    }

    void minHeapify(int parentIndex, int size)
    {
        int leftIndex = leftIndexOf(parentIndex);
        int rightIndex = rightIndexOf(parentIndex);
        int smallestIndex = parentIndex;

        if (leftIndex < size && content[leftIndex] < content[parentIndex])
        {
            smallestIndex = leftIndex;
        }

        if (rightIndex < size && content[rightIndex] < content[smallestIndex])
        {
            smallestIndex = rightIndex;
        }

        if (smallestIndex != parentIndex)
        {
            // Swap the value of parent with the value of its largest child
            exchange(parentIndex, smallestIndex);

            // Proceed to heapify from the largest child's position, that now contains the parent's value
            minHeapify(smallestIndex, size);
        }
    }

    void exchange(int indexA, int indexB)
    {
        int temp = content[indexA];
        content[indexA] = content[indexB];
        content[indexB] = temp;
    }

    void maxSiftUp(int index)
    {
        int currentIndex = index;
        while (index > 0 && content[parentIndexOf(currentIndex)] < content[currentIndex])
        {
            int parentIndex = parentIndexOf(currentIndex);
            exchange(parentIndex, currentIndex);
            currentIndex = parentIndex;
        }
    }

    void minSiftUp(int index)
    {
        int currentIndex = index;
        while (index > 0 && content[parentIndexOf(currentIndex)] > content[currentIndex])
        {
            int parentIndex = parentIndexOf(currentIndex);
            exchange(parentIndex, currentIndex);
            currentIndex = parentIndex;
        }
    }

public:
    BinHeap(bool isMax)
    {
        setIsMax(isMax);
    }

    void setIsMax(bool isMax)
    {
        this->isMaxInternal = isMax;
    }

    bool isMax()
    {
        return isMaxInternal;
    }

    void insert(int value)
    {
        content.push_back(value);

        if (isMax())
        {
            maxSiftUp(content.size() - 1);
        }
        else
        {
            minSiftUp(content.size() - 1);
        }
    }

    int pop()
    {
        int desiredValue = content[0];

        int lastIndex = content.size() - 1;

        if (lastIndex != 0)
        {
            content[0] = content[lastIndex];
        }

        content.pop_back();
        int size = content.size();

        if (size > 0)
        {
            if (isMax())
            {
                maxHeapify(0, size);
            }
            else
            {
                minHeapify(0, size);
            }
        }

        return desiredValue;
    }
};