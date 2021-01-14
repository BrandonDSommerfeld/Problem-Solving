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
static constexpr int limit = 1000000;

bool isPrime(long long num)
{
    if(num < limit)
    {
        return !composite[num];
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

int main ()
{
    //Consider hexagons labeled with numbers
    //You start with just 1, then place 2 ... 
    //counterclockwise around it, starting from the top
    //Continue to add layers forever

    //Define a function PD for prime differences, which for a given
    //Tile is the number of neighbors where their difference is prime
    //Find the 2000th number which has PD(n) = 3

    //Side length grows in the sequence 1, 2, 3, 4, ...

    //Difference between top number goes 1, 6, 12, 18, 24, ...

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
    composite[0] = true;
    composite[1] = true;

    int loc = 2;
    long long val = 8;
    int goal = 2000;

    //You only actually have to check corners and the last
    //tile in a layer
    //All others are adjacent to 2, which gives 1,
    //And then are adjacent to a pair, and at least one
    //Of each of those pairs is even.
    //Thus, this code just goes around the layers and only
    //Checks those values
    for(long long layer = 1; ; layer++)
    {
        for(int side = 0; side < 6; side++)
        {
            if(side == 0)
            {
                int num = 0;
                if(isPrime(6*layer+5))
                {
                     num++;
                }
                if(isPrime(6*layer+7))
                {
                    num++;
                }
                if(isPrime(12*layer+17))
                {
                    num++;
                }
                if(num == 3)
                {
                    loc++;
                    if(loc == goal)
                    {
                        std::cout << val << '\n';
                        return 0;
                    }
                }
            }
            else
            { 
                int num = 0;
                if(isPrime(layer*6+side))
                {
                    num++;
                }
                if(isPrime((layer+1)*6+side))
                {
                    num++;
                }
                if(isPrime((layer+1)*6+side-1))
                {
                    num++;
                }
                if(isPrime((layer+1)*6+side+1))
                {
                    num++;
                }
                if(num == 3)
                {
                    loc++;
                    if(loc == goal)
                    {
                        std::cout << val << '\n';
                        return 0;
                    }
                }
            }
            if(side == 5)
            {
                int num = 0;
                if(isPrime(6*(layer+1)-1))
                {
                    num++;
                }
                if(isPrime(6*(2*layer+1)-1))
                {
                    num++;
                }
                if(isPrime(6*(layer+2)-1))
                {
                    num++;
                }
                if(num == 3)
                {
                    loc++;
                    if(loc == goal)
                    {
                        std::cout << (val+layer) << '\n';
                        return 0;
                    }
                }
            }
            val += (layer + 1);
        }
    }
    return 0;
}