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
    //Find the smallest number such that x, 2x, ... 6x
    //All have the same digits and are just permutations
    
    //Just brute force with the permutation function

    for(int i{1}; i < 1000000; i++)
    {
        if(permutations(i, 2*i, 3*i) && permutations(4*i, 5*i, 6*i)
            && permutations(i, 4*i, 2*i))
            {
                std::cout << i << '\n';
                return 0;
            }
    }
    
    return 0;
}