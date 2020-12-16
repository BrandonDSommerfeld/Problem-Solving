#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <bitset>
#include "math_unsigned.cpp"

bool palin (std::string num)
{
    while(num[0] == '0')
    {
        num = num.substr(1);
    }
    for(int i = 0; i < num.length()/2; i++)
    {
        if(num[i] != num[num.length()-1-i])
        {
            return false;
        }
    }
    return true;
}

int main ()
{
    //Find the sum of all numbers below 1000000 which are palindromes
    //In both base 10 and base 2
    bool* palindrome = new bool[1000000];
    for(int i = 1; i < 1000000; i++)
    {
        if(palin(std::to_string(i)))
        {
            palindrome[i] = true;
        }
        else
        {
            palindrome[i] = false;
        }
    }
    int sum{0};
    //After doing base check, check for base 2
    for(int i = 1; i < 1000000; i++)
    {
        if(palindrome[i])
        {
            if(palin(std::bitset<32>(i).to_string()))
            {
                sum += i;
            }
        }
    }
    std::cout << sum << '\n';
    return 0;
}