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

long long numFactors(long long num)
{
    long long ans = 1;
    int power = 0;
    for(int i = 2; i <= std::sqrt(num); i++)
    {
        if(!composite[i])
        {
            while(num % i == 0)
            {
                num /= i;
                power++;
            }
            std::cout << i << ' ' << power+1 << '\n';
            ans *= power+1;
            power = 0;
        }
    }
    if(num != 1)
    {
        ans *= 2;
    }
    return ans;
}

int main ()
{
    //Find the first n which has more than 1000 solutions to
    // 1/x + 1/y = 1/n
    //Where x and y are integers
    
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
    //You can rewrite the equation as
    //xy - nx - ny = 0
    //xy - nx - ny + n^2 = n^2
    //(x-n)(y-n) = n^2
    //Thus, the number of solutions is the number of factors
    //of n^2
    //Brute forcing here was pretty quick, but
    //you can be a lot smarter by purposely combining
    //small primes
    for(long long i = 1; ; i++)
    {
        if(composite[i] && (numFactors(i*i)+1)/2 > 1000)
        {
            std::cout << i << '\n';
            break;
        }
    }
    return 0;
}