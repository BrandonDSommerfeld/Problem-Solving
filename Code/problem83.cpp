#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include "math_unsigned.cpp"


int main()
{
    //Has a text file with a matrix

    //Find minimum path from top left to bottom right, allowed
    //to move in any direction

    std::ifstream inf{"p083_matrix.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    auto nums = new long long[80][80];

    for(int i = 0; i < 80; i++)
    {
        std::string in{};
        std::getline(inf, in);
        int current = 0;
        int used = 0;
        for(int j = 0; j < in.length(); j++)
        {
            if(48 <= in[j] && in[j] <= 57)
            {
                current *= 10;
                current += in[j]-48;
            }
            else
            {
                nums[i][used] = current;
                current = 0;
                used++;
            }
        }
        nums[i][used] = current;
    }

    long long best[80][80];
    for(int i = 0; i < 80; i++)
    {
        for(int j = 0; j < 80; j++)
        {
            best[i][j] = 0;
        }
    }

    //Copied from problem 81, finds ideal distances
    //If only moving right and down
    for(int i = 79; i >= 0; i--)
    {
        for(int j = 79; j >= 0; j--)
        {
            if(i == 79 && j == 79)
            {
                best[i][j] = nums[i][j];
            }
            else if (i == 79)
            {
                best[i][j] = nums[i][j] + best[i][j+1];
            }
            else if (j == 79)
            {
                best[i][j] = nums[i][j] + best[i+1][j];
            }
            else
            {
                if(best[i+1][j] < best[i][j+1])
                {
                    best[i][j] = nums[i][j] + best[i+1][j];
                }
                else
                {
                    best[i][j] = nums[i][j] + best[i][j+1];
                }
                
            }
            
        }
    }

    //Basically run djikstra's while considering
    //Adjacent entries as connected with a weight
    //But compute total distance to just the bottom right
    bool changed = true;
    while(changed)
    {
        changed = false;
        //Add in up moves
        for(int i = 1; i < 80; i++)
        {
            for(int j = 0; j < 80; j++)
            {
                if(best[i-1][j] + nums[i][j] < best[i][j])
                {
                    best[i][j] = best[i-1][j] + nums[i][j];
                    changed = true;
                }
            }
        }
        //Add in left moves
        for(int j = 1; j < 80; j++)
        {
            for(int i = 0; i < 80; i++)
            {
                if(best[i][j-1] + nums[i][j] < best[i][j])
                {
                    best[i][j] = best[i][j-1] + nums[i][j];
                    changed = true;
                }
            }
        }
        //Add in down moves
        for(int i = 78; i >= 0; i--)
        {
            for(int j = 0; j < 80; j++)
            {
                if(best[i+1][j] + nums[i][j] < best[i][j])
                {
                    best[i][j] = best[i+1][j] + nums[i][j];
                    changed = true;
                }
            }
        }
        //Add in right moves
        for(int j = 78; j >= 0; j--)
        {
            for(int i = 0; i < 80; i++)
            {
                if(best[i][j+1] + nums[i][j] < best[i][j])
                {
                    best[i][j] = best[i][j+1] + nums[i][j];
                    changed = true;
                }
            }
        }
    }
    
    std::cout << best[0][0] << '\n';
    return 0;
}