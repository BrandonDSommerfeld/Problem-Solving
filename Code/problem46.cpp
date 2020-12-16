#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find the smallest odd composite number which cannot be written
    //as a prime + 2*x^2

    bool* composite = new bool[1000000];
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
    composite[0] = true;
    composite[1] = true;


    //Just go through composite numbers and brute force all squares
    for(int i{9}; i < 1000000; i += 2)
    {
        if(composite[i])
        {
            bool works{false};
            for(int j{1}; j < std::sqrt(i); j++)
            {
                if(i-2*j*j > 0 && !composite[i-2*j*j])
                {
                    works = true;
                }
            }
            if(!works)
            {
                std::cout << i << '\n';
                return 0;
            }
        }
    }
    return 0;
}