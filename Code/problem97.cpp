#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include "math_unsigned.cpp"

int indexOf(std::vector<long long>& nums, long long elem)
{
    for(int i = 0; i < nums.size(); i++)
    {
        if(nums[i] == elem)
        {
            return i;
        }
    }
    return -1;
}

int main ()
{
    //Find the last 10 digits of the prime number
    // 28433 * 2^7830457 + 1

    //Use the repeating nature of powers to compute 2 to that power
    //mod 10^10

    
    return 0;
}