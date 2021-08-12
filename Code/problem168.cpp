#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include "math_unsigned.h"
#include "math_signed.h"
#include "math_rational.h"
#include "math_fast_rational.h"
#include "algorithms.h"

unsigned long long extendTo5(unsigned long long num, unsigned long long digits)
{
  switch(digits)
  {
    case 1:
      return num*11111;
    case 2:
      return (num*10101) % 100000;
    case 3:
      return (num * 1001) % 100000;
    case 4:
      return (num * 10001) % 100000;
    default:
      return num;
  }
}

//For numbers with less than 5 digits, like 1/3, find the sum of 33,333,3333
unsigned long long sumSmall(unsigned long long num, unsigned long long digits)
{
  switch(digits)
  {
    case 1: 
      //Exclude single digit numbers
      return (num*1233) % 100000;
    case 2:
      return (num*102) % 100000;
    default:
      return num;
  }
}

int main ()
{
  //Find the last 5 digits of the sum of all numbers 10 < n < 10^100, 
  //for which if you rotate all of the digits to the right,
  //and bring the last digit to the front, the result is a multiple of n
  unsigned long long sum = 0;
  unsigned long long limit = 100;
  unsigned long long last5 = 100000;
  //The answers are like 142857, the repeating part of a fraction
  //In this case, we start with 1/7 as 0.142857 repeating, and since it has 6 repeating 
  //digits, we multiply by 10^5 to get
  //14285.714285 repeating
  //That is, we right shift by multiplying by 10 to the power of 1 less than the number of digits
  //In this case, 10^5 mod 7 = 5, so the result is 5/7
  //Thus, we need to start with a fraction greater than 1/10 so that the leading digit isn't 0,
  //and when we multiply by 10 to this power, it still needs to be less than 1 so that we don't
  //add an extra digit. This greatly restricts our search space

  //In fact, because 10^(n-1) must be less than 10 mod i, and 10^n = 1 mod i, we cannot 
  //have i > 100
  for(unsigned long long i = 3; i < limit; i += 2)
  {
    if(i % 5 != 0)
    {
      //Find the repeating fraction of the number, and 10^(n-1) mod i
      unsigned long long multiplier = 1;
      math::Unsigned num = 10;
      bool works = false;
      unsigned long long digits = 1;
      for(int j = 0; j < 100 && !works; j++)
      {
        if((multiplier * 10) % i == 1)
        {
          works = true;
        }
        else
        {
          multiplier = (multiplier * 10) % i;
          num *= 10; 
          digits++;
        }
      }
      if(works && multiplier < 10)
      {
        num -= 1;
        num /= i;
        num %= last5;
        unsigned long long end = num.to_uint();
        //Numerator of the fraction. Needs to be at least 1/10, up to 1/0.9999 when multiplier applied
        for(int j = i/10+1; j*multiplier <= i; j++)
        {
          //Exception to count 99999 just once
          if(algorithms::gcd(i,j) == 1 || (i == 9 && j == 9))
          {
            if(digits < 5)
            {
              sum = (sum + sumSmall(end,digits)*j) % last5;
            }
            unsigned long long temp = extendTo5(end, digits); 
            unsigned long long start = 0;
            while(start < 5)
            {
              start += digits;
            }
            //Account for taking the digits and just making them repeat for a larger number
            sum = (sum + temp*j*((100-start)/digits + 1)) % last5;
          }
        }
      }
    }
  }
  std::cout << sum << '\n';
  return 0;
}