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

math::Unsigned choose (int n, int k)
{
    math::Unsigned ans = 1;
    for(int i = k+1; i <= n; i++)
    {
        ans *= i;
    }
    for(int i = 1; i <= n-k; i++)
    {
        ans /= i;
    }
    return ans;
}

int main ()
{
    //Continuing from previous problems, for sets of size 12
    //How many sets do you really need to check for equality?

    //For pairs of subsets of size 2, you just choose 4 elements
    //And only check 1 way of putting them into sets, with the
    //smallest and largest in the same set
    //If you put 1 2 and 3 4,
    //They cannot be equal since 3 > 1 and 4 > 2
    //If you do 1 3 and 2 4, 2 > 1 and 4 > 3 so greater sum always

    //Do this for triplets up to pairs with size 6
    
    return 0;
}