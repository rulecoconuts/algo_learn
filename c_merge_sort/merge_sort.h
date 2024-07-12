#include <cmath>
#include <cstring>

void merge(int *arr, int start, int split, int end)
{
    int leftStart = start;
    int rightStart = split + 1;

    int length = end - start + 1;

    const int leftSize = split - leftStart + 1;
    const int rightSize = end - (split + 1) + 1;

    int left[leftSize];
    memcpy((char *)left, (char *)(arr + start), sizeof(int) * leftSize);

    int right[rightSize];
    memcpy((char *)right, (char *)(arr + split + 1), sizeof(int) * rightSize);

    int leftIndex = 0;
    int rightIndex = 0;

    int lastLeft = leftSize - 1;
    int lastRight = rightSize - 1;

    for (int i = start; i <= end; i++)
    {
        if (rightIndex > lastRight || (leftIndex <= lastLeft && left[leftIndex] < right[rightIndex]))
        {
            // Left is less than right. Put left in array.
            // Move left forward
            arr[i] = left[leftIndex];
            leftIndex++;
        }
        else
        {
            arr[i] = right[rightIndex];
            rightIndex++;
        }
    }
}

void mergeSortRecurse(int *arr, int start, int end)
{
    // Calculate split
    int length = end - start + 1;

    if (length == 1)
        return;

    if (length == 2)
    {
        if (arr[end] < arr[start])
        {
            // Put the two elements in the right order
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
        }
        return;
    }

    int split = start + ceil((double)length / (double)2) - 1;

    // if ((start == 5 && split == 2) || ((split + 1) == 5 && end == 2))
    // {
    //     int j = 5;
    // }

    // Perform mergeSort on left and right splits
    mergeSortRecurse(arr, start, split);
    mergeSortRecurse(arr, split + 1, end);

    // Merge splits
    merge(arr, start, split, end);
}

void mergeSort(int *arr, int length)
{
    mergeSortRecurse(arr, 0, length - 1);
}
