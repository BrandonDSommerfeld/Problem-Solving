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
    //Take a pythagorean triple, place the hypotenuse along
    //the side of a square 4 times to make a square with a hole
    //in the middle.
    //If the perimeter is below 100 million, how many such 
    //squares side lengths are divisible by the inner

    //Essentially, pythagorean triples where a-b divides c
    //Pretty easy with the formula to generate triples

    int total = 0;
    static constexpr int limit = 100000000;
    for(long long u = 1; u < 1000000; u++)
    {
        for(long long v = u+1; v < 1000000; v++)
        {
            if(algorithms::gcd(u,v) == 1)
            {
                long long a = v*v-u*u;
                long long b = 2*u*v;
                long long c = v*v+u*u;
                if(a+b+c < limit)
                {
                    if(a > b)
                    {
                        if(c % (a-b) == 0)
                        {
                            total += limit/(a+b+c);
                        }
                    }
                    else
                    {
                        if(c % (b-a) == 0)
                        {
                            total += limit/(a+b+c);
                        }
                    }
                }
                else
                {
                    break;
                }
                
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}