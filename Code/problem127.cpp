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

static bool* composite;
static std::vector<int> primes;

int gcd(int num1, int num2)
{
    if(num1 == 0)
    {
        return num2;
    }
    if(num2 == 0)
    {
        return num1;
    }
    if(num1 > num2)
    {
        return gcd(num1 % num2, num2);
    }
    return gcd(num1, num2 % num1);
}

int rad (int n)
{
    int ans = 1;
    for(int i = 0; n > 1; i++)
    {
        if(n % primes[i] == 0)
        {
            ans *= primes[i];
            n /= primes[i];
        }
        while(n % primes[i] == 0)
        {
            n /= primes[i];
        }
    }
    return ans;
}

int main ()
{
    //Call a triple an abc hit if
    // gcd(a,b) = gcd(a,c) = gcd(b,c) = 1
    // a < b
    // a+b = c
    // rad(abc) < c
    // Where rad is the product of all distinct prime factors

    //Find the sum of all c in abc hits for c < 120000

    //Mega slow, answer is 18407904
    //Main idea is that at least 2 of the numbers must
    //have a prime factor more than once, otherwise
    //the product is too large
    int limit = 120000;
    composite = new bool[limit];
    for(int i{2}; i < 1000; i++)
    {
        if(!composite[i])
        {
            for(int j{2}; i*j < limit; j++)
            {
                composite[i*j] = true;
            }
        }
    }

    for(int i = 2; i < limit; i++)
    {
        if(!composite[i])
        {
            primes.push_back(i);
        }
    }

    math::Unsigned total = 0;
    int numHits = 0;
    std::set<int> seen{};
    for(int c = 0; primes[c]*primes[c] < limit; c++)
    {
        int val = primes[c];
        if(c == 0)
        {
            val += 2;
        }
        for(int k = 1; k*val*val < limit; k++)
        {
            if(seen.find(k*val*val) == seen.end())
            {
                std::set<int> seen2{};
                for(int a = 0; primes[a]*primes[a] < k*val*val; a++)
                {
                    int val2 = primes[a];
                    if(gcd(val2,k) == 1 && gcd(val2, val) == 1)
                    {
                        for(int d = 1; val2*val2*d < k*val*val; d++)
                        {
                            if(gcd(d,k) == 1 && gcd(d, val) == 1)
                            {
                                
                                long long r = rad(k*val*val);
                                r *= rad(d*val2*val2);
                                r *= rad(k*val*val-d*val2*val2);
                                if(r < k*val*val &&
                                seen2.find(d*val2*val2) == seen2.end()
                                && seen2.find(k*val*val-d*val2*val2) == seen2.end())
                                {     
                                    std::cout << k*val*val-d*val2*val2 << ' ' <<
                                    d*val2*val2 << ' ' << k*val*val << '\n';
                                    numHits++;
                                    total += k*val*val;
                                    seen.insert(k*val*val);
                                    seen2.insert(d*val2*val2);
                                    seen2.insert(k*val*val-d*val2*val2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << numHits << '\n';
    std::cout << total << '\n';
    return 0;
}