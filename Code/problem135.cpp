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
#include "algorithms.cpp"

int main ()
{
    //Consider positive integers x,y,z such that
    // x^2-y^2-z^2 = n
    // and x,y,z form an arithmetic progression
    //How many values of n below 1 million
    //have exactly 10 possible sequences?

    //Write x=a+2d, y=a+d, z=a
    //Then (3d-a)(d+a) = n
    //Thus, just iterate over values of d and a

    static constexpr int limit = 1000000;
    int *ways = new int[limit];
    for(int i = 0; i < limit; i++)
    {
        ways[i] = 0;
    }

    //If d is considered fixed, then the above factorization is 
    //an upside down parabola, so once a value that is too large
    //is found, we stop and then go from the other side
    for(long long d = 1; d < limit; d++)
    {
        bool stopped = false;
        for(long long a = 1; a < 3*d && a+d < limit; a++)
        {
            if((3*d-a)*(d+a) < limit)
            {
                ways[(3*d-a)*(d+a)]++;
            }
            else
            {
                stopped = true;
                break;
            }
        }
        if(stopped)
        {
            for(long long a = 3*d-1; a > 0 && a+d < limit; a--)
            {
                if((3*d-a)*(d+a) < limit)
                {
                    ways[(3*d-a)*(d+a)]++;
                }
                else
                {
                    break;
                }
            }
        }
    }

    int total = 0;
    for(int i = 1; i < limit; i++)
    {
        if(ways[i] == 10)
        {
            total++;
        }
    }
    std::cout << total << '\n';
    return 0;
}