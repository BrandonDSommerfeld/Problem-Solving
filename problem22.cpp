#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //We have text file p022_names.txt
    //Need to compute "name score" of each name
    //Given by A=1 to Z=26, sum the letters
    //Then multiply by 1 indexed position in list when sorted
    std::ifstream inf{"p022_names.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    std::string input{};
    std::getline(inf, input);
    std::string names[6000];
    std::string name{};
    bool started{false};
    int place{0};
    //Reading names into string array
    for(int i{0}; i < input.length(); i++)
    {
        if(input[i] == '"')
        {
            if(started)
            {
                started = false;
                names[place] = name;
                place++;
            }
            else
            {
                started = true;
                name = "";
            }
        }
        else if (started)
        {
            name += input[i];
        }
    }
    std::sort(names, names+place);
    long sum{0};
    //Standard loop and sum on ASCII values
    for(int i{0}; i < place; i++)
    {
        int smallSum{0};
        for(int j{0}; j < names[i].length(); j++)
        {
            smallSum += (names[i][j] - 64);
        }
        sum += smallSum*(i+1);
    }
    std::cout << sum << '\n';
    return 0;
}