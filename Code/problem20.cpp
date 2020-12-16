#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Compute the sum of the digits of 100!
    //Getting arbitrary sized integers was the hardest part
    math::Unsigned num{1};
    for(int i{2}; i < 101; i++)
    {
        num *= i;
    }
    int sum{0};
    while(num > 0)
    {
        sum += (num % 10).to_uint();
        num /= 10;
    }
    std::cout << sum << '\n';
    return 0;
}