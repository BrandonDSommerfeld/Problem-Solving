#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int digits(math::Unsigned num)
{
    int digits{0};
    while(num > 0)
    {
        digits++;
        num /= 10;
    }
    return digits;
}

int main ()
{
    //The infinite fraction 1+1/(2+1/(2+1/...))
    //Is the square root of 2
    //If we cut off the pluses, we get
    //1, 1+1/2, 1+1/(2+1/2)
    //Of the first 1,000
    //How many numerators have more digits than denominator

    //Just use the repeating part of the fraction, easy to calculate
    math::Unsigned numerator{1};
    math::Unsigned denominator{2};
    int num{0};
    for (int i{0}; i < 1000; i++)
    {
        if(digits(numerator+denominator) > digits(denominator))
        {
            num++;
        }
        //Add 2 to value, and take reciprocal
        denominator = 2*denominator + numerator;
        numerator = (denominator-numerator)/2;
    }
    std::cout << num << '\n';

    return 0;
}