
void exchange(int *arr, int indexA, int indexB)
{
    int temp = arr[indexA];
    arr[indexA] = arr[indexB];
    arr[indexB] = temp;
}

int partition(int *arr, int start, int end)
{
    int pivotValue = arr[start];

    int smallIndex = start;

    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] < pivotValue)
        {
            smallIndex++;
            exchange(arr, smallIndex, i);
        }
    }

    exchange(arr, start, smallIndex);

    return smallIndex;
}

void quickSortRecurse(int *arr, int start, int end)
{
    int length = end - start + 1;

    if (length < 2)
        return;

    int pivotIndex = partition(arr, start, end);

    quickSortRecurse(arr, start, pivotIndex - 1);
    quickSortRecurse(arr, pivotIndex + 1, end);
}

void quickSort(int *arr, int length)
{
    quickSortRecurse(arr, 0, length - 1);
}