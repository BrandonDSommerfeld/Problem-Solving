#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int digitSum(math::Unsigned num)
{
    int sum{0};
    while(num > 0)
    {
        sum += (num % 10).to_uint();
        num /= 10;
    }
    return sum;
}

int main ()
{
    //Find the number a^b with a, b < 100
    //Such that the sum of the digits is maximized.

    //Just brute force with big integers
    int max{0};
    for(int a{1}; a < 100; a++)
    {
        for(int b{1}; b < 100; b++)
        {
            math::Unsigned num{1};
            for(int e{0}; e < b; e++)
            {
                num *= a;
            }
            int sum = digitSum(num);
            if(sum > max)
            {
                max = sum;
            }
        }
    }
    std::cout << max << '\n';
    return 0;
}