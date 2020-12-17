#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main()
{
    //Has a text file with a matrix

    //Find minimum path from anywhere on the left to anywhere on 
    //the right, allowed to move right, up and down

    std::ifstream inf{"p082_matrix.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    long long nums[80][80];

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

    for(int j = 79; j >= 0; j--)
    {
        //Initial setup for col, just moving directly right
        for(int i = 0; i < 80; i++)
        {
            if(j != 79)
            {
                best[i][j] = nums[i][j] + best[i][j+1];
            }
            else
            {
                best[i][j] = nums[i][j];
            }
            
        }
        //Going down the rows, only consider moving up
        for(int i = 1; i < 80; i++)
        {
            if(best[i-1][j] + nums[i][j] < best[i][j])
            {
                best[i][j] = best[i-1][j] + nums[i][j];
            }
        }
        //Moving down
        for(int i = 78; i >= 0; i--)
        {
            if(best[i+1][j] + nums[i][j] < best[i][j])
            {
                best[i][j] = best[i+1][j] + nums[i][j];
            }
        }
    }
    int b = 1000000;
    for(int i = 0; i < 80; i++)
    {
        if(best[i][0] < b)
        {
            b = best[i][0];
        }
    }
    std::cout << b << '\n';
    return 0;
}