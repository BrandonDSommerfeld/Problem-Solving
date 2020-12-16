#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
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

math::Unsigned root (int num)
{
    math::Unsigned result = 0;
    math::Unsigned goal = num;
    for(int i = 0; i < 100; i++)
    {
        //Repeatedly increase digit until it is too big,
        //Then go for the next digit
        while(result*result < goal)
        {
            result++;
        }
        result--;

        result *= 10;
        goal *= 100;
    }
    return result;
}

int digitSum(int num)
{
    int result = 0;
    math::Unsigned r = root(num);
    while(r > 0)
    {
        result += (r%10).to_uint();
        r /= 10;
    }
    return result;
}

int main ()
{
    //For all numbers <= 100, if its square root is irrational,
    //Find the sum of the first 100 digits including pre-decimal
    //For all of them, and sum that
    int total = 0;
    std::cout << digitSum(2) << '\n';
    for(int i = 1; i <= 100; i++)
    {
        if(!square(i))
        {
            total += digitSum(i);
        }
    }
    std::cout << total << '\n';
    return 0;
}