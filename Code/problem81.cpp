#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main()
{
    //Has a text file with a matrix

    //Find the path from top left to bottom right with minimum
    //value. Use greedy algorithm from the bottom up
    //Only allowed to move down and right

    std::ifstream inf{"p081_matrix.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    int nums[80][80];

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

    int best[80][80];
    for(int i = 0; i < 80; i++)
    {
        for(int j = 0; j < 80; j++)
        {
            best[i][j] = 0;
        }
    }

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
    std::cout << best[0][0] << '\n';
    return 0;
}