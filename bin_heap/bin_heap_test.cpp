#include "bin_heap.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
    int size = atoi(argv[1]);
    char *strEnd = nullptr;
    unsigned long max = strtoul(argv[2], &strEnd, 10);

    BinHeap heap(false);
    unsigned int values[size] = {};

    ifstream urandom("/dev/urandom", ios::in | ios::binary);

    // Read [size] numbers from random generator device
    try
    {
        if (urandom)
        {
            cout << "About to read from urandom" << endl;

            urandom.read(reinterpret_cast<char *>(values), sizeof(unsigned int) * size);
            if (urandom)
            {
                cout << "Succesfully read from urandom" << endl;
            }
            else
            {
                cout << "Failed to read from urandom" << endl;
            }
        }
        else
        {
            cout << "Failed to read from urandom" << endl;
        }
    }
    catch (...)
    {
        urandom.close();
    }

    for (int i = 0; i < size; i++)
    {
        values[i] = values[i] % max;

        heap.insert(values[i]);

        cout << values[i];

        if (i == size - 1)
        {
            cout << endl;
        }
        else
        {
            cout << ", ";
        }
    }

    for (int i = 0; i < size; i++)
    {
        cout << heap.pop();

        if (i == size - 1)
        {
            cout << endl;
        }
        else
        {
            cout << ", ";
        }
    }
}