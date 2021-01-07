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
    //Colors cannot be mixed, but unlike in the previous problems
    //They can be next to each other
    //How many ways are there to so?

    math::Unsigned red[51];
    math::Unsigned green[51];
    math::Unsigned blue[51];
    for(int i = 0; i <= 50; i++)
    {
        red[i] = 0;
        green[i] = 0;
        blue[i] = 0;
    }
    red[0] = 1;
    green[0] = 1;
    blue[0] = 1;
    //Simple recurrence relation on whether the tiling starts with
    //a grey square or the colored tile
    for(int i = 1; i <= 50; i++)
    {
        red[i] += red[i-1];
        green[i] += green[i-1];
        blue[i] += blue[i-1];
        if(i >= 2)
        {
            red[i] += red[i-2];
        }
        if(i >= 3)
        {
            green[i] += green[i-3];
        }
        if(i >= 4)
        {
            blue[i] += blue[i-4];
        }
    }
    //Remove the all grey tiles from each one
    std::cout << red[50] + green[50] + blue[50] - 3 << '\n';
    return 0;
}