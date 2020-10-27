#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Amicable numbers are numbers where the sum of their proper
    //divisors is equal to each other
    //Compute the sum of all such pairs below 10000
    int factors[10000];
    int pairSum{0};
    for(int i{1}; i <= 10000; i++)
    {
        int sum{0};
        for(int j{1}; j <= std::round(std::sqrt(i)); j++)
        {
            if(i % j == 0)
            {
                sum += j;
                //Don't double count squares, or i itself
                if(i/j != j && j != 1)
                {
                    sum += i/j;
                }
            }
        }
        factors[i-1] = sum;
        if(sum <= 10000)
        {
            //Check if they pair together
            if(factors[sum-1] == i && sum != i)
            {
                pairSum += i + sum;
            }
        }
    }
    std::cout << pairSum << '\n';
    return 0;
}