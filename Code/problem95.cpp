#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include "math_unsigned.cpp"


int divisorSum(int num)
{
    int sum = 1;
    for(int i = 2; i <= std::sqrt(num); i++)
    {
        if(num % i == 0)
        {
            sum += i;
            if(num/i != i)
            {
                sum += num/i;
            }
        }
    }
    return sum;
}

int index(std::vector<int> nums, int elem)
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

int chainLength(int num, std::vector<int> seen)
{
    num = divisorSum(num);
    if(num > 1000000)
    {
        return 0;
    }
    int ind = index(seen, num);
    if(ind != -1)
    {
        if(ind == 0)
        {
            return seen.size();
        }
        return 0;
    }
    seen.push_back(num);
    return chainLength(num, seen);
}

int main ()
{
    //Given a number, compute the sum of its proper divisors
    //Some numbers are perfect and go to themselves, and other
    //Numbers form an amicable chain

    //Find the smallest member of the longest amicable chain,
    //Where none of the members exceed 1 million

    //Just recursively go over each number and see if it arrives at
    //itself
    int best = 0;
    int place = 0;
    for(int i = 1; i <= 1000000; i++)
    {
        std::vector<int> temp{};
        temp.push_back(i);
        int length = chainLength(i, temp);
        if(length > best)
        {
            best = length;
            place = i;
        }
    }
    std::cout << best << '\n';
    std::cout << place << '\n';
    return 0;
}