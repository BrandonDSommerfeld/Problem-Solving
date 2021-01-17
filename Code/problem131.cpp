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
static std::vector<long long> primes;
static std::set<long long> cubes;

bool recursiveIsCube(math::Unsigned low, math::Unsigned& high,
math::Unsigned& num)
{
    if(low == high)
    {
        return low*low*low == num;
    }
    math::Unsigned mid = (low+high)/2;
    math::Unsigned guess = mid*mid*mid;
    if(guess < num)
    {
        return recursiveIsCube(mid+1, high, num);
    }
    if(guess > num)
    {
        return recursiveIsCube(low, mid, num);
    }
    return true;
}

bool isCube(math::Unsigned num)
{
    math::Unsigned guess = 1;
    while(guess*guess*guess <= num)
    {
        guess *= 2;
    }
    return recursiveIsCube(guess/2, guess, num);
}

int main ()
{
    //Given a prime p, sometimes there exists an n such that
    //n^3 + pn^2 = k^3
    //The n is unique, if it exists
    //Figure out how many primes below 1 million have such an n

    //n^2(n+p) = k^3
    //Note that n+p and n^2 share no factors, so we need
    //Both to be cubes of their own, drastically lowers
    //search space
    static constexpr int limit = 1000000;
    composite = new bool[limit];
    for(int i = 0; i < limit; i++)
    {
        composite[i] = false;
    }
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
    composite[0] = true;
    composite[1] = true;

    for(int i = 2; i < limit; i++)
    {
        if(!composite[i])
        {
            primes.push_back(i);
        }
    }

    std::set<long long> cubes{};
    for(long long i = 1; i <= 1000; i++)
    {
        cubes.insert(i*i*i);
    }

    int num = 0;
    for(int i = 0; i < primes.size() && primes[i] < limit; i++)
    {
        int p = primes[i];
        auto iter = cubes.cbegin();
        while(iter != cubes.end())
        {
            if(cubes.find(*iter+p) != cubes.end())
            {
                num++;
                break;
            }
            iter++;
        }
    }
    std::cout << num << '\n';
    return 0;
}