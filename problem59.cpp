#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //p059_cipher.txt contains an encypted message
    //The key is 3 lowercase letters, and to decode message
    //You take ascii values as binary, and repeat it as much as needed
    //Then xor with encrypted message
    //Find the sum of ascii values in original text

    std::ifstream inf{"p059_cipher.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }
    std::string in{};
    std::getline(inf, in);
    std::vector<char> input{};
    char num{0};
    for(int i{0}; i < in.length(); i++)
    {
        if(in[i] != ',')
        {
            num *= 10;
            num += in[i] - 48;
        }
        else
        {
            input.push_back(num);
            num = 0;
        }
    }
    input.push_back(num);
    //Iterate through all possible passwords
    //Answer ends up being exp, which was awful to find
    //It says it is normal English, but it has fractions and numbers
    for(char a{'a'}; a <= 'z'; a++)
    {
        for(char b{'a'}; b <= 'z'; b++)
        {
            for(char c{'a'}; c <= 'z'; c++)
            {
                char* message = new char[1500];
                int current {0};
                bool words{true};
                for(int i{0}; i < input.size() && words; i++)
                {
                    if(current == 0)
                    {
                        message[i] = input[i] ^ a;
                    }
                    else if(current == 1)
                    {
                        message[i] = input[i] ^ b;
                    }
                    else
                    {
                        message[i] = input[i] ^ c;
                    }
                    if(message[i] < 32 || message[i] > 122)
                    {
                        words = false;
                    }
                    current = (current+1)%3;
                }
                message[input.size()] = '\0';
                if(words)
                {
                    std::cout << a << b << c << ' ';
                    std::cout << message << '\n';
                }
                delete[] message;
            }
        }
    }
    //Just add up ascii values now that it was found
    int sum{0};
    char* message = new char[1500];
    int current {0};
    for(int i{0}; i < input.size(); i++)
    {
        if(current == 0)
         {
            message[i] = input[i] ^ 'e';
         }
        else if(current == 1)
         {
             message[i] = input[i] ^ 'x';
         }
        else
        {
          message[i] = input[i] ^ 'p';
        }
        sum += message[i];            
        current = (current+1)%3;
    }
    std::cout << sum << '\n';
    return 0;
}