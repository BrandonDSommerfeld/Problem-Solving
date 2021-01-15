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

int main ()
{
    //Given a prime p, sometimes there exists an n such that
    //n^3 + pn^2 = k^3
    //The n is unique, if it exists
    //Figure out how many primes below 1 million have such an n

    //Factor as
    //n^2(n + p) = k^3
    static constexpr int limit = 1000000;
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
    return 0;
}