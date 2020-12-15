#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //How many ways can you write 100 as the sum of 2 or more
    //positive integers, order does not matter

    
    //Column represents the total sum of numbers,
    //Row represents the largest number used
    //The way they are added ensures you always add from
    //smallest to largest, so each way is only counted once
    
    //Like the coin problem with values 1-99
    math::Unsigned ways[100][101];
    

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j <= 100; j++)
        {
            ways[i][j] = 0;
        }
    }
    ways[0][0] = 1;
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j <= 100; j++)
        {
            if(i != 0)
            {
                ways[i][j] += ways[i-1][j];
            }
            if(j > i)
            {
                ways[i][j] += ways[i][j-i-1];
            }
        }
    }
    //Subtract 1 because you don't want just 100 by itself
    std::cout << (ways[99][100] - 1) << '\n';
    return 0;
}