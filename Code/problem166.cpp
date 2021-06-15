#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include "math_unsigned.h"
#include "math_signed.h"
#include "math_rational.h"
#include "math_fast_rational.h"
#include "algorithms.h"

int main ()
{
    //How many 4x4 grids with numbers 0-9 have all rows, columns, 
    //and both diagonals with the same sum?

    /*
    1's are squares we iterate over, and the 2's are 
    determined by the values of the 1's
    1 1 1 2
    1 1 2 2
    1 1 1 2
    2 2 2 2
    */
    //Set up 8 equations, solve for the 2's in terms of the 1's
    //Then iterate over all ways to set the 1's

    //Where in the left/right matrices each variable appears
    int* loc = new int[16]{};
    loc[1] = 1;
    loc[2] = 2;
    loc[4] = 3;
    loc[5] = 4;
    loc[6] = 1;
    loc[7] = 2;
    loc[8] = 5;
    loc[9] = 6;
    loc[10] = 7;
    loc[11] = 3;
    loc[12] = 4;
    loc[13] = 5;
    loc[14] = 6;
    loc[15] = 7;

    math::FastRational** leftMatrix = new math::FastRational*[8];
    math::FastRational** rightMatrix = new math::FastRational*[8];
    for(int i = 0; i < 10; i++)
    {
        leftMatrix[i] = new math::FastRational[8]{};
        rightMatrix[i] = new math::FastRational[8]{};
    }
    //Comments are abrieviated, 0 for the 0th number
    //0+1+2+3 = 4+5+6+7
    //0+1+2-4-5 = -3+6+7
    leftMatrix[0][loc[0]] = 1;
    leftMatrix[0][loc[1]] = 1;
    leftMatrix[0][loc[2]] = 1;
    leftMatrix[0][loc[4]] = -1;
    leftMatrix[0][loc[5]] = -1;
    rightMatrix[0][loc[3]] = -1;
    rightMatrix[0][loc[6]] = 1;
    rightMatrix[0][loc[7]] = 1;
    //0+1+2+3 = 8+9+10+11
    //0+1+2-8-9-10 = -3+11
    leftMatrix[1][loc[0]] = 1;
    leftMatrix[1][loc[1]] = 1;
    leftMatrix[1][loc[2]] = 1;
    leftMatrix[1][loc[8]] = -1;
    leftMatrix[1][loc[9]] = -1;
    leftMatrix[1][loc[10]] = -1;
    rightMatrix[1][loc[3]] = -1;
    rightMatrix[1][loc[11]] = 1;
    //0+1+2+3 = 12+13+14+15
    //0+1+2 = -3+12+13+14+15
    leftMatrix[2][loc[0]] = 1;
    leftMatrix[2][loc[1]] = 1;
    leftMatrix[2][loc[2]] = 1;
    rightMatrix[2][loc[3]] = -1;
    rightMatrix[2][loc[12]] = 1;
    rightMatrix[2][loc[13]] = 1;
    rightMatrix[2][loc[14]] = 1;
    rightMatrix[2][loc[15]] = 1;
    //0+1+2+3 = 0+4+8+12
    //1+2-4-8= -3+12
    leftMatrix[3][loc[1]] = 1;
    leftMatrix[3][loc[2]] = 1;
    leftMatrix[3][loc[4]] = -1;
    leftMatrix[3][loc[8]] = -1;
    rightMatrix[3][loc[3]] = -1;
    rightMatrix[3][loc[12]] = 1;
    //0+1+2+3 = 1+5+9+13
    //0+2-5-9 = -3+13
    leftMatrix[4][loc[0]] = 1;
    leftMatrix[4][loc[2]] = 1;
    leftMatrix[4][loc[5]] = -1;
    leftMatrix[4][loc[9]] = -1;
    rightMatrix[4][loc[3]] = -1;
    rightMatrix[4][loc[13]] = 1;
    //0+1+2+3 = 2+6+10+14
    //0+1-10 = -3+6+14
    leftMatrix[5][loc[0]] = 1;
    leftMatrix[5][loc[1]] = 1;
    leftMatrix[5][loc[10]] = -1;
    rightMatrix[5][loc[6]] = 1;
    rightMatrix[5][loc[3]] = -1;
    rightMatrix[5][loc[14]] = 1;
    //0+1+2+3 = 3+7+11+15
    //0+1+2 = 7+11+15
    leftMatrix[6][loc[0]] = 1;
    leftMatrix[6][loc[1]] = 1;
    leftMatrix[6][loc[2]] = 1;
    rightMatrix[6][loc[7]] = 1;
    rightMatrix[6][loc[11]] = 1;
    rightMatrix[6][loc[15]] = 1;
    //0+1+2+3 = 0+5+10+15
    //1+2-5-10 = -3+15
    leftMatrix[7][loc[1]] = 1;
    leftMatrix[7][loc[2]] = 1;
    leftMatrix[7][loc[5]] = -1;
    leftMatrix[7][loc[10]] = -1;
    rightMatrix[7][loc[3]] = -1;
    rightMatrix[7][loc[15]] = 1;

    math::FastRational** inv1 = algorithms::matrixInverse(rightMatrix, 8);
    
    //0+1+2+3 = 3+6+9+12
    //0+1+2-9 = 6+12
    leftMatrix[7][loc[0]] = 1;
    leftMatrix[7][loc[1]] = 1;
    leftMatrix[7][loc[2]] = 1;
    leftMatrix[7][loc[9]] = -1;
    rightMatrix[7][loc[6]] = 1;
    rightMatrix[7][loc[12]] = 1;

    //Probably include both diagonals, rotate the row/col of all 2's?

    math::FastRational** inv2 = algorithms::matrixInverse(rightMatrix, 8);

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            std::cout << inv1[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            std::cout << inv2[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}