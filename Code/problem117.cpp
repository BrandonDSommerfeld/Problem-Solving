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
    //Given a rectangle of size 50, you can place
    //red tiles of size 2, green of size 3, or blue of size 4
    //Colors can be mixed
    //How many ways are there to so?

    math::Unsigned ways[51];
    for(int i = 0; i <= 50; i++)
    {
        ways[i] = 0;
    }
    ways[0] = 1;
    //Simple recurrence relation on whether first tile is
    //Grey square, red, green, or blue
    for(int i = 1; i <= 50; i++)
    {
        ways[i] += ways[i-1];
        if(i >= 2)
        {
            ways[i] += ways[i-2];
        }
        if(i >= 3)
        {
            ways[i] += ways[i-3];
        }
        if(i >= 4)
        {
            ways[i] += ways[i-4];
        }
    }
    std::cout << ways[50] << '\n';
    return 0;
}