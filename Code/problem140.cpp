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
#include "algorithms.cpp"

bool contains (std::vector<math::Signed> list, math::Signed elem)
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
    //Consider the numbers given by
    //G(1) = 1
    //G(2) = 4
    //G(n) = G(n-1)+G(n-2)
    //Once again, we have the function
    //A(x) = xG(1) + x^2G(2) + ...
    //We only care about integer values for this function
    //Find the sum of the first 30 integers for which x is rational

    //a + ax = 1/xa - 3x - 1
    //(a+3)x^2 + (a+1)x - a = 0
    //x = (-a-1) + sqrt((a+1)^2+4a(a+3))/(2a+6)
    //Need a^2+2a+1+4a^2+12a to be square
    //5a^2+14a+1 = k^2
    //Basically 137, used online solver to get recurrence relations

    math::Signed x1 = 0;
    math::Signed y1 = -1;
    math::Signed x2 = x1;
    math::Signed y2 = y1;

    int iterations = 20;
    std::vector<math::Signed> found{};
    for(int i = 0; i < iterations; i++)
    {
        if(x1 > 0 && !contains(found, x1))
        {
            found.push_back(x1);
        }
        if(x2 > 0 && !contains(found, x2))
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 14;
        y1 = -20*temp1-9*temp2-28;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 14;
        y2 = 20*temp1-9*temp2+28;
    }

    x1 = 2;
    y1 = -7;
    x2 = x1;
    y2 = y1;
    for(int i = 0; i < iterations; i++)
    {
        if(x1 > 0 && !contains(found, x1))
        {
            found.push_back(x1);
        }
        if(x2 > 0 && !contains(found, x2))
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 14;
        y1 = -20*temp1-9*temp2-28;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 14;
        y2 = 20*temp1-9*temp2+28;
    }

    x1 = 0;
    y1 = 1;
    x2 = x1;
    y2 = y1;
    for(int i = 0; i < iterations; i++)
    {
        if(x1 > 0 && !contains(found, x1))
        {
            found.push_back(x1);
        }
        if(x2 > 0 && !contains(found, x2))
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 14;
        y1 = -20*temp1-9*temp2-28;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 14;
        y2 = 20*temp1-9*temp2+28;
    }

    x1 = -4;
    y1 = 5;
    x2 = x1;
    y2 = y1;
    for(int i = 0; i < iterations; i++)
    {
        if(x1 > 0 && !contains(found, x1))
        {
            found.push_back(x1);
        }
        if(x2 > 0 && !contains(found, x2))
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 14;
        y1 = -20*temp1-9*temp2-28;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 14;
        y2 = 20*temp1-9*temp2+28;
    }

    x1 = -3;
    y1 = 2;
    x2 = x1;
    y2 = y1;
    for(int i = 0; i < iterations; i++)
    {
        if(x1 > 0 && !contains(found, x1))
        {
            found.push_back(x1);
        }
        if(x2 > 0 && !contains(found, x2))
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 14;
        y1 = -20*temp1-9*temp2-28;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 14;
        y2 = 20*temp1-9*temp2+28;
    }

    x1 = -3;
    y1 = -2;
    x2 = x1;
    y2 = y1;
    for(int i = 0; i < iterations; i++)
    {
        if(x1 > 0 && !contains(found, x1))
        {
            found.push_back(x1);
        }
        if(x2 > 0 && !contains(found, x2))
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 14;
        y1 = -20*temp1-9*temp2-28;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 14;
        y2 = 20*temp1-9*temp2+28;
    }

    std::sort(found.begin(), found.end());
    math::Signed total = 0;
    for(int i = 0; i < 30; i++)
    {
        total += found[i];
    }
    std::cout << total << '\n';
    
    return 0;
}