#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find the fraction with denominator below 1000000 which is closest
    //To 3/7 without being it.

    //Brute force each denominator

    double best = 1;
    int place = 0;

    for(int i = 8; i <= 1000000; i++)
    {
        int guess = std::floor((3.0/7)*i);

        if(guess*7 != 3*i)
        {
            if(std::abs(static_cast<double>(guess)/i - 3.0/7.0) < best)
            {
                best = std::abs(static_cast<double>(guess)/i - 3.0/7.0);
                place = guess;
            }
            if(std::abs(static_cast<double>(guess+1)/i - 3.0/7.0) < best)
            {
                best = std::abs(static_cast<double>(guess+1)/i - 3.0/7.0);
                place = guess+1;
            }
        }
    }
    std::cout << best << '\n';
    std::cout << place << '\n';
    return 0;
}