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

bool palindrome (std::string num)
{
    int len = num.length();
    for(int i = 0; i < len/2; i++)
    {
        if(num[i] != num[len-1-i])
        {
            return false;
        }
    }
    return true;
}

inline long long sumSquares(long long n)
{
    return n*(n+1)*(2*n+1)/6;
}

int main ()
{
    //Find the sum of all numbers below 10^8
    //Which are palindromic and also can be expressed
    //as the sum of consecutive squares

    //It turns out to be faster to generate all possible sums
    //and check if palindrome, rather than generate palindromes
    //and see if they can be made from a sum
    //j < i-1 because it must be a sum of squares, so at least 2 terms
    
    static constexpr long long limit = 100000000;
    math::Unsigned total = 0;
    std::set<long long> seen{};
    for(int i = 0; i*i < limit; i++)
    {
        for(int j = 0; j < i-1; j++)
        {
            long long guess = sumSquares(i) - sumSquares(j);
            if(guess < limit && seen.find(guess) == seen.end() &&
                palindrome(std::to_string(guess)))
            {
                seen.insert(guess);
                total += guess;
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}