#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find the polynomial x^2+ax+b which gives the most number of primes
    //as you plug in 0 1 2 3 ...
    //Bound a with abs below 1000, abs of b equal to or below 1000

    bool composite[1000000];
    for(int i{2}; i <= 1000; i++)
    {
        if(!composite[i])
        {
            for(int j{2}; i*j < 1000000; j++)
            {
                composite[i*j]= true;
            }
        }
    }
    int longest{0};
    int best{0};
    for(int a{-999}; a < 1000; a++)
    {
        for(int b{-1000}; b <= 1000; b++)
        {
            int num{0};
            for(int x{0}; ; x++)
            {
                int val{x*x+a*x+b};
                if(val < 2 || composite[val])
                {
                    break;
                }
                num++;
            }
            if(num > longest)
            {
                longest = num;
                best = a*b;
            }
        }
    }
    std::cout << best << '\n';
    return 0;
}