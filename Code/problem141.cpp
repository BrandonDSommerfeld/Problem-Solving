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
#include "algorithms.cpp"

math::Unsigned exp(int base, int e)
{
    math::Unsigned ans = 1;
    for(int i = 0; i < e; i++)
    {
        ans *= base;
    }
    return ans;
}

bool contains(std::vector<math::Unsigned> list, math::Unsigned elem)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i] == elem)
        {
            return true;
        }
    }
    return false;
}

std::vector<math::Unsigned> factors(math::Unsigned num)
{
    std::vector<math::Unsigned> ans{};
    ans.push_back(1);
    for(int i = 0; algorithms::primes[i]*algorithms::primes[i]
    <= num; i++)
    {
        while(num % algorithms::primes[i] == 0)
        {
            num /= algorithms::primes[i];
            int size = ans.size();
            for(int j = 0; j < size; j++)
            {
                if(!contains(ans, algorithms::primes[i]*ans[j]))
                {
                    ans.push_back(algorithms::primes[i]*ans[j]);
                }
            }
        }
    }
    if(num != 1)
    {
        int size = ans.size();
        for(int i = 0; i < size; i++)
        {
            if(!contains(ans, ans[i]*num))
            {
                ans.push_back(ans[i]*num);
            }
        }
    }
    return ans;
}

int main ()
{
    //For a number n, perform division by d to write
    //n = q*d + r
    //We want d, q, r to be a geometric sequence, any order allowed
    //Find the sum of all square n below 10^12 for which this occurs

    //r is strictly less than q
    //Hence we need r^2*d^3+r to be square
    //Write the ratio as n/d, so
    //r^2 n^3 / d^3 + r is square
    //Since we can multiply by the ratio twice, r must be some 
    //multiple of d^2
    //n and d have gcd 1
    //k^2 d^4 n^3 / d^3 + k d^2
    //k^2 d n^3 + k d^2 = a^2
    //kd(kn^3+d) = a^2
    //k = -d^2 + sqrt(d^4+4a^2dn^3) / 2dn^3
    //d = -k^2n^3 + sqrt(k^4n^6+4ka^2) / 2k
    //k must be a factor of 4a^2 so we can pull it out

    /*
    Remainder, ratio, square
    Try to find a pattern from it?
    Only used square starters, probably missed some
    1 2/1 9
    36 2/1 10404     
    1225 2/1 12006225
    41616 2/1 13855173264
    These numbers are both squares and triangular numbers
    Also solutions to 8x^2 + 1 being square
    Something with kn^3+d????

    25 3/1 16900
    67600 3/1 123383587600
    69696 3/2 16394241600
    3969 4/3 37344321
    1936 5/4 7322436
    1089 6/1 256160025
    21609 10/7 1361388609
    5184 10/9 36869184
    521284 24/19 547674002500
    12544 33/16 1380568336
    50625 39/25 9729849600
    81 40/9 576081
    */


    math::Unsigned limit = 1;
    for(int i = 0; i < 12; i++)
    {
        limit *= 10;
    }
    algorithms::generatePrimes(1000000);


    std::set<math::Unsigned> found{};
    math::Unsigned total = 0;

    for(int n = 2; n < 100; n++)
    {
        for(int d = 1; d < n && (static_cast<math::Unsigned>(n)
        *n*n+d)*d < limit; d++)
        {
            if(algorithms::gcd(n,d) == 1)
            {
                math::Unsigned guess = n;
                guess *= n;
                guess *= n;
                guess += d;
                guess *= d;
                for(int k1 = 2; guess < limit; k1++)
                {
                    int k = k1*k1;
                    if(found.find(guess) == found.end() && 
                    algorithms::isSquare(guess))
                    {
                        total += guess;
                        found.insert(guess);
                        std::cout << (k1-1)*(k1-1)*d*d << ' ' << k1-1 << ' ' <<
                        (k1-1)*(k1-1) << ' ' << n << '/' <<
                        d << ' ' << guess << '\n';
                    }
                    guess = (static_cast<math::Unsigned>(k)*n*n*n+d)
                    * k * d;
                }
            }
        }
    }

    std::cout << total << '\n';
    return 0;
}