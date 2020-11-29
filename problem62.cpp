#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

bool permutations(unsigned long long num1, unsigned long long num2)
{
    int digitCount1[10];
    int digitCount2[10];
    for(int i{0}; i < 10; i++)
    {
        digitCount1[i] = 0;
        digitCount2[i] = 0;
    }

    //Count up how many times each digit is used
    while(num1 > 0)
    {
        digitCount1[num1%10]++;
        num1/=10;
    }
    while(num2 > 0)
    {
        digitCount2[num2%10]++;
        num2/=10;
    }

    //If they didn't all use the same digit the same number of times
    //They are not permutations of each other
    for(int i{0}; i < 10; i++)
    {
        if(digitCount1[i] != digitCount2[i])
        {
            return false;
        }
    }
    return true;
}

int digits (unsigned long long num)
{
    int digit{0};
    while(num > 0)
    {
        digit++;
        num /= 10;
    }
    return digit;
}

int main ()
{
    //Find the smallest cube for which itself and 4 permutations
    //Are all cubes

    unsigned long long place{100};
    int prev{0};
    std::vector<unsigned long long> cubes{};
    //Just brute force search over all cubes of a given length
    while(place < 10000000)
    {
        int dig = digits(place*place*place);
        //We hit the next number of digits, iterate over current collection
        if(dig > prev)
        {
            prev = dig;
            for(int i{0}; i < cubes.size(); i++)
            {
                unsigned long long current = cubes[i];
                int num{0};
                for(int j = i + 1; j < cubes.size(); j++)
                {
                    if(permutations(current, cubes[j]))
                    {
                        num++;
                    }
                }
                if(num == 4)
                {
                    std::cout << current << '\n';
                    return 0;
                }
            }
            cubes = std::vector<unsigned long long>{};
        }
        cubes.push_back(place*place*place);
        place++;
    }
    return 0;
}