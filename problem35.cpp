#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //A circular prime is a number where all rotations of the digits are 
    //prime: 197, 719, 971
    //Find the number of such primes below 1000000
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
    return 0;
}