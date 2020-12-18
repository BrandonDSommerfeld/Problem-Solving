#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include "math_unsigned.cpp"

static std::vector<int> primes;
static bool* composite;

int main ()
{
    //Find how many numbers below 50 million can be written
    //as the sum of a prime squared, prime cubed,
    //and prime to the fourth
    //The primes may be the same

    //Brute force all sums
    //with prime sieve from previous problems

    int limit = 10000;
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
    static constexpr int highest = 50000000;

    std::vector<int> squares{};
    for(int i = 0; primes[i]*primes[i] < highest; i++)
    {
        squares.push_back(primes[i]*primes[i]);
    }
    std::vector<int> cubes{};
    for(int i = 0; primes[i]*primes[i]*primes[i] < highest; i++)
    {
        cubes.push_back(primes[i]*primes[i]*primes[i]);
    }
    std::vector<int> tetras{};
    for(int i = 0; primes[i]*primes[i]*primes[i]*primes[i] < highest; i++)
    {
        tetras.push_back(primes[i]*primes[i]*primes[i]*primes[i]);
    }
    bool *possible = new bool[highest];
    for(int i = 0; i < highest; i++)
    {
        possible[i] = false;
    }

    for(int i = 0; i < squares.size(); i++)
    {
        for(int j = 0; j < cubes.size(); j++)
        {
            if(squares[i] + cubes[j] < highest)
            {
                for(int k = 0; k < tetras.size(); k++)
                {
                    if(squares[i] + cubes[j] + tetras[k] < highest)
                    {
                        possible[squares[i] + cubes[j] + tetras[k]] = true;
                    }
                }
            }
        }
    }
    int total = 0;
    for(int i = 0; i < highest; i++)
    {
        if(possible[i])
        {
            total++;
        }
    }
    std::cout << total << '\n';

    return 0;
}