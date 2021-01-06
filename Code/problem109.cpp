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

int main ()
{
    //How many ways can you checkout from darts with a score
    //Of 100 or less
    //There are 1-20, with double and triple,
    //Then bullseye is 25 or 50 doubled only
    //To checkout, you must get exactly 0 and end with a double

    int ways[1000];
    for(int i = 0; i < 200; i++)
    {
        ways[i] = 0;
    }

    for(int d = 1; d <= 20; d++)
    {
        ways[2*d]++;
    }
    ways[50]++;

    for(int d1 = 1; d1 <= 20; d1++)
    {
        for(int d2 = 1; d2 <= 20; d2++)
        {
            ways[d1+2*d2]++;
            ways[2*d1+2*d2]++;
            ways[3*d1+2*d2]++;
        }
        ways[d1+50]++;
        ways[2*d1+50]++;
        ways[3*d1+50]++;
    }
    for(int d2 = 1; d2 <= 20; d2++)
    {
        ways[25+2*d2]++;
        ways[50+2*d2]++;
    }
    ways[75]++;
    ways[100]++;


    for(int d1 = 1; d1 <= 20; d1++)
    {
        for(int d2 = d1; d2 <= 20; d2++)
        {
            for(int d3 = 1; d3 <= 20; d3++)
            {
                ways[d1+d2+2*d3]++;
                ways[d1+2*d2+2*d3]++;
                ways[d1+3*d2+2*d3]++;
                ways[2*d1+2*d2+2*d3]++;
                ways[2*d1+3*d2+2*d3]++;
                ways[3*d1+3*d2+2*d3]++;
                if(d1 != d2)
                {
                    ways[3*d1+2*d2+2*d3]++;
                    ways[3*d1+d2+2*d3]++;
                    ways[2*d1+d2+2*d3]++;
                }
            }
            ways[d1+d2+50]++;
            ways[d1+2*d2+50]++;
            ways[d1+3*d2+50]++;
            ways[2*d1+2*d2+50]++;
            ways[2*d1+3*d2+50]++;
            ways[3*d1+3*d2+50]++;
            if(d1 != d2)
            {
                ways[3*d1+2*d2+50]++;
                ways[3*d1+d2+50]++;
                ways[2*d1+d2+50]++;
            }
        }
        for(int d3 = 1; d3 <= 20; d3++)
        {
            ways[d1+25+2*d3]++;
            ways[2*d1+25+2*d3]++;
            ways[3*d1+25+2*d3]++;
            ways[d1+50+2*d3]++;
            ways[2*d1+50+2*d3]++;
            ways[3*d1+50+2*d3]++;
        }
        ways[d1+25+50]++;
        ways[2*d1+25+50]++;
        ways[3*d1+25+50]++;
        ways[d1+50+50]++;
        ways[2*d1+50+50]++;
        ways[3*d1+50+50]++;
    }

    for(int d3 = 1; d3 <= 20; d3++)
    {
        ways[25+25+2*d3]++;
        ways[50+50+2*d3]++;
        ways[50+25+2*d3]++;
    }
    ways[25+25+50]++;
    ways[25+50+50]++;
    ways[50+50+50]++;

    int total = 0;
    for(int i = 0; i < 100; i++)
    {
        total += ways[i];
    }
    std::cout << total << '\n';
    return 0;
}