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

int main ()
{
    //Problem has a text file, where each line contains a base
    //and then an exponent
    //Determine which line number has greatest value a^b

    std::ifstream inf{"p099_base_exp.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    double highest = 0;
    int loc = 0;
    int i = 1;
    //Convert all values into base e by doing
    //a^b = (e^ln(a))^b = e^(b*ln(a))
    //Then you just find largest exponent
    for(std::string in; std::getline(inf, in); )
    {
        int space = in.find(',');
        int base = std::stoi(in.substr(0, space));
        int exp = std::stoi(in.substr(space+1,in.length()-space));

        double val = std::log(base) * exp;
        if(val > highest)
        {
            highest = val;
            loc = i;
        }
        i++;
    }
    std::cout << highest << '\n';
    std::cout << loc << '\n';
    return 0;
}