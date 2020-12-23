#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include "math_unsigned.cpp"

int maximum(std::vector<int> nums)
{
    //Build the numbers from the outside in, by reversing operations
    std::set<int> possible{};
    //Do each operation one at a time
    for(int num1 = 0; num1 < 4; num1++)
    {
        for(int op1 = 0; op1 < 4; op1++)
        {
            for(int num2 = 0; num2 < 4; num2++)
            {
                if(num1 != num2)
                {
                    double result1 = 0;
                    switch(op1)
                    {
                        case 0:
                            if(nums[num2] == 0)
                            {
                                continue;
                            }
                            result1 = static_cast<double>(nums[num1])/nums[num2];
                            break;
                        case 1:
                            result1 = nums[num1]*nums[num2];
                            break;
                        case 2:
                            result1 = nums[num1]+nums[num2];
                            break;
                        case 3:
                            result1 = nums[num1]-nums[num2];
                            break;
                    }
                    for(int op2 = 0; op2 < 4; op2++)
                    {
                        for(int num3 = 0; num3 < 4; num3++)
                        {
                            if(num1 != num3 && num2 != num3)
                            {
                                double result2 = 0;
                                switch(op2)
                                {
                                    case 0:
                                        if(nums[num3] == 0)
                                        {
                                            continue;
                                        }
                                        result2 = result1/nums[num3];
                                        break;
                                    case 1:
                                        result2 = result1*nums[num3];
                                        break;
                                    case 2:
                                        result2 = result1+nums[num3];
                                        break;
                                    case 3:
                                        result2 = result1-nums[num3];
                                        break;
                                }
                                for(int op3 = 0; op3 < 4; op3++)
                                {
                                    for(int num4 = 0; num4 < 4; num4++)
                                    {
                                        if(num1 != num4 && num2 != num4 && num3 != num4)
                                        {
                                            double result3 = 0;
                                            switch(op3)
                                            {
                                                case 0:
                                                    if(nums[num4] == 0)
                                                    {
                                                        continue;
                                                    }
                                                    result3 = result2/nums[num4];
                                                    break;
                                                case 1:
                                                    result3 = result2*nums[num4];
                                                    break;
                                                case 2:
                                                    result3 = result2+nums[num4];
                                                    break;
                                                case 3:
                                                    result3 = result2-nums[num4];
                                                    break;
                                            }
                                            int closest = std::round(result3);
                                            if(std::abs(closest-result3) < 0.01)
                                            {
                                                possible.insert(closest);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //Do operations on pairs, then operation on results
    for(int num1 = 0; num1 < 4; num1++)
    {
        for(int op1 = 0; op1 < 4; op1++)
        {
            for(int num2 = 0; num2 < 4; num2++)
            {
                if(num1 != num2)
                {
                    double result1 = 0;
                    switch(op1)
                    {
                        case 0:
                            if(nums[num2] == 0)
                            {
                                continue;
                            }
                            result1 = static_cast<double>(nums[num1])/nums[num2];
                            break;
                        case 1:
                            result1 = nums[num1]*nums[num2];
                            break;
                        case 2:
                            result1 = nums[num1]+nums[num2];
                            break;
                        case 3:
                            result1 = nums[num1]-nums[num2];
                            break;
                    }
                    for(int op2 = 0; op2 < 4; op2++)
                    {
                        for(int num3 = 0; num3 < 4; num3++)
                        {
                            if(num1 != num3 && num2 != num3)
                            {
                                for(int num4 = 0; num4 < 4; num4++)
                                {
                                    if(num1 != num4 && num2 != num4 && num3 != num4)
                                    {
                                        double result2 = 0;
                                        switch(op2)
                                        {
                                            case 0:
                                                if(nums[num4] == 0)
                                                {
                                                    continue;
                                                }
                                                result2 = static_cast<double>(nums[num3])/nums[num4];
                                                break;
                                            case 1:
                                                result2 = nums[num3]*nums[num4];
                                                break;
                                            case 2:
                                                result2 = nums[num3]+nums[num4];
                                                break;
                                            case 3:
                                                result2 = nums[num3]-nums[num4];
                                                break;
                                        }
                                        for(int op3 = 0; op3 < 4; op3++)
                                        {
                                            double result3 = 0;
                                            switch(op3)
                                            {
                                                case 0:
                                                    if(result2 == 0)
                                                    {
                                                        continue;
                                                    }
                                                    result3 = result1 / result2;
                                                    break;
                                                case 1:
                                                    result3 = result1*result2;
                                                    break;
                                                case 2:
                                                    result3 = result1+result2;
                                                    break;
                                                case 3:
                                                    result3 = result1-result2;
                                                    break;
                                            }
                                            int closest = std::round(result3);
                                            if(std::abs(closest-result3) < 0.01)
                                            {
                                                possible.insert(closest);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    int prev = 0;
    for(auto iter = possible.cbegin(); iter != possible.cend(); iter++)
    {
        if(*iter > 0 && *iter - 1 != prev)
        {
            return prev;
        }
        prev = *iter;
    }
    return possible.size();
}

int main ()
{
    //Find the set of 4 distinct 1 digit numbers
    //Such that with parantheses, *, /, +, and - you can create
    //all numbers from 1 to n, with n as large as possible
    //Note: Not allowed to concatenate into 12 or something

    //Iterate over all sets
    int highest = 0;
    int place = 0;

    //Honestly just tedious to make all of the loops above
    for(int a = 0; a < 10; a++)
    {
        for(int b = a+1; b < 10; b++)
        {
            for(int c = b+1; c < 10; c++)
            {
                for(int d = c+1; d < 10; d++)
                {
                    std::vector<int> temp{};
                    temp.push_back(a);
                    temp.push_back(b);
                    temp.push_back(c);
                    temp.push_back(d);
                    int best = maximum(temp);
                    if(best > highest)
                    {
                        highest = best;
                        place = 1000*a+100*b+10*c+d;
                    }
                }
            }
        }
    }
    std::cout << highest << '\n';
    std::cout << place << '\n';
    
    return 0;
}