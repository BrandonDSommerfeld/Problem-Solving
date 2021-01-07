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
    //Consider a rectangle with 50 square tiles
    //You can cover it with red tiles which are at least 
    //3 long with no limits, but red tiles must be at least
    //1 apart
    //How many ways are there to place red tiles, including none at all?

    //Differentiate ways which start with a grey vs those with either
    math::Unsigned grey[51];
    math::Unsigned either[51];
    for(int i = 0; i <= 50; i++)
    {
        grey[i] = 0;
        either[i] = 0;
    }

    grey[0] = 1;
    either[0] = 1;
    //Simple recurrence relation
    //Based on either placing a grey block in front
    //Or different sizes of red blocks
    for(int i = 1; i <= 50; i++)
    {
        grey[i] = either[i-1];
        for(int j = 3; j <= i; j++)
        {
            either[i] += grey[i-j];
        }
        either[i] += grey[i];
    }
    std::cout << either[50] << '\n';
    return 0;
}