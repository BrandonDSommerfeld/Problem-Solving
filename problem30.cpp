#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find sum of all numbers which can be written as the 
    //sum of the 5th power of their digits
    //Just brute force numbers
    int sum{0};
    for(int i{2}; i < 1000000; i++)
    {
        int digitSum{0};
        int copy{i};
        while(copy > 0)
        {
            int digit{copy % 10};
            digit = digit*digit*digit*digit*digit;
            digitSum += digit;
            copy /= 10;
        }
        if(digitSum == i)
        {
            sum += i;
        }
    }
    std::cout << sum << '\n';
    return 0;
}