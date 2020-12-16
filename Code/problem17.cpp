#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "math_unsigned.cpp"

int single (int i)
{
    if(i == 1)
        {
            return 3;
        }
        else if(i == 2)
        {
            return 3;
        }
        else if(i == 3)
        {
            return 5;
        }
        else if(i == 4)
        {
            return 4;
        }
        else if(i == 5)
        {
            return 4;
        }
        else if(i== 6)
        {
            return 3;
        }
        else if(i == 7)
        {
            return 5;
        }
        else if(i  == 8)
        {
            return 5;
        }
        else if(i  == 9)
        {
            return 4;
        }
        return 0;
}
int main ()
{
    int sum{0};
    for(int i {1}; i < 1000; i++)
    {
        if(i % 100 < 10)
        {
            sum += single(i % 100);
        }
        else if(i % 100 == 10)
        {
            sum += 3;
        }
        else if(i % 100 == 11)
        {
            sum += 6;
        }
        else if(i % 100 == 12)
        {
            sum += 6;
        }
        else if(i % 100 == 13)
        {
            sum += 8;
        }
        else if(i % 100 == 14)
        {
            sum += 8;
        }
        else if(i % 100 == 15)
        {
            sum += 7;
        }
        else if(i % 100 == 16)
        {
            sum += 7;
        }
        else if(i % 100 == 17)
        {
            sum += 9;
        }
        else if(i % 100 == 18)
        {
            sum += 8;
        }
        else if(i % 100 == 19)
        {
            sum += 8;
        }
        else if(i % 100 >= 20 && i % 100 < 40)
        {
            sum += single(i % 10);
            sum += 6;
        }
        else if(i % 100 >= 40 && i % 100 < 70)
        {
            sum += single(i % 10);
            sum += 5;
        }
        else if(i % 100 >= 70 && i % 100 < 80)
        {
            sum += single(i % 10);
            sum += 7;
        }
        else if(i % 100 >= 80)
        {
            sum += single(i % 10);
            sum += 6;
        }
        if(i / 100 > 0)
        {
            sum += single(i / 100);
            sum += 7;
            if(i % 100 != 0)
            {
                sum += 3;
            }
        }
    }
    //Calculates the number of letters in the numbers
    //"one" to "one thousand", more casework than thinking
    std::cout << sum << '\n';
    return 0;
}