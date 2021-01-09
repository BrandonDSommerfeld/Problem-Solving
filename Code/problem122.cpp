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

int adjustedLog(int num)
{
    int ans = 0;
    while(num > 1)
    {
        if(num % 2 == 1)
        {
            ans++;
        }
        ans++;
        num /= 2;
    }
    return ans;
}

int main ()
{
    //For numbers 1 to 200, what is the most efficient way to compute
    // x^n
    //Generally, binary where you computing x^2, x^4, x^8, ...
    //and combining is pretty good, but it isn't always the best

    //Something to do with prime factors?
    //You create it by creating 1 prime factor, then
    //using it as n for another prime factor?
    int total = 0;
    int required[201];
    for(int i = 1; i <= 200; i++)
    {
        required[i] = 0;
        int current = 0;
        int copy = i;
        for(int j = 2; j <= copy; j++)
        {
            while(copy % j == 0)
            {
                current += required[j];
                copy /= j;
            }
        }
        if(current == 0)
        {
            current = adjustedLog(i);
        }
        required[i] = current;
        total += current;
        std::cout << i << ' ' << current << '\n';
    }
    std::cout << total << '\n';
    
    return 0;
}