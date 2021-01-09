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

math::Unsigned recursive (int num, int start)
{
    if(num == 0)
    {
        math::Unsigned ans{1};
        for(int i = start; i <= 15; i++)
        {
            ans *= i;
        }
        return ans;
    }
    if(start > 15)
    {
        return 0;
    }
    math::Unsigned ans{0};
    math::Unsigned multiplier{1};
    for(int i = start; i <= 15; i++)
    {
        ans += multiplier * recursive(num-1, i+1);
        multiplier *= i;
    }
    return ans;
}

int main ()
{
    //There is a game where there is a bag with 1 red disc, and 1 blue
    //Each turn, one is drawn at random, then another red is added
    //At the end, you win if you have drawn more blue than red
    //Find the odds of winning, then use that to compute the maximum
    //reward that can be provided without going under
    
    math::Unsigned denom{1};
    for(int i = 2; i <= 16; i++)
    {
        denom *= i;
    }
    //Do some weird stuff where I calculate all ways to select
    //The blue discs, while multiplying by the odds for the red ones
    math::Unsigned numerator{0};
    for(int i = 8; i <= 15; i++)
    {
        numerator += recursive(i, 1);
    }
    std::cout << numerator << '\n';
    std::cout << denom << '\n';
    std::cout << denom / numerator << '\n';
    return 0;
}