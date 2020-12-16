#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main()
{
    //Problem 67 has a text file with a triangle
    //Find the maximum path from top to bottom

    //Just use a greedy algorithm from the top up: You always
    //choose the most points from the 2 options

    std::ifstream inf{"p067_triangle.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    int nums[100][100];

    for(int i = 0; i < 100; i++)
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
    
    int* best = new int[100];
    for(int i = 0; i < 100; i++)
    {
        best[i] = nums[99][i];
    }

    for(int i = 99; i > 0; i--)
    {
        int* temp = new int[i];
        for(int j = 0; j < i; j++)
        {
            if(best[j] > best[j+1])
            {
                temp[j] = nums[i-1][j]+best[j];
            }
            else
            {
                temp[j] = nums[i-1][j]+best[j+1];
            }
        }
        best = temp;
    }
    std::cout << best[0] << '\n';
    return 0;
}