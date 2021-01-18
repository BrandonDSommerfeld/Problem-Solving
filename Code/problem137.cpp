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

int main ()
{
    //Consider the infinite function
    //A(x) = 0 + x + x^2 + 2x^3 + 3x^4 + 5x^5 ...
    //Where the coefficients are Fibonacci numbers
    //We want values of x for which this is a positive integer
    //Find the 15th such A(x) where x is rational

    //You can write A(x) + xA(x) = 1/x A(x) - 1
    //x = ((-a-1) + sqrt(5a^2+2a+1))/(2a)
    //Thus, you need 5a^2+2a+1 to be square
    //The smart solution is to look for pythagorean triples of the form
    // (a+1)^2 + (2a)^2 = k^2
    //But I just used an online equation solver
    //To get initial solutions and a recurrence relation

    math::Signed x1 = 0;
    math::Signed y1 = -1;
    math::Signed x2 = x1;
    math::Signed y2 = y1;

    std::vector<math::Signed> found{};
    for(int i = 0; i < 15; i++)
    {
        if(x1 > 0)
        {
            found.push_back(x1);
        }
        if(x2 > 0)
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 2;
        y1 = -20*temp1-9*temp2-4;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 2;
        y2 = 20*temp1-9*temp2+4;
    }

    x1 = 2;
    y1 = 5;
    x2 = x1;
    y2 = y1;
    for(int i = 0; i < 15; i++)
    {
        if(x1 > 0)
        {
            found.push_back(x1);
        }
        if(x2 > 0)
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 2;
        y1 = -20*temp1-9*temp2-4;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 2;
        y2 = 20*temp1-9*temp2+4;
    }

    x1 = 0;
    y1 = -1;
    x2 = x1;
    y2 = y1;
    for(int i = 0; i < 15; i++)
    {
        if(x1 > 0)
        {
            found.push_back(x1);
        }
        if(x2 > 0)
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 2;
        y1 = -20*temp1-9*temp2-4;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 2;
        y2 = 20*temp1-9*temp2+4;
    }

    x1 = -1;
    y1 = 2;
    x2 = x1;
    y2 = y1;
    for(int i = 0; i < 15; i++)
    {
        if(x1 > 0)
        {
            found.push_back(x1);
        }
        if(x2 > 0)
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 2;
        y1 = -20*temp1-9*temp2-4;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 2;
        y2 = 20*temp1-9*temp2+4;
    }

    x1 = -1;
    y1 = -2;
    x2 = x1;
    y2 = y1;
    for(int i = 0; i < 15; i++)
    {
        if(x1 > 0)
        {
            found.push_back(x1);
        }
        if(x2 > 0)
        {
            found.push_back(x2);
        }
        math::Signed temp1 = x1;
        math::Signed temp2 = y1;

        x1 = -9*temp1 - 4*temp2 - 2;
        y1 = -20*temp1-9*temp2-4;

        temp1 = x2;
        temp2 = y2;

        x2 = -9*temp1 + 4*temp2 - 2;
        y2 = 20*temp1-9*temp2+4;
    }

    std::sort(found.begin(), found.end());
    for(int i = 0; i < found.size(); i++)
    {
        std::cout << i << ' ' << found[i] << '\n';
    }
    return 0;
}