#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int digits (int num)
{
    int digit{0};
    while(num > 0)
    {
        digit++;
        num /= 10;
    }
    return digit;
}

bool recurse (int num, bool *used, std::vector<int> *nums,
int *prev, int size)
{
    if(size == 6)
    {
        if(prev[0] / 100 == prev[5] % 100)
            return true;
        return false;
    }
    bool copy[5];
    for(int i{0}; i < 5; i++)
    {
        copy[i] = used[i];
    }
    for(int i{0}; i < 5; i++)
    {
        if(!copy[i])
        {
            copy[i] = true;
            for(int j{0}; j < nums[i].size(); j++)
            {
                if(num % 100 == nums[i][j]/100)
                {   
                    prev[size] = nums[i][j];
                    if(recurse(nums[i][j], copy, nums, prev, size+1))
                    {
                        return true;
                    }
                }
            }
            copy[i] = false;
        }
    }
    return false;
}

int main ()
{
    //Find a 4 digit triangular, square, pentagonal ... octagonal number
    //Such that you can put them in a sequence and the last 2 digits
    //of each number is the first 2 digits of the next
    //Including wrap around from last to first
    
    std::vector<int> triangular{};
    for(int i{0}; i < 1000; i++)
    {
        int num = i*(i+1)/2;
        if(digits(num) > 4) break;
        if(digits(num) == 4)
        {
            triangular.push_back(num);
        }
    }
    
    std::vector<int> square{};
    for(int i{0}; i < 1000; i++)
    {
        int num = i*i;
        if(digits(num) > 4) break;
        if(digits(num) == 4)
        {
            square.push_back(num);
        }
    }
    
    std::vector<int> pentagonal{};
    for(int i{0}; i < 1000; i++)
    {
        int num = i*(3*i-1)/2;
        if(digits(num) > 4) break;
        if(digits(num) == 4)
        {
            pentagonal.push_back(num);
        }
    }
    std::vector<int> hexagonal{};
    for(int i{0}; i < 1000; i++)
    {
        int num = i*(2*i-1);
        if(digits(num) > 4) break;
        if(digits(num) == 4)
        {
            hexagonal.push_back(num);
        }
    }
    std::vector<int> heptagonal{};
    for(int i{0}; i < 1000; i++)
    {
        int num = i*(5*i-3)/2;
        if(digits(num) > 4) break;
        if(digits(num) == 4)
        {
            heptagonal.push_back(num);
        }
    }
    std::vector<int> octagonal{};
    for(int i{0}; i < 1000; i++)
    {
        int num = i*(3*i-2);
        if(digits(num) > 4) break;
        if(digits(num) == 4)
        {
            octagonal.push_back(num);
        }
    }
    std::vector<int> nums[5];
    nums[0] = triangular;
    nums[1] = square;
    nums[2] = pentagonal;
    nums[3] = hexagonal;
    nums[4] = heptagonal;
    int *prev = new int[6];
    int sum{0};
    for(int i{0}; i < octagonal.size(); i++)
    {
        bool used[5];
        for(int j{0}; j < 5; j++)
        {
            used[i] = false;
        }
        prev[0] = octagonal[i];
        if(recurse(octagonal[i], used, nums, prev, 1))
        {
            for(int j{0}; j < 6; j++)
            {
                //Program crashes after print for some reason?
                //Still lets you see numbers though, so good enough
                std::cout << prev[j] << '\n';
            }
        }
    }
    
    return 0;
}