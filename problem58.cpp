#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

bool isPrime (unsigned long long num)
{
    for(int i{2}; i <= std::round(std::ceil(std::sqrt(num))); i++)
    {
        if(num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main ()
{
    //Place numbers in a spiral
    // 5 4 3
    // 6 1 2
    // 7 8 9
    //Keep going around, count how many primes are on diagonals
    //Find side length where less than 10% of diagonals
    //are prime. This includes the center 1

    unsigned long long upLeft{5};
    unsigned long long upRight{3};
    unsigned long long downLeft{7};
    int numPrimes{0};
    //Just iterate and add in next 4 numbers until found
    //DownRight is square numbers, and never prime
    //Actually can't use a sieve, because numbers get too big
    for(int i{0}; i < 100000; i++)
    {
        if(isPrime(upRight))
        {
            numPrimes++;
        }
        if(isPrime(upLeft))
        {
            numPrimes++;
        }
        if(isPrime(downLeft))
        {
            numPrimes++;
        }

        upRight += 8*i+10;
        upLeft += 8*i+12;
        downLeft += 8*i+14;

        if((4*i+5)/numPrimes == 10)
        {
            std::cout << (2*i+3) << '\n';
            return 0;
        }
    }
    return 0;
}