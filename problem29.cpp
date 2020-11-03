#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find number of distinct values of a^b for
    // 2 <= a,b <= 100
    //Just do 99*99 and subtract duplicates
    int num{99*99};
    num -= 49; //10 and 100 overlap 10^4 = 100^2 ... 10^100 = 100^50
    num -= 49; //For 7 and 49
    num -= 49; //For 6 and 36
    num -= 49; //For 5 and 25
    
    bool hit[601];
    int hits{0};
    for(int i{2}; i <= 600; i++)
    {
        hit[i] = false;
        if(i <= 100)
        {
            hit[i] = true;
        }
        if(i % 2 == 0 && i / 2 <= 100)
        {
            hit[i] = true;
        }
        if(i % 3 == 0 && i / 3 <= 100)
        {
            hit[i] = true;
        }
        if(i % 4 == 0 && i / 4 <= 100)
        {
            hit[i] = true;
        }
        if(i % 5 == 0 && i / 5 <= 100)
        {
            hit[i] = true;
        }
        if(i % 6 == 0 && i / 6 <= 100)
        {
            hit[i] = true;
        }
        if(hit[i])
        {
            hits++;
        }
    }
    bool hit2[401];
    int hits2{0};
    for(int i{2}; i <= 400; i++)
    {
        hit2[i] = false;
        if(i <= 100)
        {
            hit2[i] = true;
        }
        if(i % 2 == 0 && i / 2 <= 100)
        {
            hit2[i] = true;
        }
        if(i % 3 == 0 && i / 3 <= 100)
        {
            hit2[i] = true;
        }
        if(i % 4 == 0 && i / 4 <= 100)
        {
            hit2[i] = true;
        }
        if(hit2[i])
        {
            hits2++;
        }
    }
    //Counted powers of 2 and 3 separately because they were hard
    num = (num - (99*10) + hits + hits2);
    std::cout << num << '\n';
    
    return 0;
}