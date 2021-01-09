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

inline int sumSquares(int n)
{
    return n*(n+1)*(2*n+1)/6;
}

int main ()
{
    //Find the sum of all numbers below 10^8
    //Which are palindromic and also can be expressed
    //as the sum of consecutive squares

    //Probably use the sum of squares formula

    static constexpr int limit = 100000000;
    long long total = 0;
    for(int i = 0; i*i < limit; i++)
    {
        for(int j = 0; j < i; j++)
        {
            int guess = sumSquares(i) - sumSquares(j);
            if(palindrome(std::to_string(guess)))
            {
                total += guess;
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}