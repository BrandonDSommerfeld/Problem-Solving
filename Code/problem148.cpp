#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include <list>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "algorithms.cpp"


int main ()
{
    //Find the number of entries which are not divisible by 7 in the first 
    //1 billion rows of Pascal's triangle

    //For a given n, need to choose k to remove all factors of 7 when we do 
    //n! / k! (n-k)!
    // n (n-1) (n-2) .. (n-k+1) / k (k-1) (k-2) (k-3) ... 2 * 1
    //Can't have more powers of 7 in the upper part

    unsigned long long limit = 1000000000;
    unsigned long long total = 0;
    unsigned long long multiplier = 1;
    unsigned long long multiplier2 = 1;
    unsigned long long base = 1;


    //For a number n, n choose k has all factors of 
    //7 removed if k and n-k add together base 7 without overflow, 
    //because otherwise there is an extra factor of 7 from the higher 
    //power which is not accounted for

    //Then for each n, figure out how many ways we can distribute 
    //the digit between the 2 numbers, which is where the digit+1
    //comes from. However, this only does 1 n at a time, so 
    //I simplify iterating a digit from 0 to 6 as just multiplying 
    //the 0 by 28, and the same for other digits
    //With this, I just need to look at the base 7 representation of 
    //the limiting value, and do digit*digit+1/2 to sum over all numbers 
    //smaller than the limit too
    while(base <= limit)
    {
        base *= 7;
        multiplier2 *= 28;
    }
    base /= 7;
    multiplier2 /= 28;
    while(base > 0)
    {
        unsigned long long digit = limit / base;

        total += multiplier*multiplier2*digit*(digit+1)/2;
        multiplier *= digit+1;
        limit -= base * digit;
        base /= 7;
        multiplier2 /= 28;
    }

    std::cout << total << '\n';
    return 0;
}