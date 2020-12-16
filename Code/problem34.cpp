#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find the sum of all numbers which are equal to
    //The sum of the factorial of their digits, 1 and 2 excluded
    int sum{0};
    int factorial[10];
    factorial[0] = 1;
    for(int i{1}; i < 10; i++)
    {
        factorial[i] = factorial[i-1] * i;
    }
    for(int i{3}; i < 1000000; i++)
    {
        int digitSum{0};
        int copy{i};
        while(copy > 0)
        {
            digitSum += factorial[copy % 10];
            copy /= 10;
        }
        if(i == digitSum)
        {
            sum += i;
        }
    }
    std::cout << sum << '\n';
    return 0;
}