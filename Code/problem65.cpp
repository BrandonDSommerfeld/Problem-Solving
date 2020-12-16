#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

math::Unsigned gcd(math::Unsigned num1, math::Unsigned num2)
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

math::Unsigned digits (math::Unsigned num)
{
    math::Unsigned sum = 0;
    while(num > 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main ()
{
    //Find the sum of the digits of the numerator of the 100th
    //Continued fraction cutoff for e as
    //e = 2 + 1/(1+1/(2+1/...))
    //And then it alternates with 2 1's, then the next even number

    //Start from the bottom and work upwards
    math::Unsigned num = 1;
    math::Unsigned denom = 1;
    for(int i = 99; i > 0; i--)
    {
        if(i % 3 == 0)
        {
            num += 2*(i/3)*denom;
            math::Unsigned temp = num;
            num = denom;
            denom = temp;
            math::Unsigned g = gcd(num, denom);
            num /= g;
            denom /= g;
        }
        else
        {
            num += denom;
            math::Unsigned temp = num;
            num = denom;
            denom = temp;
            math::Unsigned g = gcd(num, denom);
            num /= g;
            denom /= g;
        }
    }

    //This gets flipped at the end when it shouldn't, so actually
    //Flip it, and then it is off by 1 since the fraction starts 
    //With 2, not 1
    denom += num;
    std::cout << digits(denom) << '\n';
    return 0;
}