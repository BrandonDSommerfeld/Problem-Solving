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

bool decreasing(int num)
{
    int prev = -1;
    while(num > 0)
    {
        if(prev == -1 || prev <= num % 10)
        {
            prev = num % 10;
            num /= 10;
        }
        else
        {
            return false;
        }
    }
    return true;
}
bool increasing(int num)
{
    int prev = -1;
    while(num > 0)
    {
        if(prev == -1 || prev >= num % 10)
        {
            prev = num % 10;
            num /= 10;
        }
        else
        {
            return false;
        }
    }
    return true;
}

int main ()
{
    //If a number does not have increasing digits, or decreasing
    //digits, with equality allowed,
    //then it is called bouncy
    //as you get larger, most numbers are bouncy
    //Find n such that exactly 99% of numbers below or equal are bouncy
    //Pretty simple brute force
    int bouncy = 0;
    for(int i = 1; ; i++)
    {
        if(!increasing(i) && !decreasing(i))
        {
            bouncy++;
        }
        if(bouncy * 100 == i * 99)
        {
            std::cout << i << '\n';
            break;
        }
    }
    return 0;
}