#include "merge_sort.h"
#include <iostream>
#include "random_array_fill.h"

using namespace std;

void printArr(int *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << arr[i];

        if (i == length - 1)
        {
            cout << endl;
        }
        else
        {
            cout << ", ";
        }
    }
}

int main()
{
    const int length = 40;
    int arr[length];

    fillArrayRandomlyRanged(arr, sizeof(int) * length, -12, 0);

    printArr(arr, length);

    mergeSort(arr, length);

    // Print arr
    printArr(arr, length);

    return 0;
}