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

bool doublePrime(int num1, int num2)
{
    return isPrime(std::stoll(std::to_string(num1) + std::to_string(num2)))
    && isPrime(std::stoll(std::to_string(num2) + std::to_string(num1)));
}

int main ()
{
    //Find 5 primes such that concatenating any 2 in either order
    //is also prime. Their sum must be minimal
    int limit = 34427;
    //This takes forever to run, answer is
    //3 3119 9887 36263 48731
    std::cout << 3+3119+9887+36263+48731 << '\n';
    for(int a{3}; a < limit; a += 2)
    {
        if(isPrime(a))
        {
            
            for(int b{a+2}; b < limit; b += 2)
            {
                if(isPrime(b) && doublePrime(a,b) && a+b < limit)
                {
                    
                    for(int c{b+2}; c < limit; c += 2)
                    {
                        if(isPrime(c) && doublePrime(a,c)
                        && doublePrime(b,c) && a+b+c < limit)
                        {
                            
                            for(int d{c+2}; d < limit; d += 2)
                            {
                                
                                if(isPrime(d) && doublePrime(a,d)
                                && doublePrime(b,d) && doublePrime(c,d)
                                && a+b+c+d < limit)
                                {
                                   for(int e{d+2}; e < limit; e += 2)
                                    {
                                        
                                        if(isPrime(e) && doublePrime(a,e)
                                        && doublePrime(b,e)
                                        && doublePrime(c,e)
                                        && doublePrime(d,e))
                                        {
                                            
                                            std::cout << a << ' ' << b << ' '
                                            << c << ' ' << d << ' ' << e
                                            << '\n';
                                            
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}