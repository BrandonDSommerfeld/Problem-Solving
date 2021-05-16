#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include <list>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "algorithms.cpp"

long long numWays (int rows, int cols)
{
    long long total = 0;

    //Add in the rows and cols formed by the intersection 
    //of the x's
    rows = rows*2+1;
    cols = cols*2+1;

    for(int row = 0; row < rows; row++)
    {
        //If we are on an even row, no diagonals so only even cols exist, 
        //only odd cols in odd rows
        for(int col = row % 2 == 0 ? 0 : 1; col < cols; col += 2)
        {
            if(row % 2 == 0)
            {
                //Non-diagonal rectangles
                total += (rows-row-1)*(cols-col-1)/4;
            }
            for(int bottom = row+2; bottom < rows; bottom++)
            {
                //Do the diagonal rectangles
                //Figure out the furthest left you can go, 
                //which is all but 1 move left, and then last one right 
                //However, have the if statement if we hit 
                //the edge before then 
                //Do the same for rightmost, and if 
                //there are any possible rectangles, add them in
                int left = (col - bottom+row + 2);
                if(col < bottom-row-1)
                {
                    left = bottom-row-col;
                }
                int right = (col + bottom-row - 2);
                if(col > cols - bottom+row)
                {
                    right = 2*cols-2-bottom+row-col; 
                }

                if(right >= left)
                {
                    total += (right-left+2)/2;
                }
            }
        }
    }
    return total;
}

int main ()
{
    //Consider a rectangle that is m x n, with gridlines going through it.
    //Then within each square, also draw an X in it
    //Consider how many smaller rectangles can be formed, including the 
    //entire rectangle, and also diagonal ones using the intersection of the X
    //Sum this up over all m x n rectangles, m <= 47, n <= 43, and we 
    //consider m x n to be different than n x m

    long long total = 0;

    for(int i = 1; i <= 47; i++)
    {
        for(int j = 1; j <= 43; j++)
        {
            total += numWays(i,j);
        }
    }
    std::cout << total << '\n';
    return 0;
}