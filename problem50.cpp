#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"


int main ()
{
    //Find the prime below 1000000 which can be written as the 
    //longest sequence of consecutive primes

    bool* composite = new bool[1000000];
    for(int i{2}; i < 1000; i++)
    {
        if(!composite[i])
        {
            for(int j{2}; i*j < 1000000; j++)
            {
                composite[i*j] = true;
            }
        }
    }

    std::vector<int> primes{};
    for(int i{2}; i < 1000000; i++)
    {
        if(!composite[i])
        {
            primes.push_back(i);
        }
    }
    int longest{0};
    int best{0};
    for(int i{primes.size()-1}; i >= 0; i--)
    {
        int num{primes[i]};
        for(int start{0}; start < i; start++)
        {
            if(num / primes[start] > longest)
            {
                int sum{0};
                int used{0};
                while(sum < num)
                {
                    sum += primes[start+used];
                    used++;
                }
                if(sum == num)
                {
                    if(used > longest)
                    {
                        longest = used;
                        best = num;
                    }
                }
            }
            else
            {
                break;
            }
            
        }
    }
    std::cout << best << '\n';
    std::cout << longest << '\n';
    return 0;
}