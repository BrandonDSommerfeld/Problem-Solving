#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int gcd(int num1, int num2)
{
    if(num1 > num2)
    {
        if(num1 % num2 == 0)
        {
            return num2;
        }
        return gcd(num1-num2*(num1/num2), num2);
    }
    if(num2 % num1 == 0)
    {
        return num1;
    }
    return gcd(num2-num1*(num2/num1), num1);
}

int main ()
{
    //Find how many unique fractions are between 1/3 and 1/2 with
    //Denominator d <= 12000

    //Brute force all denominators, and check which values
    //are relatively prime in the range
    math::Unsigned total = 0;
    for(int i = 4; i <= 12000; i++)
    {
        int lower = i/3 + 1;
        int upper = i/2;

        for(int j = lower; j <= upper; j++)
        {
            if(gcd(j, i) == 1)
            {
                total++;
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}