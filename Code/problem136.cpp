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
    //How many values of n below 50 million
    //have exactly 1 possible sequences?

    //Exact same code as last problem, except larger limit and 
    //look for 1

    static constexpr int limit = 50000000;
    int *ways = new int[limit];
    for(int i = 0; i < limit; i++)
    {
        ways[i] = 0;
    }

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
        if(ways[i] == 1)
        {
            total++;
        }
    }
    std::cout << total << '\n';
    return 0;
}