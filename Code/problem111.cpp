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

static std::vector<int> primes;

bool isPrime(math::Unsigned num)
{
    for(int i = 0; i < primes.size() && primes[i]*primes[i] <= num; i++)
    {
        if(num % primes[i] == 0)
        {
            return false;
        }
    }
    return true;
}

math::Unsigned recursive2(std::string num, int digit)
{
    if(num[0] == '0')
    {
        return 0;
    }
    if(num.find('a') == -1)
    {
        math::Unsigned temp{num};
        if(isPrime(temp))
        {
            return temp;
        }
        return 0;
    }

    math::Unsigned ans = 0;
    int loc = num.find('a');
    for(int d = 0; d < 10; d++)
    {
        if(d != digit)
        {
            std::string copy{num};
            copy[loc] = d+48;
            ans += recursive2(copy, digit);
        }
    }
    return ans;
}

math::Unsigned recursive1(std::string num, int replacements, int d)
{
    if(replacements == 0)
    {
        return recursive2(num, d);
    }
    math::Unsigned ans = 0;
    for(int i = num.length() - 1; i >= 0; i--)
    {
        if(num[i] == 'a')
        {
            break;
        }
        std::string copy{num};
        copy[i] = 'a';
        ans += recursive1(copy, replacements-1, d);
    }
    return ans;
}

math::Unsigned sum(int d, int num)
{
    std::string temp{};
    for(int i = 0; i < 10; i++)
    {
        temp += d + 48;
    }
    return recursive1(temp, 10-num, d);
}

int main ()
{
    //Consider all 10 digit prime numbers
    //For each digit 0-9, find the primes which have the most
    //of that digit
    //Find the sum of all of these primes over all digits
    bool *composite = new bool[100000];
    for(int i = 2; i < 100000; i++)
    {
        composite[i] = false;
    }
    for(int i = 2; i < 1000; i++)
    {
        if(!composite[i])
        {
            for(int k = 2; i*k < 100000; k++)
            {
                composite[i*k] = true;
            }
        }
    }

    primes = *(new std::vector<int>{});
    primes.reserve(10000);
    for(int i = 2; i < 100000; i++)
    {
        if(!composite[i])
        {
            primes.push_back(i);
        }
    }

    //So this is a complicated setup
    //Using the recursive functions above, I select all places for
    //non-repeating digits, and then fill them in with digits
    //and test if they are prime
    math::Unsigned total = 0;
    for(int d = 0; d < 10; d++)
    {
        for(int num = 9; num >= 0; num--)
        {
            math::Unsigned temp = sum(d, num);
            if(temp != 0)
            {
                total += temp;
                break;
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}