#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

static std::vector<int> primes;
static bool* composite;

bool permutations(int num1, int num2)
{
    int digitCount1[10];
    int digitCount2[10];
    for(int i{0}; i < 10; i++)
    {
        digitCount1[i] = 0;
        digitCount2[i] = 0;
    }

    //Count up how many times each digit is used
    while(num1 > 0)
    {
        digitCount1[num1%10]++;
        num1/=10;
    }
    while(num2 > 0)
    {
        digitCount2[num2%10]++;
        num2/=10;
    }

    //If they didn't all use the same digit the same number of times
    //They are not permutations of each other
    for(int i{0}; i < 10; i++)
    {
        if(digitCount1[i] != digitCount2[i])
        {
            return false;
        }
    }
    return true;
}

int totient(int num)
{
    if(num == 1) return 1;
    if(!composite[num])
    {
        return num-1;
    }
    
    //This loop could be improved by making it iterative instead
    //of recursive
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
    //Find the number below 10^7 such that its totient is a permutation
    //Of it, and n/totient is maximized

    //Just brute force again

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


    double best = 4;
    int place = 0;
    for(int i = 3; i < limit; i++)
    {
        int t = totient(i);
        if(static_cast<double>(i)/t < best && permutations(i, t))
        {
            best = static_cast<double>(i)/t;
            place = i;
            std::cout << best << '\n';
            std::cout << place << '\n';
        }
    }
    std::cout << best << '\n';
    std::cout << place << '\n';
    return 0;
}