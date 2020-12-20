#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include "math_unsigned.cpp"

int maximum(int a, int b, int c, int d)
{
    return 0;
}

int main ()
{
    //Find the set of 4 distinct 1 digit numbers
    //Such that with parantheses, *, /, +, and - you can create
    //all numbers from 1 to n, with n as large as possible
    //Note: Not allowed to concatenate into 12 or something

    //Iterate over all sets
    int highest = 0;
    int place = 0;
    for(int a = 0; a < 10; a++)
    {
        for(int b = a+1; b < 10; b++)
        {
            for(int c = b+1; c < 10; c++)
            {
                for(int d = c+1; d < 10; d++)
                {
                    int best = maximum(a,b,c,d);
                    if(best > highest)
                    {
                        highest = best;
                        place = 1000*a+100*b+10*c+d;
                    }
                }
            }
        }
    }
    std::cout << highest << '\n';
    std::cout << place << '\n';
    return 0;
}