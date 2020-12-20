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

    //Just turn IIII into IV and
    //VIIII into IX, and same for larger denominations
    int total = 0;
    for(int i = 0; i < 1000; i++)
    {
        std::string in{};
        std::getline(inf, in);

        int count = 0;
        char prev = '\0';
        for(int j = 0; j < in.length(); j++)
        {
            if(in[j] == prev)
            {
                count++;
                if(count == 4)
                {
                    if(in[j] == 'C')
                    {
                        if(j == 3 || in[j-4] != 'D')
                        {
                            total += 2;
                        }
                        else
                        {
                            total += 3;
                        }
                    }
                    if(in[j] == 'X')
                    {
                        if(j == 3 || in[j-4] != 'L')
                        {
                            total += 2;
                        }
                        else
                        {
                            total += 3;
                        }
                    }
                    if(in[j] == 'I')
                    {
                        if(j == 3 || in[j-4] != 'V')
                        {
                            total += 2;
                        }
                        else
                        {
                            total += 3;
                        }
                    }
                }
            }
            else
            {
                prev = in[j];
                count = 1;
            }
            
        }
    }
    std::cout << total << '\n';
    return 0;
}