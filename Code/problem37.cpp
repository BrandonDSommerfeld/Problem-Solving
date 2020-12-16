#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <bitset>
#include "math_unsigned.cpp"

int main ()
{
    //Find sum of all primes such that repeatedly removing the
    //leftmost digit always leaves a prime, and from the right too

    //Find all primes
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
    composite[1] = true;

    int num{0};
    int sum{0};
    std::vector<std::string> found {};
    found.push_back("3");
    found.push_back("7");
    //Found only has candidates for left removal
    for(int i{0}; i < found.size() && num < 11; i++)
    {
        for(int j = 1; j < 10; j++)
        {
            //Add every possible leading digit, probably could 
            //just do 1,3,7,9, because ending in others not prime
            std::string candidate{std::to_string(j) + found[i]};
            //If prime, goes onto left removal possibiliites
            if(!composite[std::stoi(candidate)])
            {
                found.push_back(candidate);
            }
            bool works{true};
            //Already know left removal works, test for right
            while(candidate.length() > 0 && works)
            {
                if(composite[std::stoi(candidate)])
                {
                    works = false;
                }
                candidate = candidate.substr(0, candidate.length()-1);
            }
            if(works)
            {
                num++;
                sum += std::stoi(found[found.size()-1]);
            }
        }
    }
    std::cout << num << '\n';
    std::cout << sum << '\n';
    return 0;
}