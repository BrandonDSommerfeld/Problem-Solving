#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.cpp"

bool recursive_square(math::Unsigned num, math::Unsigned low, 
math::Unsigned high)
{
    if(low == high)
    {
        return low*low == num;
    }
    math::Unsigned mid = (low+high)/2;
    if(mid*mid < num)
    {
        return recursive_square(num, mid+1, high);
    }
    if(mid*mid > num)
    {
        return recursive_square(num, low, mid);
    }
    return true;
}

bool square (math::Unsigned num)
{
    math::Unsigned guess = 1;
    while(guess*guess <= num)
    {
        guess *= 2;
    }
    return recursive_square(num, guess/2, guess);
}

int gcd(int num1, int num2)
{
    if(num1 > num2)
    {
        if(num1 % num2 == 0)
        {
            return num2;
        }
        return gcd(num1-num2*(num1/num2), num2);
    }
    if(num2 % num1 == 0)
    {
        return num1;
    }
    return gcd(num2-num1*(num2/num1), num1);
}

std::vector<std::vector<int>> continued (int D)
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

    std::vector<int> nums{};

    std::vector<int> repeating{};
    std::vector<int> start{};
    while(true)
    {
        double approx = (a+b*std::sqrt(D))/d;
        
        int floor = std::floor(approx);

       
        nums.push_back(floor);

        a -= d*floor;
        
        int prev = d;
        d = a*a-b*b*D;
        a = prev*a;
        
        b = -prev*b;
        if(d < 0)
        {
            a *= -1;
            b *= -1;
            d *= -1;
        }
        int q = gcd(gcd(a,b), d);
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
            for(int i = 0; i < hit; i++)
            {
                start.push_back(nums[i]);
            }
            for(int i = hit; i < nums.size(); i++)
            {
                repeating.push_back(nums[i]);
            }
            break;
        }
        std::vector<int> *current = new std::vector<int>{};
        current->push_back(a);
        current->push_back(b);
        current->push_back(d);
        seen.push_back(*current);
    }
    std::vector<std::vector<int>> res{};
    res.push_back(start);
    res.push_back(repeating);
    return res;
}

int main ()
{
    //Find the D such that the minimum solution of x to
    //x^2 - D y^2 = 1
    //is as large as possible for D <= 1000

    math::Unsigned largest = 0;
    int place = 0;

    //This was basically impossible to solve without looking up
    //The equation above is known as the Pell equation
    //And solutions x,y give you a good approximation
    // x/y is about sqrt(D)
    //Thus, solutions to the equation are actually the best rational
    //Approximation for sqrt(D), given by cutting the continued
    //Fraction off at a certain point
    for(int D = 2; D <= 1000; D++)
    {
        if(!square(D))
        {
            std::vector<std::vector<int>> root = continued(D);

            math::Unsigned num1 = 1;
            math::Unsigned num2 = 0;
            math::Unsigned denom1 = 0;
            math::Unsigned denom2 = 1;

            int loc = 0;
            bool start = true;

            while(true)
            {
                if(start)
                {
                    num2 = root[0][loc]*num1+num2;
                    denom2 = root[0][loc]*denom1 + denom2;
                    loc++;
                    if(loc == root[0].size())
                    {
                        loc = 0;
                        start = false;
                    }
                }
                else
                {
                    num2 = root[1][loc]*num1+num2;
                    denom2 = root[1][loc]*denom1 + denom2;
                    loc++;
                    loc %= root[1].size();
                }
                if(num2*num2>D*denom2*denom2 && 
                    num2*num2-D*denom2*denom2 == 1)
                {
                    if(num2 > largest)
                    {
                        largest = num2;
                        place = D;
                    }
                    break;
                }
                math::Unsigned temp = num1;
                num1 = num2;
                num2 = temp;

                math::Unsigned temp2 = denom1;
                denom1 = denom2;
                denom2 = temp2;
            }
            
        }
    }
    std::cout << largest << '\n';
    std::cout << place << '\n';
    return 0;
}