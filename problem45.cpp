#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find the second number which is triangular, pentagonal, and 
    //hexagonal. First is 40755
    //Triangular: n(n+1)/2
    //Pentagonal: n(3n-1)/2
    //Hexagonal n(2n-1)

    //Just brute force hexagonal numbers, since they
    //are the furthest apart
    for(long long i{144}; i < 100000; i++)
    {
        long long num{i*(2*i-1)};
        bool works{true};
        long long guess = static_cast<long long>(std::round(std::sqrt(2*num/3)));
        if(guess*(3*guess-1)/2 != num)
        {
            works = false;
        }
        long long guess2 = static_cast<long long>(std::round(std::sqrt(2*num)));
        if(guess2*(guess2+1)/2 != num)
        {
            works = false;
        }
        if(works)
        {
            std::cout << num << '\n';
            return 0;
        }
    }
    return 0;
}