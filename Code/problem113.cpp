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

math::Unsigned choose (int n, int k)
{
    math::Unsigned ans = 1;
    for(int i = k+1; i <= n; i++)
    {
        ans *= i;
    }
    for(int i = 2; i <= n-k; i++)
    {
        ans /= i;
    }
    return ans;
}

int main ()
{
    //How many numbers below 10^100 are not bouncy
    //as defined in the previous problem?

    //Such a number is either increasing or decreasing
    //Consider all the ways to 'place'
    //the increases or decreases in the digits
    //Have your digits and 9 increases or decreases,
    //so d+9 C d arrangments, doubled for increasing
    //and decreasing, then remove those which start with 0
    //Also remove double counts where all digits are equal, there are only
    //10 because I missed all 0's somehow when removing those which
    //start with 0??
    math::Unsigned ans{0};
    for(int d = 1; d <= 100; d++)
    {
        //      incr/decr          start with 0     double counted
        ans += 2*choose(d+9, d) - choose(d+8, d-1) - 10;
    }
    std::cout << ans << '\n';
    return 0;
}