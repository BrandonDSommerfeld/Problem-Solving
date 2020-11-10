#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int wordSum(std::string word)
{
    int sum{0};
    for(int i{0}; i < word.length(); i++)
    {
        sum += word[i] - 64;
    }
    return sum;
}

int main ()
{
    //p042_words.txt is a file with many words
    //A=1, Z=26
    //Find how many words have a sum that is a triangular number

    bool* triangle = new bool[1000000];
    for(int i = 0; i < 2000; i++)
    {
        if(i*(i+1)/2 < 1000000)
        {
            triangle[i*(i+1)/2] = true;
        }
    }
    std::ifstream inf{"p042_words.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    std::string input{};
    std::getline(inf, input);
    std::string names[3000];
    std::string name{};
    bool started{false};
    int place{0};
    //Reading words into string array
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

    int num{0};
    for(int i {0}; i < place; i++)
    {
        if(triangle[wordSum(names[i])])
        {
            num++;
        }
    }
    std::cout << num << '\n';
    return 0;
}