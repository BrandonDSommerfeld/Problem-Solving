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
#include "math_signed.cpp"


static bool* composite;
static std::vector<int> primes;

int rad(int n)
{
    int ans = 1;
    for(int i = 0; n > 1; i++)
    {
        if(n % primes[i] == 0)
        {
            ans *= primes[i];
            n /= primes[i];
        }
        while(n % primes[i] == 0)
        {
            n /= primes[i];
        }
    }
    return ans;
}

struct pair
{
    int num;
    int rad;
};

bool operator< (pair p1, pair p2)
{
    if(p1.rad < p2.rad)
    {
        return true;
    }
    if(p1.rad > p2.rad)
    {
        return false;
    }
    return p1.num < p2.num;
}

int main ()
{
    //Define rad(n) as the product of all distinct prime factors of n
    //For 1 <= n <= 100000,
    //find which number is 10000th in a sorted list
    //by rad value, then by n if tied
    
    int limit = 1000000;
    composite = new bool[limit];
    for(int i{2}; i < 1000; i++)
    {
        if(!composite[i])
        {
            for(int j{2}; i*j < limit; j++)
            {
                composite[i*j] = true;
            }
        }
    }

    for(int i = 2; i < limit; i++)
    {
        if(!composite[i])
        {
            primes.push_back(i);
        }
    }

    pair *nums = new pair[100000];
    for(int i = 1; i <= 100000; i++)
    {
        pair temp{};
        temp.num = i;
        temp.rad = rad(i);
        nums[i-1] = temp;
    }

    std::sort(nums, nums+100000);
    std::cout << nums[9999].num << '\n';
    return 0;
}