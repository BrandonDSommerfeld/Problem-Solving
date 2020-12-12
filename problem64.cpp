#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

int main ()
{
    //Find how many square roots N <= 10000
    //Have a repeating portion of odd length

    //Just apply continued fraction algorithm
    //Keep track of the current number as
    //(a+b sqrt(c))/d
    int num{0};
    for(int i{2}; i <= 10000; i++)
    {
        long double root = std::sqrt(i);
        int guess = std::round(root);
        if(guess*guess != i)
        {
            int a = 0;
            int b = 1;
            int d = 1;

            std::vector<std::vector<int>> seen{};
            std::vector<int> first{};
            first.push_back(a);
            first.push_back(b);
            first.push_back(d);
            seen.push_back(first);
            while(true)
            {
                double approx = (a+b*std::sqrt(i))/d;
                int floor = std::floor(approx);

                a -= d*floor;

                int prev = d;
                d = a*a-b*b*i;
                a = prev*a;
                b = -prev*b;
                int q = std::__gcd(std::__gcd(a, b), d);
                d /= q;
                a /= q;
                b /= q;

                int hit = -1;
                for(int j = 0; j < seen.size(); j++)
                {
                    if(a == seen[j][0] && 
                    b == seen[j][1] &&
                    d == seen[j][2])
                    {
                        hit = j;
                        break;
                    }
                }
                if(hit != -1)
                {
                    if((seen.size()-hit)%2 == 1)
                    {
                        num++;
                    }
                    break;
                }
                std::vector<int> current{};
                current.push_back(a);
                current.push_back(b);
                current.push_back(d);
                seen.push_back(current);
            }
        }
    }
    std::cout << num << '\n';
    return 0;
}