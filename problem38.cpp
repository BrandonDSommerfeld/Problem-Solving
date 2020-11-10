#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <bitset>
#include "math_unsigned.cpp"

bool pandigital(int num)
{
    //Calculate whether number uses all 9 digits exactly once
    bool used[10];
    used[0] = true;
    for(int i{1}; i < 10; i++)
    {
        used[i] = false;
    }
    while(num > 0)
    {
        int digit = num % 10;
        if(used[digit]) return false;
        used[digit] = true;
        num /= 10;
    }
    return true;
}

int main ()
{
    //For a given number k, compute the products k, 2k, 3k, 4k ... nk
    //And concatenate them into k2k3k...nk
    //Find the largest 9 digit number which can be written this way,
    //And has all numbers 1-9 in it

    std::string best{"123456789"};
    //Just brute force all possible products like this
    for(int i{1}; i < 10000; i++)
    {
        std::string prod{};
        int j{1};
        while(prod.length() < 9)
        {
            prod += std::to_string(i*j);
            j++;
        }
        //If of length 9, pandigital, and better
        if(prod.length() == 9)
        {
            if(pandigital(std::stoi(prod)) && std::stoi(prod) > std::stoi(best))
            {
                best = prod;
            }
        }
    }
    std::cout << best << '\n';
    return 0;
}