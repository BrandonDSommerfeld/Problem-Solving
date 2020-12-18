#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
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
    //Consider rectangular prisms, and the shortest
    //path from one vertex to the further one along the 
    //surface. Occasionally this is an integer, and this 
    //problem is finding the least n such that there are
    //at least 1 million such integer shortest paths
    //on prisms where every side is n or less

    //Consider the longest side. If you move x along this side
    //on one face, then you move s1-x on the other face
    //This gives total length

    //Sqrt(x^2+b^2) + sqrt((a-x)^2 + c^2)
    //This is minimized when x = ab/b+c
    //Which gives minimum distance
    //sqrt(a^2 + (b+c)^2)
    //Thus, this problem is just looking for pythagorean triples
    //Which we already have code for

    static constexpr int limit = 10000;
    int *num = new int[limit];
    for(int i = 0; i < limit; i++)
    {
        num[i] = 0;
    }

    for(int m = 2; m < 1000; m++)
    {
        for(int n = 1; n < m; n++)
        {
            if((m+n)%2 == 1 && gcd(m,n) == 1)
            {
                int a = m*m-n*n;
                int b = 2*m*n;
                for(int k = 1; a*k < limit; k++)
                {
                    //a is big enough to be greatest side
                    if(2*a*k > b*k)
                    {
                        //Check if we can divide b any way,
                        //or if we need both parts below a
                        if(a < b)
                        {
                            num[a*k] += (2*a*k-b*k+2)/2;
                        }
                        else
                        {
                            num[a*k] += (b*k)/2;
                        }
                    }
                    //b is big enough to be largest
                    if(2*b*k > a*k && b*k < limit)
                    {
                        if(b*k < a*k)
                        {
                            num[b*k] += (2*b*k-a*k+2)/2;
                        }
                        else
                        {
                            num[b*k] += (a*k)/2;
                        }
                        
                    }
                }
            }
        }
    }
    int total = 0;
    for(int i = 0; i < limit; i++)
    {
        total += num[i];
        if(total > 1000000)
        {
            std::cout << i << '\n';
            return 0;
        }
    }
    std::cout << "Finished\n";
    return 0;
}