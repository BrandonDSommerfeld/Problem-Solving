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

bool recursive_square(math::Unsigned num, math::Unsigned low, 
math::Unsigned high)
{
    if(low == high)
    {
        return low*low == num;
    }
    math::Unsigned mid = (low+high)/2;
    if(mid*mid < num)
    {
        return recursive_square(num, mid+1, high);
    }
    if(mid*mid > num)
    {
        return recursive_square(num, low, mid);
    }
    return true;
}

bool square (math::Unsigned num)
{
    math::Unsigned guess = 1;
    while(guess*guess <= num)
    {
        guess *= 2;
    }
    return recursive_square(num, guess/2, guess);
}

bool permutations(std::string word1, std::string word2)
{
    if(word1.length() != word2.length())
    {
        return false;
    }
    int count1[128]{};
    int count2[128]{};
    for(int i = 0; i < word1.length(); i++)
    {
        count1[word1[i]]++;
        count2[word2[i]]++;
    }
    for(int i = 0; i < 128; i++)
    {
        if(count1[i] != count2[i])
        {
            return false;
        }
    }
    return true;
    
}

int bestSquare(std::string word1, std::string word2)
{
    int loc = 0;
    while(loc < word1.length() && word1[loc] < 60)
    {
        loc++;
    }
    if(loc == word1.length())
    {
        int num1 = std::stoi(word1);
        int num2 = std::stoi(word2);
        if(square(num1) && square(num2))
        {
            if(num1 > num2)
            {
                return num1;
            }
            return num2;
        }
        return 0;
    }
    
    char current = word1[loc];

    int start = 0;
    if(loc == 0 || word2[0] == current)
    {
        start = 1;
    }
    int best = 0;
    for(int num = start; num < 10; num++)
    {
        if(word1.find(num+48) == -1)
        {
            std::string copy1{word1};
            std::string copy2{word2};
            for(int i = 0; i < copy1.length(); i++)
            {
                if(copy1[i] == current)
                {
                    copy1[i] = num+48;
                }
                if(copy2[i] == current)
                {
                    copy2[i] = num+48;
                }
            }
            int val = bestSquare(copy1, copy2);
            if(val > best)
            {
                best = val;
            }
        }
    }
    return best;
}


int main ()
{
    //This problem has a text file with words
    //Then, find all words which have an anagram, or permutation 
    //also in the file

    //Then assign each letter a digit, and we want both
    //the word and the anagram to be squares
    //Find the largest square in one of these pairs

    

    std::ifstream inf{"p098_words.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    std::vector<std::string> words{};
    words.reserve(2000);
    std::string in; 
    std::getline(inf, in);
    std::string current{};
    bool open = false;
    for(int i = 0; i < in.length(); i++)
    {
        if(in[i] == '"')
        {
            if(!open)
            {
                open = true;
            }
            else
            {
                words.push_back(current);
                current = "";
                open = false;
            }
        }
        else if(in[i] != ',')
        {
            current += in[i];
        }
    }
    //Longest word is 14 characters

    int maximum = 0;
    for(int i = 0; i < words.size(); i++)
    {
        for(int j = i+1; j < words.size(); j++)
        {
            if(permutations(words[i], words[j]))
            {
                int value = bestSquare(words[i], words[j]);
                if(value > maximum)
                {
                    maximum = value;
                }
            }
        }
    }
    std::cout << maximum << '\n';
    //This takes a while to run, answer is 18769
    //Could be faster with better square checking/ignore larger
    //words
    

    return 0;
}