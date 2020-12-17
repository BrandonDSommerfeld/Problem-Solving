#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include "math_unsigned.cpp"

long long choose2(int n)
{
    return n*(n-1)/2;
}

int main ()
{
    //Find the rectangle which contains the closest to 2000000
    //Sub rectangles, including itself

    //From each side, you pick the 2 sides, so a 
    //x by y rectangle has
    //xC2 * yC2 subrectangles, just find this close to 2000000

    static constexpr int limit = 2500;
    long long ways[limit];
    for(int i = 0; i < limit; i++)
    {
        ways[i] = choose2(i);
    }

    long long closest = 100000;
    int loc1 = 0;
    int loc2 = 0;
    for(int i = 1; i < limit-1; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            if(std::abs(ways[i+1]*ways[j+1]-2000000L) < closest)
            {
                closest = std::abs(ways[i+1]*ways[j+1]-2000000);
                loc1 = i;
                loc2 = j;
            }
        }
    }
    std::cout << loc1 << ' ' << loc2 << ' ' << loc1*loc2 << '\n';
    return 0;
}