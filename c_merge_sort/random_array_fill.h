#include <fstream>
#include <cmath>

void fillArrayRandomly(int *array, size_t size)
{
    std::ifstream randomDevice("/dev/urandom", std::ios::in | std::ios::binary);

    try
    {
        if (randomDevice)
        {
            randomDevice.read((char *)array, size);
        }

        randomDevice.close();
    }
    catch (...)
    {
        randomDevice.close();
    }
}

void fillArrayRandomlyRanged(int *array, size_t size, int min, int max)
{
    fillArrayRandomly(array, size);

    for (int i = 0; i < size / sizeof(int); i++)
    {
        array[i] = array[i] % (max + 1);

        if (array[i] < min)
        {
            array[i] = (min + abs(array[i])) % (max + 1);
        }
    }
}