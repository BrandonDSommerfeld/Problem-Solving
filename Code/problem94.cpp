#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include "math_unsigned.cpp"


int gcd(int num1, int num2)
{
    if(num1 > num2)
    {
        if(num1 % num2 == 0)
        {
            return num2;
        }
        return gcd(num1-num2*(num1/num2), num2);
    }
    if(num2 % num1 == 0)
    {
        return num1;
    }
    return gcd(num2-num1*(num2/num1), num1);
}

int main ()
{
    //An almost equilateral triangle has 2 equal sides, and 1 side
    //which differs by 1

    //Find the sum of the perimeters of all such triangles
    //with integer sides and areas with perimeter <= 1 billion

    //Integer area requires sides to create a pythagorean triple
    //With the height, so just look for triples
    math::Unsigned total = 0;
    int limit = 333333334;
    for(int m = 2; m < 20000; m++)
    {
        for(int n = 1; n < m; n++)
        {
            if((m+n)%2 == 1 && gcd(m,n) == 1)
            {
                int a = m*m-n*n;
                int b = 2*m*n;
                int c = m*m+n*n;
                if(a <= limit && c <= limit &&
                2*a == c+1 || 2*a == c-1)
                {
                    total += 2*a;
                    total += 2*c;
                }
                else if (b <= limit && c <= limit
                   && 2*b == c+1 || 2*b == c-1)
                {
                    total += 2*b;
                    total += 2*c;
                }
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}