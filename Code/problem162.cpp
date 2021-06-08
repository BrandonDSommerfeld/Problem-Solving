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
  //How many hexadecimal numbers with 16 or less digits contain all 3 digits 0,1, and A?
  //Exclude leading 0's from the number

  //Answer should be expressed in hexadecimal

  //Just use the principle of inclusion and exclusion
  //We start with all numbers of the given length, and remove those 
  //which lack 0,1, or A
  //But then we double removed those which lack 2 of them, so 
  //we add those back in, and finally subtract out numbers which lack all 3
  math::Unsigned total = 0;
  for(int len = 3; len <= 16; len++)
  {
    math::Unsigned allDigits = 15*algorithms::exp(16, len-1);
    math::Unsigned missingAll3 = algorithms::exp(13, len);
    math::Unsigned missing0 = algorithms::exp(15, len);
    math::Unsigned missing1 = 14*algorithms::exp(15, len-1);
    math::Unsigned missingA = 14*algorithms::exp(15, len-1);
    math::Unsigned missing01 = algorithms::exp(14, len);
    math::Unsigned missing0A = algorithms::exp(14, len);
    math::Unsigned missing1A = 13*algorithms::exp(14, len-1);
    total += (allDigits+missing01+missing0A+missing1A) - (missingAll3+missing0+missing1+missingA);
  }
  std::cout << algorithms::hexadecimal(total) << '\n';
  return 0;
}