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

int digitSum(math::Unsigned num)
{
    int ans = 0;
    while(num > 0)
    {
        ans += (num % 10).to_uint();
        num /= 10;
    }
    return ans;
}

bool contains(std::vector<math::Unsigned> list, math::Unsigned elem)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i] == elem)
        {
            return true;
        }
    }
    return false;
}

int main ()
{
    //Find the 30th number which is a power of the sum of its digits

    //Just brute force a bunch of powers and hope I found at least 30
    std::vector<math::Unsigned> found{};
    for(int i = 2; i < 100; i++)
    {
        for(int j = 2; j < 50; j++)
        {
            math::Unsigned guess{1};
            for(int e = 0; e < j; e++)
            {
                guess *= i;
            }
            if(digitSum(guess) == i && !contains(found, guess))
            {
                found.push_back(guess);   
            }
        }
    }
    std::sort(found.begin(), found.end());
    std::cout << found[29] << '\n';
    return 0;
}