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

bool pandigital(math::Unsigned num)
{
    int occurrences[10];
    for(int i = 0; i < 10; i++)
    {
        occurrences[i] = 0;
    }
    while(num > 0)
    {
        occurrences[(num%10).to_uint()]++;
        num /= 10;
    }
    for(int i = 1; i < 10; i++)
    {
        if(occurrences[i] != 1)
        {
            return false;
        }
    }
    return true;
}

math::Unsigned first9Digits(math::Unsigned num)
{
    while (num > 1000000000)
    {
        num /= 10;
    }
    return num;
}

int main ()
{
    //Find the first fibonacci number whose last 9 digits are 1-9
    //And the first 9 digits are as well, in some order

    //Answer ends up being like 300000, so you can only keep
    //track of the first digits and last digits to be fast
    //Keep the top 20 front digits in case of addition 
    //carryover affecting the sum
    math::Unsigned ten20 = 1;
    for(int i = 0; i < 20; i++)
    {
        ten20 *= 10;
    }
    math::Unsigned firstFront = 0;
    math::Unsigned secondFront = 1;
    math::Unsigned thirdFront = 1;

    math::Unsigned firstBack = 0;
    math::Unsigned secondBack = 1;
    math::Unsigned thirdBack = 1;
    int count = 2;
    while(true)
    {
        if(pandigital(first9Digits(thirdFront))
        && pandigital(thirdBack))
        {
            std::cout << count << '\n';
            break;
        }
        count++;
        firstBack = secondBack;
        secondBack = thirdBack;
        thirdBack = (firstBack+secondBack) % 1000000000;

        firstFront = secondFront;
        secondFront = thirdFront;
        thirdFront = (firstFront+secondFront);
        while(thirdFront > ten20)
        {
            thirdFront /= 10;
            secondFront /= 10;
            firstFront /= 10;
        }
    }
    return 0;
}