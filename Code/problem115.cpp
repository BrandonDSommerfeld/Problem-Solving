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
    //Similar to previous problem, find the shortest rectangle
    //such that there are more than 1 million ways to cover it
    //with blocks of size at least 50
    math::Unsigned grey[1000];
    math::Unsigned either[1000];
    for(int i = 0; i < 1000; i++)
    {
        grey[i] = 0;
        either[i] = 0;
    }

    grey[0] = 1;
    either[0] = 1;
    //Simple recurrence relation
    //Based on either placing a grey block in front
    //Or different sizes of red blocks
    for(int i = 1; i < 1000; i++)
    {
        grey[i] = either[i-1];
        for(int j = 50; j <= i; j++)
        {
            either[i] += grey[i-j];
        }
        either[i] += grey[i];
        if(either[i] > 1000000)
        {
            std::cout << i << '\n';
            break;
        }
    }
    return 0;
}