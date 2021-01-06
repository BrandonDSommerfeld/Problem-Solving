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

bool works (int *set1, int *set2, int size)
{
    if(set1[0] > set2[0])
    {
        return false;
    }
    for(int i = 1; i < size; i++)
    {
        if(set1[i] > set2[i])
        {
            return true;
        }
    }
    return false;
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

    int *test1 = new int[6];
    for(int i = 0; i < 6; i++)
    {
        test1[i] = i+1;
    }
    int ways1 = 0;
    for(int num1 = 0; num1 < 6; num1++)
    {
        for(int num2 = num1+1; num2 < 6; num2++)
        {
            for(int num3 = num2+1; num3 < 6; num3++)
            {
                int set1[3];
                int set2[3];
                set1[0] = test1[num1];
                set1[1] = test1[num2];
                set1[2] = test1[num3];
                int used = 0;
                for(int i = 0; i < 6; i++)
                {
                    if(i != num1 && i != num2 && i != num3)
                    {
                        set2[used] = test1[i];
                        used++;
                    }
                }
                if(works(set1, set2, 3))
                {
                    ways1++;
                }
            }
        }
    }
    delete[] test1;
    test1 = new int[8];
    for(int i = 0; i < 8; i++)
    {
        test1[i] = i+1;
    }
    int ways2 = 0;
    for(int num1 = 0; num1 < 8; num1++)
    {
        for(int num2 = num1+1; num2 < 8; num2++)
        {
            for(int num3 = num2+1; num3 < 8; num3++)
            {
                for(int num4 = num3+1; num4 < 8; num4++)
                {
                    int set1[4];
                    int set2[4];
                    set1[0] = test1[num1];
                    set1[1] = test1[num2];
                    set1[2] = test1[num3];
                    set1[3] = test1[num4];
                    int used = 0;
                    for(int i = 0; i < 8; i++)
                    {
                        if(i != num1 && i != num2 && i != num3
                        && i != num4)
                        {
                            set2[used] = test1[i];
                            used++;
                        }
                    }
                    if(works(set1, set2, 4))
                    {
                        ways2++;
                    }
                }
            }
        }
    }
    delete[] test1;
    test1 = new int[10];
    for(int i = 0; i < 10; i++)
    {
        test1[i] = i+1;
    }
    int ways3 = 0;

    for(int num1 = 0; num1 < 10; num1++)
    {
        for(int num2 = num1+1; num2 < 10; num2++)
        {
            for(int num3 = num2+1; num3 < 10; num3++)
            {
                for(int num4 = num3+1; num4 < 10; num4++)
                {
                    for(int num5 = num4+1; num5 < 10; num5++)
                    {
                        int set1[5];
                        int set2[5];
                        set1[0] = test1[num1];
                        set1[1] = test1[num2];
                        set1[2] = test1[num3];
                        set1[3] = test1[num4];
                        set1[4] = test1[num5];
                        int used = 0;
                        for(int i = 0; i < 10; i++)
                        {
                            if(i != num1 && i != num2 && i != num3
                            && i != num4 && i != num5)
                            {
                                set2[used] = test1[i];
                                used++;
                            }
                        }
                        if(works(set1, set2, 5))
                        {
                            ways3++;
                        }
                    }
                }
            }
        }
    }
    delete[] test1;
    test1 = new int[12];
    for(int i = 0; i < 12; i++)
    {
        test1[i] = i+1;
    }
    int ways4 = 0;
    for(int num1 = 0; num1 < 12; num1++)
    {
        for(int num2 = num1+1; num2 < 12; num2++)
        {
            for(int num3 = num2+1; num3 < 12; num3++)
            {
                for(int num4 = num3+1; num4 < 12; num4++)
                {
                    for(int num5 = num4+1; num5 < 12; num5++)
                    {
                        for(int num6 = num5+1; num6 < 12; num6++)
                        {
                            int set1[6];
                            int set2[6];
                            set1[0] = test1[num1];
                            set1[1] = test1[num2];
                            set1[2] = test1[num3];
                            set1[3] = test1[num4];
                            set1[4] = test1[num5];
                            set1[5] = test1[num6];
                            int used = 0;
                            for(int i = 0; i < 12; i++)
                            {
                                if(i != num1 && i != num2 && i != num3
                                && i != num4 && i != num5 && i != num6)
                                {
                                    set2[used] = test1[i];
                                    used++;
                                }
                            }
                            if(works(set1, set2, 6))
                            {
                                ways4++;
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << ways1 << ' ' << ways2 << ' ' << ways3 << ' ' 
    << ways4 << '\n';

    math::Unsigned answer = 0;
    answer += choose(12, 4);
    answer += ways1 * choose(12,6);
    answer += ways2 * choose(12,8);
    answer += ways3 * choose(12, 10);
    answer += ways4 * choose(12, 12);
    std::cout << answer << '\n';
    return 0;
}