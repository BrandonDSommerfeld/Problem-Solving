#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Calculates the sum of the digits of 2^1000
    math::Unsigned num{1};
    for(int i{0}; i < 1000; i++)
    {
        num *= 2;
    }
    int sum{0};
    //Repeatedly pop off last digit and add it
    while(num > 0)
    {
        sum += static_cast<int>((num % 10).to_uint());
        num /= 10;
    }
    std::cout << sum << '\n';
    return 0;
}

