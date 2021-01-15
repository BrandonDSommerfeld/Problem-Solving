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

int gcd(int num1, int num2)
{
    if(num1 == 0)
    {
        return num2;
    }
    if(num2 == 0)
    {
        return num1;
    }
    if(num1 > num2)
    {
        return gcd(num1 % num2, num2);
    }
    return gcd(num1, num2 % num1);
}

int exp(long long b, int e, int n)
{
    long long ans = 1;
    while(e > 0)
    {
        if(e % 2 == 1)
        {
            ans = (ans*b) % n;
        }
        b = (b * b) % n;
        e /= 2;
    }
    return ans;
}

std::vector<int>* factors (int num)
{
    std::vector<int> *ans = new std::vector<int>{};
    for(int i = 0; i < primes.size() && primes[i] * primes[i] <= num; i++)
    {
        if(num % primes[i] == 0)
        {
            num /= primes[i];
            ans->push_back(primes[i]);
        }
        while(num % primes[i] == 0)
        {
            num /= primes[i];
        }
    }
    if(num > 1)
    {
        ans->push_back(num);
    }
    return ans;
}

int best(int tot, int mod)
{
    std::vector<int> *fac = factors(tot);
    int largest = tot;
    for(int j = 0; j < fac->size(); j++)
    {
        if(exp(10, tot/((*fac)[j]), mod) == 1)
        {
            largest = tot/((*fac)[j]);
        }
    }
    if(largest == tot)
    {
        return largest;
    }
    return best(largest, mod);
}

int totient (int num)
{
    int ans = num;
    for(int i = 0; i < primes.size () && primes[i] * primes[i] <= num; i++)
    {
        if(num % primes[i] == 0)
        {
            num /= primes[i];
            ans /= primes[i];
            ans *= primes[i]-1;
        }
        while(num % primes[i] == 0)
        {
            num /= primes[i];
        }
    }
    if(num > 1)
    {
        ans /= num;
        ans *= num-1;
    }
    return ans;
}

int main ()
{
    //Continuing on the last problem, find the sum of the first
    //25 composite numbers n where the smallest 111...111
    //divisible by n has a number of 1's which divides n-1
    //For primes, this is given because the totient is p-1

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

    int total = 0;
    int found = 0;
    //Basically just reuse functions from last problem to determine
    //The number of digits in the repunit 11...11
    //and see if that divides n-1
    for(int i = 3; ; i++)
    {
        if(composite[i] && gcd(10,i) == 1)
        {
            int largest = best(totient(9*i), 9*i);
            if((i-1) % largest == 0)
            {
                total += i;
                found++;
                std::cout << i << '\n';
                if(found == 25)
                {
                    std::cout << total << '\n';
                    return 0;
                }
            }
        }
    }
    return 0;
}