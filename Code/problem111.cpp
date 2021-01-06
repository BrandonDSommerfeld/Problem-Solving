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

static std::vector<int> primes;

bool isPrime(long long num)
{
    for(int i = 0; primes[i] <= std::sqrt(num); i++)
    {
        if(num % primes[i] == 0)
        {
            return false;
        }
    }
    return true;
}

int function(int d, int num)
{
    
}

int main ()
{
    //Consider all 10 digit prime numbers
    //For each digit 0-9, find the primes which have the most
    //of that digit
    //Find the sum of all of these primes over all digits
    bool *composite = new bool[100000];
    for(int i = 2; i < 100000; i++)
    {
        composite[i] = false;
    }
    for(int i = 2; i < 1000; i++)
    {
        if(!composite[i])
        {
            for(int k = 2; i*k < 100000; k++)
            {
                composite[i*k] = true;
            }
        }
    }

    primes = *(new std::vector<int>{});
    primes.reserve(10000);
    for(int i = 2; i < 100000; i++)
    {
        if(!composite[i])
        {
            primes.push_back(i);
        }
    }

    for(int d = 0; d < 10; d++)
    {

    }
    return 0;
}