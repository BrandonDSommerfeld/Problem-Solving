#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find the least number n such that the number of partitions
    //Of n is divisible by 1000000

    //Similar to previous coin counting problems, just much bigger
    //Figured out that the full 2D array isn't needed, just the
    //previous row, so you only bring one row down with you 
    //to save memory


    constexpr int limit = 100000;
    
    int* ways = new int[limit+1];
    for(int i = 0; i <= limit; i++)
    {
        ways[i] = 0;
    }
    ways[0] = 1;
    for(int i = 0; i < limit; i++)
    {
        int* next = new int[limit+1];
        for(int j = 0; j <= i; j++)
        {
            next[j] = ways[j];
        }
        for(int j = i+1; j <= limit; j++)
        {
            next[j] = (ways[j] + next[j-i-1])%1000000;
        }
        if(next[i+1] == 0)
        {
            std::cout << (i+1) << '\n';
            return 0;
        }
        delete[] ways;
        ways = next;
    }
    
    std::cout << "Finished\n";
    return 0;
}

