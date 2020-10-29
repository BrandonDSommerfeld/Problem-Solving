#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Place numbers in a square in a spiral from the middle
    // 7 8 9
    // 6 1 2
    // 5 4 3
    //Find the sum of the diagonals in 1001x1001
    long sum{1};
    int num{3};
    //Branch out in each direction from the center
    //The distance between numbers increases by 8 each time
    for(int i{1}; i <= 500; i++)
    {
        sum += num;
        num += 2+8*i;
    }
    num = 5;
    for(int i{1}; i <= 500; i++)
    {
        sum += num;
        num += 4+8*i;
    }
    num = 7;
    for(int i{1}; i <= 500; i++)
    {
        sum += num;
        num += 6+8*i;
    }
    num = 9;
    for(int i{1}; i <= 500; i++)
    {
        sum += num;
        num += 8+8*i;
    }
    std::cout << sum << '\n';
    return 0;
}