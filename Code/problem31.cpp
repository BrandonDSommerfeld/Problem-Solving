#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //There are coins worth 1, 2, 5, 10, 20, 50, 100, 200
    //How many ways can you make 200, order does not matter
    int ways[8][201];
    for(int i{0}; i < 8; i++)
    {
        ways[i][0] = 1;
        for(int j{1}; j <= 200; j++)
        {
            ways[i][j] = 0;
        }
    }
    int values[8];
    values[0] = 1;
    values[1] = 2;
    values[2] = 5;
    values[3] = 10;
    values[4] = 20;
    values[5] = 50;
    values[6] = 100;
    values[7] = 200;
    //Array calculates all ways to make values with just lowest coin
    //Then all ways if the next lowest is allowed
    //And so on
    for(int i{0}; i < 8; i++)
    {
        for(int j{1}; j <= 200; j++)
        {
            if(j-values[i] < 0 && i > 0)
            {
                ways[i][j] = ways[i-1][j];
            }
            else if(i > 0)
            {
                ways[i][j] = ways[i][j-values[i]] + ways[i-1][j];            }
            else
            {
                ways[i][j] = ways[i][j-values[i]];
            }
            
        }
    }
    std::cout << ways[7][200] << '\n';
    return 0;
}