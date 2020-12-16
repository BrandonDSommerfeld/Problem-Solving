#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find the last 10 digits of
    //1^1 + 2^2 + 3^3 + ... 1000^1000

    //Just use the modular arithmetic properties of unsigned numbers

    unsigned long long answer {0};
    for(unsigned long long i{1}; i <= 1000; i++)
    {
        unsigned long long term{1};
        for(unsigned long long j {0}; j < i; j++)
        {
            term *= i;
            term %= 10000000000LL;
        }
        answer += term;
    }
    std::cout << (answer%10000000000LL) << '\n';
    return 0;
}