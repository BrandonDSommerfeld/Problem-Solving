#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "algorithms.cpp"

long long evaluate(bool* odd, bool* overflow, int len)
{
    long long total = 1;
    for(int i = 0; i < len; i++)
    {
        if(!odd[i])
        {
            if(i == len-1 || !overflow[i+1])
            {
                return 0;
            }
            if(i < (len+1)/2)
            {
                //Have to account for middle digits and leading 0's
                if(len % 2 == 1 && i == len/2)
                {
                    total *= 5;
                }
                else if(i == 0 && !overflow[i])
                {
                    total *= 20;
                }
                else 
                {
                    total *= 25;
                }                
            }
        }
        else
        {
            if(i != len-1 && overflow[i+1])
            {
                return 0;
            }
            if(i < (len+1)/2)
            {
                if(len % 2 == 1 && i == len/2)
                {
                    return 0;
                }
                if(i == 0 && !overflow[i])
                {
                    total *= 20;
                }
                else if(!overflow[i])
                {
                    total *= 30;
                }
                else
                {
                    total *= 20;
                }
            }
        }
    }

    return total;
}

long long recurse2(bool* odd, bool* overflow, int loc, int len)
{
    if(loc == (len+1)/2)
    {
        return evaluate(odd, overflow, len);
    }
    long long total = 0;
    total += recurse2(odd, overflow, loc+1, len);
    overflow[loc] = true;
    overflow[len-1-loc] = true;
    total += recurse2(odd, overflow, loc+1, len);
    overflow[loc] = false;
    overflow[len-1-loc] = false;
    return total;
}

long long recurse1(bool* odd, bool* overflow, int loc, int len)
{
    //Only go halfway, because sum is mirrored
    if(loc == (len+1)/2)
    {
        return recurse2(odd, overflow, 0, len);
    }
    long long total = 0;
    total += recurse1(odd, overflow, loc+1, len);
    odd[loc] = true;
    odd[len-1-loc] = true;
    total += recurse1(odd, overflow, loc+1, len);
    odd[loc] = false;
    odd[len-1-loc] = false;
    return total;
}

int main ()
{
    //A number is reversible if adding it to its 
    //reverse gives a number with only odd digits
    //Leading 0's are not allowed on the number 
    //or its reverse
    //Find number of reversible numbers below 1 billion
    
    //First digit plus last must be odd for the units 
    //digit to be odd
    //Also means second digit plus second to last cannot overflow, 
    //or else leading digit won't be odd

    //Really, all that matters at each digit is if the 
    //sum is odd or not, and whether it overflows
    //so just check every possible configuration of these
    long long total = 0;
    for(int i = 2; i < 10; i++)
    {
        bool* odd = (bool*) calloc(sizeof(bool), i);
        bool* overflow = (bool*) calloc(sizeof(bool), i);
        total += recurse1(odd, overflow, 0, i);

        std::cout << total << '\n'; 
        free(odd);
        free(overflow);
    }    
    std::cout << total << '\n';
    return 0; 
}