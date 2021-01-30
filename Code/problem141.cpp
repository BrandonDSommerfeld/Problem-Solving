#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "algorithms.cpp"

int main ()
{
    //For a number n, perform division by d to write
    //n = q*d + r
    //We want d, q, r to be a geometric sequence, any order allowed
    //Find the sum of all square n below 10^12 for which this occurs

    


    unsigned long long limit = 1;
    for(int i = 0; i < 12; i++)
    {
        limit *= 10;
    }
    //My god, I had the answer for the longest time, but I thought
    //I was wrong because using math::Unsigned was making it way too slow
    //Note that if the ratio is n/d, then the remainder must be 
    //Divisible by d^2, so write r = kd^2
    //Thus, we are looking for a^2 = k^2 d n^3 + kd^2
    //Just iterate over k, d, and n, and it works out
    unsigned long long total = 0;
    for(unsigned long long d = 1; d < 1000; d++)
    {
        for(unsigned long long k = 1; k*d*d < 1000000; k++)
        {
            int current = k*d*d;
            unsigned long long guess = 2;
            for(unsigned long long n = d+1; guess < limit; n++)
            {
                if(algorithms::gcd(n-1,d) == 1 &&
                algorithms::isSquare(guess))
                {
                    total += guess;
                    std::cout << current << ' ' << (n-1) << '/' << d << ' ' <<
                    guess << ' ' << total << '\n';
                }
                guess = n*k*k*d*n*n + current;                   
            }
        }
    }
    

    std::cout << total << '\n';
    return 0;
}