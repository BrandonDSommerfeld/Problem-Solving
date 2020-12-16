#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Compute the millionth permutation of 0123456789
    //Loop on the 9th digit to the 0th
    std::string answer{};
    int remaining{1000000};
    bool used[10];
    for(int i{0}; i < 10; i++)
    {
        used[i] = false;
    }
    for(int i{9}; i >= 0; i--)
    {
        int factorial{1};
        for(int j{2}; j <= i; j++)
        {
            factorial *= j;
        }
        int digit{0};
        //Factorial represents permutations of further digits
        //Go to next digit if we need more permutations
        while(remaining > factorial)
        {
            remaining -= factorial;
            digit++;
        }
        int found{0};
        for(int j{0}; j < 10; j++)
        {
            if(!used[j])
            {
                found++;
                if(found == digit+1)
                {
                    answer += std::to_string(j);
                    used[j] = true;
                }
            }
        }
    }
    std::cout << answer << '\n';
    return 0;
}