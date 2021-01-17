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

bool works(std::vector<int> list)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i] != 2 && list[i] != 5)
        {
            return false;
        }
    }
    return true;
}

int main ()
{
    //Consider the number 111...111 with 10^n 1's
    //For some primes p, these numbers are never divisible
    //by p, regardless of the value of n
    //Find the sum of all such primes which are below 100000

    static constexpr int limit = 100000;
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

    math::Unsigned total{};
    for(int i = 0; i < primes.size(); i++)
    {
        int digits = best(totient(9*primes[i]), 9*primes[i]);
        std::vector<int> *fac = factors(digits);
        if(!works(*fac))
        {
            total += primes[i];
        }
    }
    std::cout << total << '\n';
    return 0;
}