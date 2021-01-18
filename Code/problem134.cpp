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

int main ()
{
    //For each pair of consecutive prime numbers except 3 and 5,
    //Find the smallest number which ends with the smaller and is divisible 
    //by the larger prime, where the smaller prime ranges from
    //5 to 1 million

    //Every time you add 1 to the leading digit, you shift
    //The remainder mod the larger prime
    //Can just calculate directly by finding the modular
    //inverse to know what leading digits you need

    algorithms::generatePrimes(1000050);
    math::Signed total{0};
    for(int i = 2; algorithms::primes[i] < 1000000; i++)
    {
        int smaller = algorithms::primes[i];
        int larger = algorithms::primes[i+1];

        int goal = algorithms::numDigits(smaller);

        math::Unsigned power{1};
        for(int j = 0; j < goal; j++)
        {
            power *= 10;
        }
        total += (((larger-smaller)*algorithms::modularInverse(power, larger))
        %larger)*power + smaller;
    }
    std::cout << total << '\n';
    return 0;
}