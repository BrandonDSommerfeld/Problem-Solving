#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

static std::vector<int> primes;
static bool* composite;

int main ()
{
    //Find the first number which can be written as the
    //Sum of primes in more than 5000 ways

    //Very similar to last problem, except now the coins are primes
    int limit = 100000;
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

    auto ways = new int[1000][1000];
    for(int i = 0; i < 1000; i++)
    {
        for(int j = 0; j < 1000; j++)
        {
            ways[i][j] = 0;
        }
    }
    ways[0][0] = 1;

    //I need to go all the way down and use all primes, 
    //so iterate on j first, still gets same effect though
    for(int j = 0; j < 1000; j++)
    {
        for(int i = 0; i < 100; i++)
        {
            if(i != 0)
            {
                ways[i][j] += ways[i-1][j];
            }
            if(j >= primes[i])
            {
                ways[i][j] += ways[i][j-primes[i]];
            }
            else
            {
                if(ways[i][j] > 5000)
                {
                    std::cout << j << '\n';
                    return 1;
                }
            }
            
        }
    }
    return 0;
}