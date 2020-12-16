#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

static std::vector<int> primes;
static bool* composite;

int totient(int num)
{
    if(num == 1) return 1;
    if(!composite[num])
    {
        return num-1;
    }
    
    int result = 1;
    for(int i = 0; num > 1 && primes[i] <= num/2; i++)
    {
        if(!composite[num])
        {
            result *= num-1;
            return result;
        }
        if(num % primes[i] == 0)
        {
            int power = 0;
            while(num % primes[i] == 0)
            {
                num /= primes[i];
                power++;
            }
            for(int j = 0; j < power-1; j++)
            {
                result *= primes[i];
            }
            result *= primes[i]-1;
        }
    }
    if(num != 1 && !composite[num])
    {
        result *= num-1;
    }
    return result;
}

int main ()
{
    //If you list all fractions strictly between 0 and 1
    //With denominators d<=1000000
    //How many are there

    int limit = 1000001;
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

    //Iterate over the denominators: 
    //At each step, there are totient(d) new fractions
    //Because they are unreduced, the rest have a common
    //Factor and thus reduce to a previous fraction

    math::Unsigned total = 0;

    for(int i = 2; i <= 1000000; i++)
    {
        total += totient(i);
    }
    std::cout << total << '\n';
    return 0;
}