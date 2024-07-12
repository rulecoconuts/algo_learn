#include <cmath>
#include <stdio.h>
#include <vector>

using namespace std;
class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int size1 = nums1.size();
        int size2 = nums2.size();
        long combinedSize = size1 + size2;
        bool isOdd = (combinedSize % 2) == 1;
        int medianIndex = ceil((double)combinedSize / (double)2) - 1;

        int index1 = 0;
        int index2 = 0;
        int combinedIndex = 0;
        double median = 0;

        while (combinedIndex < combinedSize)
        {
            bool isIndex1Current = isFirstIndexCurrent(index1, index2, nums1, nums2, size1, size2);
            bool isIndex1Next;

            if (isIndex1Current)
            {
                isIndex1Next = isFirstIndexCurrent(index1 + 1, index2, nums1, nums2, size1, size2);
            }
            else
            {
                bool isIndex2Next = isFirstIndexCurrent(index2 + 1, index1, nums2, nums1, size2, size1);
                isIndex1Next = !isIndex2Next;
            }

            if (combinedIndex == medianIndex)
            {

                if (isIndex1Current)
                {
                    median = nums1[index1];
                }
                else
                {
                    median = nums2[index2];
                }

                if (!isOdd)
                {
                    if (isIndex1Next && isIndex1Current)
                    {
                        median += nums1[index1 + 1];
                    }
                    else if (!isIndex1Next && !isIndex1Current)
                    {
                        median += nums2[index2 + 1];
                    }
                    else if (isIndex1Next)
                    {
                        median += nums1[index1];
                    }
                    else
                    {
                        median += nums2[index2];
                    }
                    median /= 2;
                }
                break;
            }

            if (isIndex1Current && !isIndex1Next)
            {
                index1++;
            }
            else if (isIndex1Current && isIndex1Next)
            {
                index1++;
            }
            else
            {
                index2++;
            }

            combinedIndex++;
        }

        return median;
    }

    bool isFirstIndexCurrent(int index1, int index2, vector<int> &nums1, vector<int> &nums2, int size1, int size2)
    {
        bool result = false;

        if (index1 < size1 && index2 < size2)
        {
            // Both indexes are valid
            result = nums1[index1] < nums2[index2];
        }
        else if (index1 < size1)
        {
            // Index 1 is valid. Move it forward
            result = true;
        }
        else
        {
            // Index 2 is valid. Move it forward
            result = false;
        }
        return result;
    }
};