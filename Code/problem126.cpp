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

int main ()
{
    //Consider a rectangular prism which is A x B x C
    //Covering all faces of this prism takes 2AB+2AC+2BC
    //cubes. Then, consider how many cubes are needed to cover
    //this already covered shape, and so on

    //Note, this is per layer, not total cubes
    //Find the first n such that there are 1000 starting prisms
    //which have n cubes on a layer

    //There are 2 sources for the increase in cubes per layer
    //First, on each edge, there is a staircase
    //which grows by 1 layer, which is the sidelength long,
    //which is the 4(a+b+c) for each edge
    //Then, at the 8 corners there is a half-cube thing
    //which grows as a triangular number, which is the count

    static constexpr int limit = 100000;
    int *ways = new int[limit];
    for(int i = 0; i < limit; i++)
    {
        ways[i] = 0;
    }
    int max = 5000;
    for(int a = 1; a <= max; a++)
    {
        for(int b = a; b <= max; b++)
        {
            if(2*(a*b+a+b) < limit)
            {
                for(int c = b; c <= max; c++)
                {
                    int cubes = 2*(a*b+a*c+b*c);
                    int count = 0;
                    while(cubes < limit)
                    {
                        ways[cubes]++;
                        cubes += 4*(a+b+c);
                        cubes += 8*count;
                        count++;
                    }
                }
            }
        }
    }
    for(int i = 0; i < limit; i++)
    {
        if(ways[i] == 1000)
        {
            std::cout << i << '\n';
            break;
        }
    }
    return 0;
}