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

bool isPrime(int num)
{
    if(num == 1)
    {
        return false;
    }
    for(int i = 0; primes[i]*primes[i] <= num; i++)
    {
        if(num % primes[i] == 0)
        {
            return false;
        }
    }
    return true;
}

int evaluate(std::string permutation, int smallest)
{
    if(permutation.length() == 0)
    {
        return 1;
    }
    int ans = 0;
    for(int len = 1; len <= permutation.length(); len++)
    {
        int guess = std::stoi(permutation.substr(0, len));
        if(guess > smallest && isPrime(guess))
        {
            ans += evaluate(permutation.substr(len), guess);
        }
    }
    return ans;
}

int recursive (std::string num)
{
    if(num.length() == 9)
    {
        return evaluate(num, 0);
    }
    int ans = 0;
    for(int d = 1; d < 10; d++)
    {
        if(num.find(d+48) == -1)
        {
            std::string copy{num};
            copy += d+48;
            ans += recursive(copy);
        }
    }
    return ans;
}

int main ()
{
    //Consider a set of numbers where every digit is used once
    // {2, 5, 47, 89, 631}
    //is one, and in particular all elements are prime
    //How many such sets use all digits are are all prime?

    //Consider all permutations, then for each permutation
    //Consider inserting various cutoff points
    //Also, enforce that the set must be in increasing
    //order to ensure it is only counted once
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

    std::cout << recursive("") << '\n';
    return 0;
}