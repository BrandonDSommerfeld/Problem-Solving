#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Abundant numbers are numbers where the sum of their proper divisors
    //is greater than the number itself
    //This program finds all numbers which cannot be written as
    //the sum of 2 abundant numbers. Proven upper bound around 20000

    bool abundant[30000];
    int sum{0};
    for(int i{1}; i < 28214; i++)
    {
        int smallSum{0};
        for(int j{1}; j <= std::round(std::sqrt(i)); j++)
        {
            if(i % j == 0)
            {
                smallSum += j;
                //Don't double count squares, or i itself
                if(i/j != j && j != 1)
                {
                    smallSum += i/j;
                }
            }
        }
        if (smallSum > i)
        {
            abundant[i] = true;
        }
        else
        {
            abundant[i] = false;
        }
        
        bool works{false};
        //See if it can be expressed as the sum of 2 abundant
        for(int j = 12; j < i; j++)
        {
            if(abundant[j] && abundant[i-j])
            {
                works = true;
            }
        }
        if(!works)
        {
            sum += i;
        }
    }
    std::cout << sum << '\n';
    return 0;
}