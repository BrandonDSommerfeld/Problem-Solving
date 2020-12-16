#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <bitset>
#include "math_unsigned.cpp"

int main ()
{
    //Find the perimeter p which has the most pythagorean triples
    int* count = new int[1001];
    for(int i = 12; i <= 1000; i++)
    {
        count[i] = 0;
    }
    //Just brute force all combinations of legs
    for(int i{3}; i < 350; i++)
    {
        for(int j{i+1}; j < 500; j++)
        {
            int hypot = std::round(std::sqrt(i*i+j*j));
            if(hypot*hypot == i*i+j*j)
            {
                if(hypot+i+j <= 1000)
                {
                    count[hypot+i+j]++;
                }
            }
        }
    }
    //Find max
    int best{0};
    int loc{0};
    for(int i{12}; i <= 1000; i++)
    {
        if(count[i] > best)
        {
            best = count[i];
            loc = i;
        }
    }
    std::cout << loc << '\n';
    std:: cout << best << '\n';

    return 0;
}