#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Calculates the number of Sundays from beginning of 1900
    //To end of 2000 which fall on the 1st of the month
    int day{2};
    int sum{0};
    for(int i {1}; i <= 100; i++)
    {
        for(int j{1}; j <= 12;j++)
        {
            if(day == 0)
            {
                sum++;
            }
            if(j == 4 || j == 6 || j == 9 || j == 11)
            {
                day = (day+2)%7;
            }
            else if (j == 2)
            {
                if(i % 4 == 0)
                {
                    day = (day+1)%7;
                }
            }
            else
            {
                day = (day+3)%7;
            }
            
        }
    }
    std::cout << sum << '\n';
    return 0;
}