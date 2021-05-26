#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "math_rational.cpp"
#include "algorithms.cpp"

int main ()
{
    //Find the sum of all factors of numbers from 1 to 10^8
    //However, we also include complex factors, like 
    //2 is divisible by 1+i and 1-i, but 
    //the coefficients must be integers to count 

    unsigned long long total = 0;
    unsigned long long limit = 100000000;

    //Normal, non-complex factors
    for(unsigned long long i = 1; i <= limit; i++)
    {
        //Just how many numbers up to limit are 
        //divisible by this factor, and then 
        //multiply by it since we are summing the factors
        total += (limit / i) * i;
    }

    for(unsigned long long a = 1; a*a <= limit; a++)
    {
        for(unsigned long long b = 1; a*a + b*b <= limit; b++)
        {
            if(algorithms::gcd(a,b) == 1)
            {
                //(a+bi)(ka-kbi)
                //k(a^2 + b^2)
                unsigned long long product = a*a+b*b;
                //Need to do this here, since numbers where a and b do 
                //not have a gcd have extra numbers, since k could be a 
                //factor of the gcd

                //Thus, we only divide by k*product here, when it would 
                //be k*k*product if we got to it from doing a and b, 
                //if we even did, because some numbers exceed the 
                //limit unless fractional k is used
                for(unsigned long long k = 1; k*product <= limit; k++)
                {
                    //Include the 2 for the conjugate of each number
                    total += 2*a*k*(limit/(k*product));
                }
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}