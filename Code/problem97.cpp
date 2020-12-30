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

    //Just track last 10 digits of the powers of 2
    long long num = 1;
    for(int i = 0; i < 7830457; i++)
    {
        num = (num*2)%10000000000L;
    }
    num = (num*28433)%10000000000L;
    num++;
    std::cout << num << '\n';


    
    return 0;
}