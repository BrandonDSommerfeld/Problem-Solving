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

int totient(int num)
{
    if(num == 1) return 1;
    if(!composite[num])
    {
        return num-1;
    }
    
    for(int i = 0; primes[i] <= num/2; i++)
    {
        if(num % primes[i] == 0)
        {
            int power = 0;
            while(num % primes[i] == 0)
            {
                num /= primes[i];
                power++;
            }
            int result = 1;
            for(int j = 0; j < power-1; j++)
            {
                result *= primes[i];
            }
            result *= primes[i]-1;
            return result*totient(num);
        }
    }
    return 0;
}

int main ()
{
    //Consider the remainders when (a-1)^n + (a+1)^n by a^2
    //over all n. 
    //For 3 <= a <= 1000, consider the maximum possible remainder
    //and find the sum of all of these
    
    int limit = 10000000;
    composite = new bool[limit];
    for(int i{2}; i < 4000; i++)
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

    //Pretty brute force, use the totient function
    //with euler's theorem to be faster
    //Only the a terms matter, since the constant terms
    //cancel and all greater are divisible by a^2
    math::Unsigned total{0};
    for(int i = 3; i <= 1000; i++)
    {
        int tot = totient(i*i);
        int max = 0;
        for(int j = 0; j < tot; j++)
        {
            if((2*i*j)%(i*i) > max)
            {
                max = (2*i*j)%(i*i);
            }
        }
        total += max;
    }
    std::cout << total << '\n';
    return 0;
}