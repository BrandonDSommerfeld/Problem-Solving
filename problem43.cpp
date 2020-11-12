#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

std::vector<std::string>* permutations(int num, bool first, 
 std::vector<std::string>* prefixes)
{
    if(num == 0)
    {
        return prefixes;
    }
    int start = 0;
    if(first)
    {
        start = 1;
    }
    std::vector<std::string>* result = new std::vector<std::string>();
    for(int i{start}; i < 10; i++)
    {
        for(int j{0}; j < (*prefixes).size(); j++)
        {
            if(((*prefixes)[j]).find(std::to_string(i)) == -1)
            {
                (*result).push_back((*prefixes)[j] + std::to_string(i));
            }
        }
    }
    return permutations(num-1, false, result);
}

int main ()
{
    //Find the sum of all numbers which use every digit 0-9
    //Where the first set of 3 digits is divisible by 1
    //Second set is divisible by 2
    //And each set is divisible by the next prime
    std::vector<std::string> temp {};
    temp.push_back("");
    std::vector<std::string>* nums {permutations(10, true, &temp)};
    long long sum{0};
    //Just brute force all combinations
    //Honestly the permutation function has more creativity
    for(int i{0}; i < (*nums).size(); i++)
    {
        bool works{true};
        if(std::stoll((*nums)[i].substr(1,3)) % 2 != 0)
        {
            works = false;
        }
        if(std::stoll((*nums)[i].substr(2,3)) % 3 != 0)
        {
            works = false;
        }
        if(std::stoll((*nums)[i].substr(3,3)) % 5 != 0)
        {
            works = false;
        }
        if(std::stoll((*nums)[i].substr(4,3)) % 7 != 0)
        {
            works = false;
        }
        if(std::stoll((*nums)[i].substr(5,3)) % 11 != 0)
        {
            works = false;
        }
        if(std::stoll((*nums)[i].substr(6,3)) % 13 != 0)
        {
            works = false;
        }
        if(std::stoll((*nums)[i].substr(7,3)) % 17 != 0)
        {
            works = false;
        }
        if(works)
        {
            sum += std::stoll((*nums)[i]);
        }
    }
    std::cout << sum << '\n';
    return 0;
}