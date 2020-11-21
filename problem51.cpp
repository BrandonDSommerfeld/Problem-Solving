#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

static bool* composite;

int recurse (const std::string& num, int position)
{
    if(position == num.length())
    {
        //If there are no numbers to replace, can't do it
        if(std::find(num.begin(), num.end(), 'a') == num.end())
            return 0;
        int found{0};
        //Go through, replacing all selected indices with numbers
        int start {0};
        //Can't start a number with 0
        if(num[0] == 'a')
        {
            start = 1;
        }
        for(int i{start}; i < 10; i++)
        {
            std::string copy{num};
            //Replace all a's with the current number
            for(int j{0}; j < position; j++)
            {
                if(copy[j] == 'a')
                {
                    copy[j] = std::to_string(i)[0];
                }
            }
            if(!composite[std::stoi(copy)])
            {
                found++;
            }
        }
        if(found == 8)
        {
            std::cout << num << '\n';
        }
        return found;
    }

    //Recursively makes all possible selections, either the
    //Positiion is selected with an 'a' or it isn't
    std::string copy{num};
    copy[position] = 'a';
    int num1 {recurse(num, position+1)};
    int num2 {recurse(copy, position+1)};
    if(num1 > num2)
        return num1;
    return num2;
}

int main ()
{
    //Find the smallest prime, say, of the form
    // 5**33 Where the stars are replaced by the same value
    //where 8 of the 10 replacements are prime
    //The stars can be any subset of the number though

    composite = new bool[1000000];
    for(int i{2}; i < 1000; i++)
    {
        if(!composite[i])
        {
            for(int j{2}; i*j < 1000000; j++)
            {
                composite[i*j] = true;
            }
        }
    }

    for(int i{101}; i < 1000000; i += 2)
    {
        if(!composite[i])
        {
            if(recurse(std::to_string(i), 0) == 8)
            {
                return 0;
            }
        }
    }

    //Smallest one gets printed in recursive, with a's in the
    //Locations in question

    return 0;
}