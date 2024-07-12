#include "quick_sort.h"
#include <iostream>
#include "../c_merge_sort/random_array_fill.h"

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
    const int length = 25;
    int arr[length];

    fillArrayRandomlyRanged(arr, sizeof(int) * length, 0, 14);

    printArr(arr, length);

    quickSort(arr, length);

    // Print arr
    printArr(arr, length);

    return 0;
}