#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

bool palin (std::string num)
{
    while(num[0] == '0')
    {
        num = num.substr(1);
    }
    for(int i = 0; i < num.length()/2; i++)
    {
        if(num[i] != num[num.length()-1-i])
        {
            return false;
        }
    }
    return true;
}

int main ()
{
    //Find number of Lychrel numbers below 10000
    //These are numbers which if you reverse and add to itself
    //Eventually forms a palindrome after enough iterations
    //Assume 50 iterations max

    int nums{0};
    for(int i{0}; i < 10000; i++)
    {
        std::string num{std::to_string(i)};
        std::reverse(num.begin(), num.end());
        math::Unsigned start {num};
        start += i;
        bool works{false};
        for(int j {0}; j < 50 && !works; j++)
        {
            if(palin(start.to_string()))
            {
                works = true;
            }
            std::string rev = start.to_string();
            std::reverse(rev.begin(), rev.end());
            math::Unsigned other{rev};
            start += other;
        }
        if(!works)
        {
            nums++;
        }
    }
    std::cout << nums << '\n';
}