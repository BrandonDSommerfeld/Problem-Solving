#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <bitset>
#include "math_unsigned.cpp"

bool pandigital(std::string num)
{
    //Calculate whether number uses all digits exactly once
    bool used[num.length()];
    used[0] = true;
    for(int i{1}; i < num.length(); i++)
    {
        used[i] = false;
    }
    while(num.length() > 0)
    {
        int digit = num[num.length()-1] - 48;
        if(used[digit]) return false;
        used[digit] = true;
        num = num.substr(0, num.length()-1);
    }
    return true;
}

bool prime (int num)
{
    for(int i{2}; i <= std::round(std::sqrt(num)); i++)
    {
        if(num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main ()
{
    //What is the largest prime which uses all digits 1-n?
    //Brute force numbers downwards
    for(int i{0}; i < 1000000000; i++)
    {
        if(pandigital(std::to_string(i)))
        {
            if(prime(i))
            {
                std::cout << i << '\n';
            }
        }
    }
    //This times out past 7 digits, but apparently there are
    //no 8 or 9 digit such primes
}