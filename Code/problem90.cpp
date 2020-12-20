#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include "math_unsigned.cpp"

std::vector<std::vector<int>> subsets ()
{
    std::vector<std::vector<int>> *res = new std::vector<std::vector<int>>{};
    for(int i = 0; i < 10; i++)
    {
        for(int j = i+1; j < 10; j++)
        {
            for(int k = j+1; k < 10; k++)
            {
                for(int m = k+1; m < 10; m++)
                {
                            
                    std::vector<int> *temp = new std::vector<int>{};
                    for(int a = 0; a < 10; a++)
                    {
                        if(a != i && a != j && 
                        a != k && a != m)
                        {
                            temp->push_back(a);
                        }
                    }
                    res->push_back(*temp);
                }
            }
        }
    }


    return *res;
}

bool contains(std::vector<int> set, int element)
{
    for(int i = 0; i < set.size(); i++)
    {
        if(set[i] == element)
        {
            return true;
        }
    }
    return false;
}


bool works(std::vector<int> set1, std::vector<int> set2)
{
    if(!((contains(set1, 0) && contains(set2, 1))
    || (contains(set1, 1) && contains(set2, 0))))
    {
        return false;
    }

    if(!((contains(set1, 0) && contains(set2, 4))
    || (contains(set1, 4) && contains(set2, 0))))
    {
        return false;
    }

    if(!((contains(set1, 0) && (contains(set2, 6) || contains(set2, 9)))
    || ((contains(set1, 6) || contains(set1, 9)) && contains(set2, 0))))
    {
        return false;
    }

    if(!((contains(set1, 1) && (contains(set2, 6) || contains(set2, 9)))
    || ((contains(set1, 6) || contains(set1, 9)) && contains(set2, 1))))
    {
        return false;
    }

    if(!((contains(set1, 2) && contains(set2, 5))
    || (contains(set1, 5) && contains(set2, 2))))
    {
        return false;
    }

    if(!((contains(set1, 3) && (contains(set2, 6) || contains(set2, 9)))
    || ((contains(set1, 6) || contains(set1, 9)) && contains(set2, 3))))
    {
        return false;
    }

    if(!((contains(set1, 4) && (contains(set2, 6) || contains(set2, 9)))
    || ((contains(set1, 6) || contains(set1, 9)) && contains(set2, 4))))
    {
        return false;
    }

    if(!((contains(set1, 4) && (contains(set2, 6) || contains(set2, 9)))
    || ((contains(set1, 6) || contains(set1, 9)) && contains(set2, 4))))
    {
        return false;
    }

    if(!((contains(set1, 8) && contains(set2, 1))
    || (contains(set1, 1) && contains(set2, 8))))
    {
        return false;
    }
    return true;
}

int main ()
{
    //There are 2 cubes, where each side has a digit on it
    //If you can flip a 6 to a 9 and vice versa
    //How many configurations let you create all 2 digit square numbers
    //padding 01, 04, 09

    std::vector<std::vector<int>> sets = subsets();

    //Most of the work is in the functions,
    //Where I generate all subsets by iterating
    //over the 4 elements not in the set, and then I just
    //test if I can make all 9 squares from the sets
    int total = 0;
    for(int i = 0; i < sets.size(); i++)
    {
        for(int j = i; j < sets.size(); j++)
        {
            if(works(sets[i], sets[j]))
            {
                total++;
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}