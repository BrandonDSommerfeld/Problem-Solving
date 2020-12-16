#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Compute the index of the first fibbonacci number with 1000 digits
    math::Unsigned num1{1};
    math::Unsigned num2{1};
    math::Unsigned digits1000{1};
    //Smallest 1000 digit number has 999 0's
    for(int i{0}; i < 999; i++)
    {
        digits1000 *= 10;
    }
    int index{3};
    while((num1+num2) / digits1000 < 1)
    {
        num2 = num2+num1;
        num1 = num2-num1;
        index++;
    }
    std::cout << index << '\n';
    return 0;
}