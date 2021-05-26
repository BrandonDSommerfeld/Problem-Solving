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
#include "algorithms.cpp"


static std::vector<std::vector<int*>> overflow5{};

bool works_base2(unsigned long long num1, unsigned long long num2, unsigned long long num3)
{
    //Count how much overflow occurs in base 2, 
    //and only return true if it is at least 12
    unsigned long long total_overflow = 0;
    unsigned long long last_overflow = 0;
    for(int i = 0; i < 18; i++)
    {
        unsigned long long curr = ((num1 >> i) & 1) + 
        ((num2 >> i) & 1) + 
        ((num3 >> i) & 1) + last_overflow;
        total_overflow += curr/2;
        last_overflow = curr/2;
    }
    return total_overflow >= 12;
}

unsigned long long calculate (const std::string& num, int loc, int last_overflow, 
int total_overflow, unsigned long long pow, unsigned long long num1, 
unsigned long long num2, unsigned long long num3)
{
    //Examine the current digit, see what we want to add to get, accounting 
    //for overflow from last addition
    int goal = static_cast<int>(num[loc])- 48 - last_overflow;
    unsigned long long total = 0;
    //If at the front, we can't allow any overflow to occur
    if(loc == 0)
    {   
        for(size_t i = 0; i < overflow5[goal].size(); i++)
        {
            if(works_base2(overflow5[goal][i][0]*pow + num1, 
            overflow5[goal][i][1]*pow + num2, 
            overflow5[goal][i][2]*pow + num3))
            {
                total++;
            }
        }
        return total;
    }
    //Early termination: only try if doing the maximum of 2 
    //overflows on each further digit will give the overflow of 12 needed
    int next_overflow = total_overflow + 2*(loc-1);
    //No overflow case
    if(next_overflow >= 12 && goal >= 0)
    {
        for(size_t i = 0; i < overflow5[goal].size(); i++)
        {
            total += calculate(num, loc-1, 0, total_overflow, pow*5, 
            overflow5[goal][i][0]*pow + num1,
            overflow5[goal][i][1]*pow + num2,
            overflow5[goal][i][2]*pow + num3);
        }
    }
    //1 overflow
    if(next_overflow >= 11)
    {
        for(size_t i = 0; i < overflow5[goal+5].size(); i++)
        {
            total += calculate(num, loc-1, 1, total_overflow+1, pow*5, 
            overflow5[goal+5][i][0]*pow + num1,
            overflow5[goal+5][i][1]*pow + num2,
            overflow5[goal+5][i][2]*pow + num3);
        }
    }
    //Overflow of 2, like 4+3+3 mod 5
    if(next_overflow >= 10)
    {
       for(size_t i = 0; i < overflow5[goal+10].size(); i++)
        {
            total += calculate(num, loc-1, 2, total_overflow+2, pow*5, 
            overflow5[goal+10][i][0]*pow + num1,
            overflow5[goal+10][i][1]*pow + num2,
            overflow5[goal+10][i][2]*pow + num3);
        }
    }
    return total;
}

int main ()
{
    //For Pascal's pyramid, which gives coefficients of 
    //(x+y+z)^n, find how many coefficients in 
    //(x+y+z)^200,000 are multiples of 10^12
    //Highly connected to problem 148, look there for reasoning
    //about why we care about overflow base 2 and base 5

    //Takes a little bit to run, not too bad but answer is 
    //479742450
    
    //Pre-calculate all ways to sum to get a certain digit 
    //in a position, with overflow allowed
    for(int i = 0; i < 15; i++)
    {
        std::vector<int*>* temp{new std::vector<int*>};
        overflow5.push_back(*temp);
    }

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            for(int k = 0; k < 5; k++)
            {
                int* temp{new int[3]};
                temp[0] = i;
                temp[1] = j;
                temp[2] = k;
                overflow5[i+j+k].push_back(temp);
            }
        }
    }

    //200,000 is
    //22400000 base 5
    std::string base5 = "22400000";
    std::cout << calculate(base5, base5.length()-1, 0, 0, 1, 0, 0, 0) << '\n';
    
    return 0;
}