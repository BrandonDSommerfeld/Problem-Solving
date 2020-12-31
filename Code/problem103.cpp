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

bool works(int *set)
{
    if(set[0] + set[1] <= set[6])
    {
        return false;
    }
    if(set[0] + set[1] + set[2] <= set[5]+set[6])
    {
        return false;
    }
    if(set[0]+set[1]+set[2]+set[3] <= set[4]+set[5]+set[6])
    {
        return false;
    }

    for(int num1 = 0; num1 < 7; num1++)
    {
        for(int num2 = 0; num2 < 7; num2++)
        {
            if(num1 != num2)
            {
                for(int num3 = 0; num3 < 7; num3++)
                {
                    if(num1 != num3 && num2 != num3)
                    {
                        for(int num4 = 0; num4 < 7; num4++)
                        {
                            if(num1 != num4 && num2 != num4
                            && num3 != num4)
                            {
                                if(set[num1]+set[num2] == set[num3]+set[num4])
                                {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for(int num1 = 0; num1 < 7; num1++)
    {
        for(int num2 = 0; num2 < 7; num2++)
        {
            if(num1 != num2)
            {
                for(int num3 = 0; num3 < 7; num3++)
                {
                    if(num1 != num3 && num2 != num3)
                    {
                        for(int num4 = 0; num4 < 7; num4++)
                        {
                            if(num1 != num4 && num2 != num4
                            && num3 != num4)
                            {
                                for(int num5 = 0; num5 < 7; num5++)
                                {
                                    if(num1 != num5 && num2 != num5
                                    && num3 != num5 && num4 != num5)
                                    {
                                        for(int num6 = 0; num6 < 7; num6++)
                                        {
                                            if(num1 != num6 && num2 != num6
                                            && num3 != num6 && num4 != num6
                                            && num5 != num6)
                                            {
                                                if(set[num1]+set[num2]+set[num3]
                                                == set[num4]+set[num5]+set[num6])
                                                {
                                                    return false;
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
    }
    return true;
}

int main ()
{
    //Find a set with 7 elements, such that for any 2 disjoint
    //subsets chosen, the sum of the elements in the larger one
    //is greater than the sum of the elements in the smaller
    //Also, all subsets of the same size have different sums
    //In particular, the sum of the 7 element set must be minimal

    //This is a stupid question
    //The problem says there is an "algorithm" to create
    //The smallest sum by taking the middle element of the 
    //previous smallest set, and then adding it to each
    //element at inserting it at the front, but says that 
    //doesn't always work, but just doing that
    //actually does work here

    //Arguably, without using this algorithm the solution is
    //"Just guess a ton of sets", so there isn't really a nice 
    //solution to this problem
    int test[7];
    test[0] = 20;
    test[1] = 31;
    test[2] = 38;
    test[3] = 39;
    test[4] = 40;
    test[5] = 42; 
    test[6] = 45;
    std::cout << works(test) << '\n';
    return 0;
}