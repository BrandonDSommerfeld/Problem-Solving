#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include "math_unsigned.cpp"
#include "math_signed.cpp"

static bool *composite;


math::Unsigned value(std::vector<int> powers, std::vector<int> primes)
{
    math::Unsigned ans = 1;
    for(int i = 0; i < powers.size(); i++)
    {
        for(int j = 0; j < powers[i]; j++)
        {
            ans *= primes[i];
        }
    }
    return ans;
}

int factors(std::vector<int> powers)
{
    int ans = 1;
    for(int i = 0; i < powers.size(); i++)
    {
        ans *= 2*powers[i]+1;
    }
    return ans;
}

int main ()
{
    //Similar to 108, find n such that 
    //1/x + 1/y = 1/n
    //has more than 4 million solutions
    //As outlined in problem 108, need a lot of factors
    
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
    std::vector<int> primes{};
    int used = 0;
    for(int i = 2; used < 100; i++)
    {
        if(!composite[i])
        {
            primes.push_back(i);
            used++;
        }
    }

    //Create the number from the ground up, by adding
    //Whichever prime factor increases the number of factors
    //the most per its value
    //This overshoots the target of 4 million factors though, 
    //so at the end I make a copy and reduce to be as close to 4 million
    //as possible
    std::vector<int> powers{};
    while((factors(powers)+1)/2 < 4000000)
    {
        double best = 0;
        int loc = -1;
        for(int i = 0; i < powers.size(); i++)
        {
            double bonus = static_cast<double>(2)/
            (2*powers[i]+1) / primes[i];
            if(bonus > best)
            {
                best = bonus;
                loc = i;
            }
        }
        if(3.0 / primes[powers.size()] > best)
        {
            powers.push_back(1);
        }
        else
        {
            powers[loc]++;   
        }
    }

    for(int i = 0; i < powers.size(); i++)
    {
        std::cout << powers[i] << ' ';
    }
    std::cout << '\n';

    std::vector<int> copy{};
    for(int i = 0; i < powers.size(); i++)
    {
        copy.push_back(powers[i]);
    }
    copy[0]--;
    copy[0]--;

    copy[0]--;
    copy[1]--;
    std::cout << (factors(copy)+1)/2 << '\n';
    std::cout << value(copy, primes) << '\n';
    return 0;
}