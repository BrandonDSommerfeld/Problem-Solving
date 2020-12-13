#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

static bool* composite;

int totient(int num)
{
    if(!composite[num])
    {
        return num-1;
    }
    int result = num;
    for(int i = 2; i <= num/2; i++)
    {
        if(!composite[i] && num % i == 0)
        {
            result /= i;
            result *= i-1;
        }
    }
    return result;
}

int main ()
{
    //Find the number value n <= 1000000
    //Such that n divided by its totient is maximized

    composite = new bool[1000000];
    for(int i{2}; i < 1000; i++)
    {
        if(!composite[i])
        {
            for(int j{2}; i*j < 1000000; j++)
            {
                composite[i*j] = true;
            }
        }
    }

    //Just brute force with my totient function
    double best = 0;
    int place = 0;
    for(int i = 6; i <= 1000000; i++)
    {
        double num = static_cast<double>(i) / totient(i);
        if(num > best)
        {
            best = num;
            place = i;
        }
    }
    std::cout << best << '\n';
    std::cout << place << '\n';
    return 0;
}