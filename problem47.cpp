#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

static bool* composite;

int primeFactors(int num)
{
    int factors{0};
    int prime{2};
    bool used{false};
    while(num > 1)
    {
        if(num % prime == 0)
        {
            num /= prime;
            //Only count each prime once
            if(!used)
            {
                factors++;
                used = true;
            }
        }
        else
        {  
            //Move to next prime
            prime++;
            while(composite[prime])
            {
                prime++;
            }
            used = false;
        }
        
    }
    return factors;
}

int main ()
{
    //Find the first sequence of consecutive integers such that each
    //Number has 4 distinct prime factors

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
    composite[1] = true;
    composite[0] = true;

    //Just brute force sequences
    //Most of the work is in the helper function
    for(int i{1}; i < 1000000; i++)
    {
        bool works{true};
        if(primeFactors(i) != 4)
        {
            works = false;
        }
        if(primeFactors(i+1) != 4)
        {
            works = false;
        }
        if(primeFactors(i+2) != 4)
        {
            works = false;
        }
        if(primeFactors(i+3) != 4)
        {
            works = false;
        }
        if(works)
        {
            std::cout << i << '\n';
            return 0;
        }
    }

    return 0;
}