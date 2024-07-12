/// Goal: Calculate the optimal grouping to perform the the multiplication of a sequence of matrices with the least number of computations

long costOfLastMultiply(int *dimensions, int start, int split, int end)
{
    return dimensions[start] * dimensions[split + 1] * dimensions[end + 1];
}

int main()
{
}