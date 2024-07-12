#include <cmath>
#include <stdio.h>
#include <unordered_set>
#include <utility>
#include <string>

using namespace std;

// #include <boost/functional/hash.hpp>

struct pairHashFunction
{
    size_t operator()(const pair<int, int> &p) const
    {
        size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);

        return seed;
        // return p.first ^ p.second;
        // uintmax_t hash = std::hash<int>{}(p.first);
        // hash <<= sizeof(uintmax_t) * 4;
        // hash ^= std::hash<int>{}(p.second);
        // return std::hash<uintmax_t>{}(hash);
    }

    static void hash_combine(size_t &seed, int v)
    {
        seed ^= v + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};

class Solution
{
public:
    string longestPalindrome(string s)
    {
        return byIntuitionBottomUp(s);
    }

    // string manacherAlgo(string s){

    // }

    string byIntuitionBottomUp(string &s)
    {
        int length = s.length();
        bool **foundPalindromes = new bool *[length];

        for (int i = 0; i < length; i++)
        {
            foundPalindromes[i] = new bool[length];
        }

        for (int i = 0; i < length; i++)
        {
            for (int k = 0; k < length; k++)
            {
                foundPalindromes[i][k] = false;
            }
        }

        int maximumLength = 1;
        int startOfMaximum = 0;

        try
        {

            for (int subStringLength = 1; subStringLength <= length; subStringLength++)
            {
                int lastStart = length - subStringLength;
                for (int start = 0; start <= lastStart; start++)
                {
                    int end = start + subStringLength - 1;
                    // printf("Before Start: %d, End: %d; Length: %d\n", start, end, length);

                    if (isAPalindromeBottomUp(s, start, end, foundPalindromes))
                    {
                        // printf("Found Start: %d, End: %d; Length: %d\n", start, end, length);
                        foundPalindromes[start][end] = true;
                        if (maximumLength < subStringLength)
                        {
                            maximumLength = subStringLength;
                            startOfMaximum = start;
                        }
                    };
                }
            }
        }
        catch (...)
        {
            for (int i = 0; i < length; i++)
            {
                delete[] foundPalindromes[i];
            }
            delete[] foundPalindromes;

            throw runtime_error("failed");
        }

        for (int i = 0; i < length; i++)
        {
            delete[] foundPalindromes[i];
        }
        delete[] foundPalindromes;

        return s.substr(startOfMaximum, maximumLength);
    }

    bool isAPalindromeBottomUp(string &s, int start, int end, bool **foundPalindromes)
    {
        int length = end - start + 1;

        if (length == 1)
        {
            return true;
        };

        if (length == 2)
        {
            return s[start] == s[end];
        }

        if (s[start] != s[end])
            return false;

        // if(palindromicRanges.contains(s.substr(start, length))) return true;

        bool isEven = length % 2 == 0;

        int middle = start + ceil((double)length / (double)2) - 1;

        if (isEven && s[middle] != s[middle + 1])
        {
            return false;
        }

        int currentStart = start + 1;
        int currentEnd = end - 1;
        int lastStart = middle;
        int lastEnd = middle;
        // printf("Initial start: %d, end: %d, String: %s\n", currentStart, currentEnd, s.substr(start, length).c_str());

        if (isEven)
        {
            lastStart = middle - 1;
            lastEnd = middle + 2;
        }
        else
        {
            lastStart = middle - 1;
            lastEnd = middle + 1;
        }

        for (; currentStart <= lastStart && currentEnd >= lastEnd; currentStart++, currentEnd--)
        {
            // printf("Start: %d %c, End: %d %c\n", currentStart, s[currentStart], currentEnd, s[currentEnd]);
            if (!foundPalindromes[currentStart][currentEnd])
            {
                return false;
            }
            if (s[currentStart] != s[currentEnd])
            {
                return false;
            }
            // palindromicRanges.insert(s.substr(currentStart, currentEnd-currentStart+1));
        }

        return true;
    }

    string byIntuition(string &s)
    {
        int length = s.length();
        unordered_set<string> foundPalindromicRanges;

        for (int subStringLength = length; subStringLength > 0; subStringLength--)
        {
            int lastStart = length - subStringLength + 1;
            for (int start = 0; start <= lastStart; start++)
            {
                int end = start + subStringLength - 1;
                if (isAPalindrome(s, start, end, foundPalindromicRanges))
                    return s.substr(start, subStringLength);
            }
        }

        return s.substr(0, 1);
    }

    bool isAPalindrome(string &s, int start, int end, unordered_set<string> &palindromicRanges)
    {
        int length = end - start + 1;

        if (length == 1)
            return true;

        // if(palindromicRanges.contains(s.substr(start, length))) return true;

        bool isEven = length % 2 == 0;

        int middle = start + ceil((double)length / (double)2) - 1;

        if (isEven && s[middle] != s[middle + 1])
        {
            return false;
        }

        int currentStart = middle;
        int currentEnd = middle;
        // printf("Initial start: %d, end: %d, String: %s\n", currentStart, currentEnd, s.substr(start, length).c_str());

        if (isEven && length > 2)
        {
            currentStart--;
            currentEnd += 2;
        }
        else if (isEven)
        {
            currentEnd++;
        }
        else
        {
            currentStart--;
            currentEnd++;
        }

        for (; currentStart >= start && currentEnd <= end; currentStart--, currentEnd++)
        {
            // printf("Start: %d %c, End: %d %c\n", currentStart, s[currentStart], currentEnd, s[currentEnd]);
            if (s[currentStart] != s[currentEnd])
            {
                return false;
            }
            // palindromicRanges.insert(s.substr(currentStart, currentEnd-currentStart+1));
        }

        return true;
    }
};