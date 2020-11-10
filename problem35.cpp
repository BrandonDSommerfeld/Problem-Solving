#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

std::string rotate (std::string num)
{
    num += num[0];
    num = num.substr(1);
    return num;
}

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
    //For each prime, use rotate as a string to rotate it
    int num{0};
    for(int i = 2; i < 1000000; i++)
    {
        if(!composite[i])
        {
            std::string boi{std::to_string(i)};
            std::string copy{rotate(boi)};
            bool works{true};
            while(copy != boi && works)
            {
                if(composite[std::stoi(copy)])
                {
                    works = false;
                }
                copy = rotate(copy);
            }
            if(works)
            {
                num++;
            }
        }
    }
    std::cout << num << '\n';
    return 0;
}