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

int main ()
{
    //Consider (p-1)^n + (p+1)^n 
    //Where p is the nth prime number
    //Consider the remainder when this is divided by p^2
    //Find the least such n that makes this remainder above 10^10
    bool *composite = new bool[1000000];
    for(int i = 0; i < 1000000; i++)
    {
        composite[i] = false;
    }
    
    for(int i = 2; i < 1000; i++)
    {
        if(!composite[i])
        {
            for(int k = 2; i*k < 1000000; k++)
            {
                composite[i*k] = true;
            }
        }
    }
    
    math::Unsigned goal{1};
    for(int i = 0; i < 10; i++)
    {
        goal *= 10;
    }
    int loc = 1;
    for(int i = 2; ; i++)
    {
        if(!composite[i])
        {
            math::Unsigned r = i;
            r *= loc;
            r *= 2;
            math::Unsigned div = i;
            div *= i;
            if(r % div > goal)
            {
                std::cout << i << ' ' << loc << '\n';
                break;
            }
            loc++;
        }
    }
    return 0;
}