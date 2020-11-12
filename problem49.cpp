#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

bool permutations(int num1, int num2, int num3)
{
    int digitCount1[10];
    int digitCount2[10];
    int digitCount3[10];
    for(int i{0}; i < 10; i++)
    {
        digitCount1[i] = 0;
        digitCount2[i] = 0;
        digitCount3[i] = 0;
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
    while(num3 > 0)
    {
        digitCount3[num3%10]++;
        num3/=10;
    }

    //If they didn't all use the same digit the same number of times
    //They are not permutations of each other
    for(int i{0}; i < 10; i++)
    {
        if(digitCount1[i] != digitCount2[i] || digitCount3[i] != digitCount2[i])
        {
            return false;
        }
    }
    return true;
}

int main ()
{
    //Find an arithmetic sequence of 3 different 4 digit primes
    //Where each prime is a permutation of the others
    //That isn't 1487 4817 8147

    bool* composite = new bool[10000];
    for(int i{2}; i < 1000; i++)
    {
        if(!composite[i])
        {
            for(int j{2}; i*j < 10000; j++)
            {
                composite[i*j] = true;
            }
        }
    }
    //Brute force all possible starting terms and differences
    for(int i{1001}; i < 10000; i += 2)
    {
        if(!composite[i])
        {
            for(int j{2}; i+2*j < 10000; j += 2)
            {
                bool works{true};
                if(composite[i+j])
                {
                    works = false;
                }
                if(composite[i+2*j])
                {
                    works = false;
                }
                if(works)
                {
                    if(permutations(i, i+j, i+2*j)
                    && !(i == 1487 && j == 3330))
                    {
                        std::cout << i << i+j << i+2*j << '\n';
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}