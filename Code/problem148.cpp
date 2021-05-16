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

int powerSeven (int length, int shift)
{
    int ans = 0;
    int divider = 7;
    while(divider <= length)
    {
        ans += length/divider;
        divider *= 7;
    }
    return ans;
}

int main ()
{
    //Find the number of entries which are not divisible by 7 in the first 
    //1 billion rows of Pascal's triangle

    //For a given n, need to choose k to remove all factors of 7 when we do 
    //n! / k! (n-k)!
    // n (n-1) (n-2) .. (n-k+1) / k (k-1) (k-2) (k-3) ... 2 * 1
    //Can't have more powers of 7 in the upper part
    //Calculate power of 7 by taking interval, divide by 7 for first, 
    //then 49 for extra, then 343 for even more

    return 0;
}