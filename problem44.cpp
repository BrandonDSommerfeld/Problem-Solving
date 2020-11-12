#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Pentagonal numbers are n(3n-1)/2
    //Find the pair of pentagonal numbers whose sum and difference is
    //pentagonal, and their difference is minimal

    //Start with i as the difference number, and add a pentagonal
    //To get original second, then add again for sum
    for(long long i{1}; i < 10000; i++)
    {
        long long num1{i*(3*i-1)/2};
        for(long long j{1}; j < 10000; j++)
        {
            long long num2{j*(3*j-1)/2};

            bool works{true};
            long long original{num1+num2};
            long long guess= static_cast<long long>(std::round(std::sqrt(2*original/3)));
            if(guess*(3*guess-1)/2 != original)
            {
                works = false;
            }

            long long sum{num1+2*num2};
            long long guess2=static_cast<long long>(std::round(std::sqrt(2*sum/3)));
            if(guess2*(3*guess2-1)/2 != sum)
            {
                works = false;
            }
            if(works)
            {
                std::cout << num1 << '\n';
                return 0;
            }
        }
    }
    return 0;
}