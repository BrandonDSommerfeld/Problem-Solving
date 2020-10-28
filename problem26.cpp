#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find the integer below 1000 with the greatest number of 
    //repeating digits in 1/d
    int best{0};
    int highest{0};
    for(int i{3}; i < 1000; i++)
    {
        //Find smallest number 999..999
        //Divisible by d, because this number will be repeated
        //To get repeating 0.999999....
        math::Unsigned num{1};
        for(int j{1}; j <= i; j++)
        {
            num *= 10;
            if((num-1) % i == 0)
            {
                if(j > highest)
                {
                    highest = j;
                    best = i;
                }
                break;
            }
        }
    }
    std::cout << best << '\n';
    return 0;
}