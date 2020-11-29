#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int digits (math::Unsigned num)
{
    int digit{0};
    while(num > 0)
    {
        digit++;
        num /= 10;
    }
    return digit;
}

int main ()
{
    //Compute how many numbers have n digits and are nth powers
    
    //Start at 1 to account for 1
    int num{1};
    //Just brute force over a bunch of numbers
    //Don't need to check 10 or above, because they always have
    //More digits than power
    for(int i{2}; i < 10; i++)
    {
        for(int e{1}; e < 100; e++)
        {
            math::Unsigned curr{1};
            for(int j{0}; j < e; j++)
            {
                curr *= i;
            }
            if(digits(curr) == e)
            {
                num++;
            }
        }
    }
    std::cout << num << '\n';
}