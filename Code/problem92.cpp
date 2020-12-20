#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include "math_unsigned.cpp"

static int *works;

int digitSum(int num)
{
    int sum = 0;
    while(num > 0)
    {
        sum += (num%10)*(num%10);
        num /= 10;
    }
    return sum;
}

bool end89(int num)
{
    int original = num;
    while(true)
    {
        num = digitSum(num);
        if(works[num] == 1)
        {
            works[original] = 1;
            return false;
        }
        if(works[num] == 2)
        {
            works[original] = 2;
            return true;
        }
    }
    return false;
}

int main ()
{
    //If you take numbers, square their digits and take that sum,
    //all numbers eventually arrive at 1 or 89
    //How many below 10 million arrive at 89

    works = new int[10000000];
    for(int i = 0; i < 10000000; i++)
    {
        works[i] = 0;
    }
    works[1] = 1;
    works[89] = 2;
    int total = 0;
    for(int i = 1; i < 10000000; i++)
    {
        if(end89(i))
        {
            total++;
        }
    }
    std::cout << total << '\n';
    return 0;
}