#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "math_rational.cpp"
#include "math_fast_rational.cpp"
#include "algorithms.cpp"

int main ()
{
    //How many 20 digit numbers never have any triplet
    //have a sum 10 or greater?
    int limit = 1000;
    //Simply go from left to right, and see how many ways there are 
    //to get each triplet of digits in the current position,
    //By building off of whatever the last triplet was
    unsigned long long* ways = (unsigned long long*) calloc(sizeof(unsigned long long), limit);
    for(int i = 100; i < limit; i++)
    {
        int digitSum = (i % 10) + (i % 100)/10 + i/100;
        if(digitSum < 10)
        {
            ways[i] = 1;
        }
    }
    for(int i = 0; i < 17; i++)
    {
        unsigned long long* next = (unsigned long long*) calloc(sizeof(unsigned long long), limit);
        for(int j = 0; j < limit; j++)
        {
            int digitSum = (j % 100)/10 + (j % 10);
            for(int k = 0; digitSum + k < 10; k++)
            {
                next[(j % 100)*10 + k] += ways[j];
            }
        }
        free(ways);
        ways = next;
    }
    unsigned long long total = 0;
    for(int i = 0; i < limit; i++)
    {
        total += ways[i];
    }
    std::cout << total << '\n';
    free(ways);
    return 0;
}