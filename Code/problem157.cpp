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
  //Consider integer solutions to the equation
  //1/a + 1/b = p/10^n
  //With a <= b and 1 <= n <= 9
  //Find the total number of solutions which satisfy this

  //Let us suppose a and b have gcd d. Then we write
  //1/dx + 1/dy = (x+y)/dxy
  //Where x and y have gcd 1
  //Then x+y cannot cancel any factors of x or y, because x is 0 mod any of its 
  //divisors, and y is not
  //Therefore, x and y can only consist of powers of 2 and 5 for the denominator to 
  //be a power of 10

  //Furthermore, the gcd d must be a factor of x+y, so we can only have extra 
  //factors if they divide the sum of sum powers of 2 and 5

  algorithms::generatePrimes(1000000); 
  unsigned long long total = 0;
  int limit = 9;
  //Iterate over all ways to distribute powers of 2 and 5 between the numbers
  unsigned long long num1_2 = 1;
  for(int pow2_1 = 0; pow2_1 <= limit+1; pow2_1++, num1_2 *= 2)
  {
    unsigned long long num2_2 = 1;
    for(int pow2_2 = 0; pow2_2 <= pow2_1; pow2_2++, num2_2 *= 2)
    {
      unsigned long long num1_5 = 1;
      for(int pow5_1 = 0; pow5_1 <= limit+1; pow5_1++, num1_5 *= 5)
      {
        unsigned long long num2_5 = 1;
        for(int pow5_2 = 0; pow5_2 <= pow5_1; pow5_2++, num2_5 *= 5)
        {
          unsigned long long num1 = num1_2 * num1_5;
          unsigned long long num2 = num2_2 * num2_5;
          int pow2 = pow2_1 + pow2_2;
          int pow5 = pow5_1 + pow5_2;
          unsigned long long numerator = num1 + num2;
          //Don't care about factors of 2 and 5 in the numerator, since 
          //They will be counted later when we increase the power
          while(numerator % 2 == 0)
          {
            numerator /= 2;
            pow2--;
          }
          while(numerator % 5 == 0)
          {
            numerator /= 5;
            pow5--;
          }
          //Find the smallest power of 10 that can be used
          if(pow2 < 1) pow2 = 1;
          if(pow5 < 1) pow5 = 1;
          if(pow2 < pow5) pow2 = pow5;
          else if (pow5 < pow2) pow5 = pow2;
          //If this is below limit, we have solutions
          if(pow2 <= limit)
          {
            //Multiply by limit-pow2+1 because we can always multiply the 
            //numerator and denominator by 10 for another solution as long 
            //as we are below limit

            //We can also multiply by any factor of the numerator for 
            //another solution, so number of factors the numerator has
            total += (limit-pow2+1) * algorithms::numFactors(numerator);
          }
          //Distribute the power of 5 to the other number and do the 
          //same thing, with a check to avoid double counting
          if(pow5_1 != pow5_2 && pow2_1 != pow2_2)
          {
            num1 = num1_2 * num2_5;
            num2 = num2_2 * num1_5;
            pow2 = pow2_1 + pow2_2;
            pow5 = pow5_1 + pow5_2;
            numerator = num1 + num2;
            while(numerator % 2 == 0)
            {
              numerator /= 2;
              pow2--;
            }
            while(numerator % 5 == 0)
            {
              numerator /= 5;
              pow5--;
            }
            if(pow2 < 1) pow2 = 1;
            if(pow5 < 1) pow5 = 1;
            if(pow2 < pow5) pow2 = pow5;
            else if (pow5 < pow2) pow5 = pow2;
            if(pow2 <= limit)
            {
              total += (limit-pow2+1) * algorithms::numFactors(numerator);
            }
          }
        }
      }
    }
  }

  std::cout << total << '\n';
  return 0;
}