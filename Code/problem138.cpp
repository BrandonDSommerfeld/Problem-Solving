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
    //Find the sum of the hypotenuse for the 12 smallest right triangles
    //Where 1 leg is +-1 of double the other
    

    //For the u,v which generate the triple u^2-v^2, 2uv, u^2+v^2
    //u^2-v^2 = 4uv +- 1
    //u^2 - 4uv + 4v^2 - 5v^2 = +-1
    //(u-2v)^2 - 5v^2 = += 1
    //u-2v ~= sqrt5 v
    //u ~= (2+sqrt5)v
    //Thus, use the convergents of continued fractions to compute
    math::Unsigned total = 0;
    int found = 0;
    math::Unsigned numerator = 4;
    math::Unsigned denominator = 1;

    while(found < 12)
    {
        total += numerator*numerator+denominator*denominator;

        math::Unsigned temp = numerator;
        numerator = 4*numerator + denominator;
        denominator = temp;
        
        found++;
    }
    std::cout << total << '\n';
    
    return 0;
}