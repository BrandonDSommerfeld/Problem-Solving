#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //How many different products a*b=c can be made using every digit
    //1-9 exactly once. Sum all such unique c.
    int sum{0};
    bool used[100000];
    for(int i{0}; i < 100000; i++)
    {
        used[i] = false;
    }
    for(int i{1}; i < 10000; i++)
    {
        for(int j{1}; j < 10000; j++)
        {
            bool used[10];
            bool works = true;
            //Keep track of used digits, 0 is not allowed so just used already
            used[0] = true;
            for(int j{1}; j < 10; j++)
            {
               used[j] = false;
            }
            int copy{i};
            while(copy > 0)
            {
               int digit{copy % 10};
               if(used[digit]) works = false;
               used[digit] = true;
               copy /= 10;
            }
            copy = j;
            while(copy > 0)
            {
               int digit{copy % 10};
               if(used[digit]) works = false;
               used[digit] = true;
               copy /= 10;
            }
            copy = i*j;
            while(copy > 0)
            {
               int digit{copy % 10};
               if(used[digit]) works = false;
               used[digit] = true;
               copy /= 10;
            }
            for(int k{0}; k < 10; k++)
            {
                if(!used[k]) works = false;
            }
            if(works && i*j < 100000 && !used[i*j])
            {
                sum += i*j;
                used[i*j] = true;
            }
        }
    }
    std::cout << sum << '\n';
    return 0;
}