#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //There are 4 fractions with 2 digit numerators and denominators
    //Such as 49/98, where cancelling the 9's gives correct answer
    //Find denominator of the product of these 4 fractions
    //Which can be simplified the wrong way. Cancelling 0's excluded
    //Fractions below 1 only
    for(int i{1}; i < 100; i++)
    {
        for(int j{1}; j < 100; j++)
        {
            if(std::abs(static_cast<double>(i) / j - 
            static_cast<double>(i/10) / (j%10)) < 0.001)
            {
                //Ensure we actually do wrong cancelling and not equal
                if(i % 10 == j / 10 && i != j)
                {
                    std::cout << i << ' ' << j << '\n';
                }
            }
        }
    }

    return 0;
}