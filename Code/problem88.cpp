#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include "math_unsigned.cpp"

int main ()
{
    //For every number from 2 to 12000 inclusive, find the smallest
    //number which is the sum of a set of k numbers, and
    //also the product of those numbers

    //Since you can pad with 1's, there is an upper bound of 2k
    //by doing 2, k, and a lot of 1's
   

    static constexpr int limit = 24000;
    std::vector<std::vector<int>> ways[limit+1];
    for(int i = 1; i <= limit; i++)
    {
        std::vector<int> *temp = new std::vector<int>{};
        temp->push_back(i);
        temp->push_back(1);
        ways[i].push_back(*temp);
    }

    //For each number, find the ways it can be written as a 
    //product from previous nums, and the pair is
    //sum total, then number of terms used
    for(int i = 4; i <= limit; i++)
    {
        for(int j = 2; j <= std::sqrt(i); j++)
        {
            if(i % j == 0)
            {
                int pair = i/j;
                for(int k = 0; k < ways[pair].size(); k++)
                {
                    std::vector<int> *temp = new std::vector<int>{};
                    temp->push_back(ways[pair][k][0]+j);
                    temp->push_back(ways[pair][k][1]+1);
                    ways[i].push_back(*temp);
                }
            }
        }
    }


    bool used[limit+1];
    bool minFound[limit/2+1];
    for(int i = 0; i <= limit; i++)
    {
        used[i] = false;
        minFound[i/2] = false;
    }
    minFound[0] = true;
    minFound[1] = true;

    //For every number, see how many 1's are needed to pad the
    //sum to be correct, and see if that number of terms
    //has been used before
    for(int i = 4; i <= limit; i++)
    {
        for(int j = 0; j < ways[i].size(); j++)
        {
            std::vector<int> pair = ways[i][j];
            int extra1s = (i-pair[0]);
            
            if(extra1s >= 0 && pair[1] + extra1s <= limit/2)
            {
                if(!minFound[pair[1]+extra1s])
                {
                    minFound[pair[1]+extra1s] = true;
                    used[i] = true;
                }
            }
        }
    }

    int total = 0;
    for(int i = 0; i <= limit; i++)
    {
        if(used[i])
        {
            total += i;
        }
    }
    std::cout << total << '\n';
    return 0;
}