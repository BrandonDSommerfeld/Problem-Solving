#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "math_rational.cpp"
#include "math_fast_rational.cpp"
#include "algorithms.cpp"

int main ()
{
  //Find the last 5 digits of 1,000,000,000,000!, excluding the trailing 0's

  unsigned long long limit = 1000000000000ULL;
  unsigned long long ans = 1;
  unsigned long long digit = 100000;

  //For each factor, remove all trailing zeros, then mod by digit, then multiply
  unsigned long long pow2 = 0;
  unsigned long long pow5 = 0;
  for(unsigned long long i = 1; i < digit; i++)
  {
    if(i % 10 != 0)
    {
      unsigned long long temp1 = 0;
      unsigned long long temp2 = 0;
      unsigned long long copy = i;
      while(copy % 2 == 0)
      {
        temp1++;
        copy /= 2;
      }
      while(copy % 5 == 0)
      {
        temp2++;
        copy /= 5;
      }
      unsigned long long pow = 0;
      for(unsigned long long multiplier = 1; multiplier*i < limit; multiplier *= 10)
      {
        pow += (limit) / (digit*multiplier);
      }
      ans = (ans * algorithms::exp(copy, pow, digit)) % digit;
      pow2 += temp1*pow;
      pow5 += temp2*pow;
    }
  } 
  std::cout << ans << '\n';
  std::cout << pow2 << ' ' << pow5 << '\n';
  std::cout << algorithms::exp(2, pow2-pow5, digit) << '\n';
  std::cout << (ans * algorithms::exp(2, pow2-pow5, digit)) % digit << '\n';
  return 0;
}