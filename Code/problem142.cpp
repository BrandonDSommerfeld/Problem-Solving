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
    //Find the numbers x,y,z with x > y > z > 0 such that
    //each pairwise sum and difference is a perfect square
    //Find the triplet with minimum sum

    unsigned long long best = 1000000;
    for(unsigned long long x = 3; x < best; x++)
    {
        for(unsigned long long y = 2; y < x; y++)
        {
            for(unsigned long long z = 1; z < y; z++)
            {
                if(algorithms::isSquare(x+y) && 
                algorithms::isSquare(x-y) && 
                algorithms::isSquare(x+z) && 
                algorithms::isSquare(x-z) && 
                algorithms::isSquare(y+z) && 
                algorithms::isSquare(y-z))
                {
                    std::cout << x << ' ' << y << ' ' << z << '\n';
                    best = x+y+z;
                }
            }
        }
    }
    std::cout << best << '\n';
    return 0;
}