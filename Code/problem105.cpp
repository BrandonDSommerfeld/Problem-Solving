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

bool works(int *set, int size)
{
    //Initial checks on different sized sets
    if(set[0] + set[1] <= set[size-1])
    {
        return false;
    }
    if(set[0] + set[1] + set[2] <= set[size-2]+set[size-1])
    {
        return false;
    }
    if(set[0]+set[1]+set[2]+set[3] <= set[size-3]+set[size-2]+set[size-1])
    {
        return false;
    }
    if(size >= 9 && set[0]+set[1]+set[2]+set[3]+set[4] <= set[size-4]+set[size-3]+set[size-2]+set[size-1])
    {
        return false;
    }
    if(size >= 11 && set[0]+set[1]+set[2]+set[3]+set[4]+set[5] <= set[size-5]+set[size-4]+set[size-3]+set[size-2]+set[size-1])
    {
        return false;
    }

    //2 element sets
    //For each possible pairing, only the set where we add
    //the largest and smallest element could be equal,
    //because in the others all elements in the second 
    //second are larger than one in the first set
    for(int num1 = 0; num1 < size; num1++)
    {
        for(int num2 = num1+1; num2 < size; num2++)
        {
            for(int num3 = num2+1; num3 < size; num3++)
            {
                for(int num4 = num3+1; num4 < size; num4++)
                {
                    if(set[num1]+set[num4] == set[num2]+set[num3])
                    {
                        return false;
                    }
                }
            }
        }
    }

    //3 element sets
    for(int num1 = 0; num1 < size; num1++)
    {
        for(int num2 = num1+1; num2 < size; num2++)
        {
            for(int num3 = num2+1; num3 < size; num3++)
            {
                for(int num4 = num3+1; num4 < size; num4++)
                {
                    for(int num5 = num4+1; num5 < size; num5++)
                    {
                        for(int num6 = num5+1; num6 < size; num6++)
                        {
                            
                        }
                    }
                }
            }
        }
    }

    
    return true;
}

int main ()
{
    //Problem has a text file, where each line has a set
    //Determine if the set is a special set or not:
    //Special set means any disjoint subsets cannot have the same
    //sum, and if one subset has more elements, it must
    //have a greater sum

    //Find the sum of all elements in the special sets

    std::ifstream inf{"p105_sets.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }

    int total = 0;
    for(std::string in; std::getline(inf, in); )
    {
        int *set = new int[12];
        int used = 0;
        int current = 0;
        for(int loc = 0; loc < in.length(); loc++)
        {
            if(in[loc] != ',')
            {
                current *= 10;
                current += in[loc]-48;
            }
            else
            {
                set[used] = current;
                used++;
                current = 0;
            }
        }
        std::sort(set, set+used);
        if(works(set, used))
        {
            for(int i = 0; i < used; i++)
            {
                total += set[i];
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}