#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int gcd(int num1, int num2)
{
    if(num1 > num2)
    {
        if(num1 % num2 == 0)
        {
            return num2;
        }
        return gcd(num1-num2*(num1/num2), num2);
    }
    if(num2 % num1 == 0)
    {
        return num1;
    }
    return gcd(num2-num1*(num2/num1), num1);
}

int main ()
{
    //How many perimeters P <= 1500000
    //Can only form 1 pythagorean triple

    //Given a reduced proper fraction n/m you can make a primitive triple
    //a = m^2
    //b = 2mn
    //c = m^2 + n^2
    //m and n must be of different even and oddness

    int limit = 1500000;

    int* ways = new int[limit+1];
    for(int i = 0; i <= limit; i++)
    {
        ways[i] = 0;
    }

    for(int m = 2; m < 1000; m++)
    {
        for(int n = 1; n < m; n++)
        {
            if((m+n)%2 == 1 && gcd(m,n) == 1)
            {
                int a = m*m-n*n;
                int b = 2*m*n;
                int c = m*m+n*n;
                int p = a+b+c;
                for(int k = 1; p*k <= limit; k++)
                {
                    ways[p*k]++;
                }
            }
        }
    }
    int num = 0;
    for(int i = 12; i <= limit; i++)
    {
        if(ways[i] == 1)
        {
            num++;
        }
    }
    std::cout << num << '\n';
    return 0;
}