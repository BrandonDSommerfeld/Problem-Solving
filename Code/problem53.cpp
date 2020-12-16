#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

math::Unsigned combos (int n, int r)
{
    //Factorial defintion of combinations
    math::Unsigned answer{1};
    for(int i{2}; i <= n; i++)
    {
        answer *= i;
    }
    for(int i{2}; i <= r; i++)
    {
        answer /= i;
    }
    for(int i{2}; i <= n-r; i++)
    {
        answer /= i;
    }
    return answer;
}

int main ()
{
    //For how many values of of n and r with 1 <= n <= 100
    //Is n C r > 1000000

    //Just brute force with big integers
    int ways{0};
    for(int n{1}; n <= 100; n++)
    {
        for(int r{0}; r <= n; r++)
        {
            if(combos(n,r) > 1000000)
            {
                ways++;
            }
        }
    }
    std::cout << ways << '\n';

    return 0;
}