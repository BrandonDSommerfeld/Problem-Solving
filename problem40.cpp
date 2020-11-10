#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <bitset>
#include "math_unsigned.cpp"

int main ()
{
    //Create the decimal 0.12345... by concatentating all naturals
    //Find product d1 * d10*d100*d1000*d10000*d100000*d1000000
    int prod{1};
    std::string boi{".1"};
    int next{2};
    while(boi.length() <= 1000000)
    {
        boi += std::to_string(next);
        next++;
    }
    //Just brute force the entire string
    //Use ascii values, too lazy to use string to int
    prod *= (boi[10]-48);
    prod *= (boi[100]-48);
    prod *= (boi[1000]-48);
    prod *= (boi[10000]-48);
    prod *= (boi[100000]-48);
    prod *= (boi[1000000]-48);
    std::cout << prod << '\n';
    return 0;
}