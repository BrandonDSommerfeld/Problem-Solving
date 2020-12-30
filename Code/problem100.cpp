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

bool recursive_square(math::Unsigned num, math::Unsigned low, 
math::Unsigned high)
{
    if(low == high)
    {
        return low*low == num;
    }
    math::Unsigned mid = (low+high)/2;
    if(mid*mid < num)
    {
        return recursive_square(num, mid+1, high);
    }
    if(mid*mid > num)
    {
        return recursive_square(num, low, mid);
    }
    return true;
}

bool square (math::Unsigned num)
{
    math::Unsigned guess = 1;
    while(guess*guess <= num)
    {
        guess *= 2;
    }
    return recursive_square(num, guess/2, guess);
}

int main ()
{
    //Find 2 numbers n and k, such that n > 10^12
    //And when you pick 2 numbers, there is exactly a 1/2 chance
    //of getting 2 numbers from the k

    //Find n and k such that n C 2 = 2* k C 2
    

    math::Unsigned num = 1;
    for(int i = 0; i < 12; i++)
    {
        num *= 10;
    }
    
    //So I used an online calculator to get this recurrence formula,
    //But you can complete the square on both sides
    //To create a Pell equation, which has known solutions
    //from the continued fraction
    math::Unsigned numerator = 0;
    math::Unsigned denominator = 1;
    while(numerator < num)
    {
        math::Unsigned temp1 = numerator;
        math::Unsigned temp2 = denominator;

        numerator = 3*temp1 + 4*temp2 - 3;
        denominator = 2*temp1+3*temp2 - 2;
        std::cout << numerator << ' ' << denominator << '\n';
    }
    
    return 0;
}