#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include "math_unsigned.cpp"

int main ()
{
    //Has a text file with Roman numerals, which are correct
    //But not totally compact
    //Find how many characters are saved by making it compact

    std::ifstream inf{"p089_roman.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    return 0;
}