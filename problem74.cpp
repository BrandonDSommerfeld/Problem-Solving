#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

static int* factorials;

int factSum(int num)
{
    int sum = 0;
    while(num > 0)
    {
        sum += factorials[num%10];
        num /= 10;
    }
    return sum;
}

int chainLength(int num)
{
    if(num == 169 || num == 363601 || num == 1454)
    {
        return 3;
    }
    if(num == 871 || num == 872 ||
    num == 45361 || num == 45362)
    {
        return 2;
    }
    if(num == factSum(num))
    {
        return 1;
    }
    return 1+chainLength(factSum(num));
}

int main ()
{
    //Given a number, you can compute the sum of the factorials
    //of each digit, and then repeat
    //145, 169, 871, 872 all get stuck in loops
    //And all other numbers eventually get to one of them
    //Find how many numbers below 1000000 have 60 non-repeating terms

    factorials = new int[10];
    factorials[0] = 1;
    for(int i = 1; i < 10; i++)
    {
        factorials[i] = factorials[i-1]*i;
    }

    //Just use the nice recursive function above to brute force
    int num = 0;
    for(int i = 1; i < 1000000 ; i++)
    {
        if(chainLength(i) == 60)
        {
            num++;
        }
    }
    std::cout << num << '\n';
    return 0;
}