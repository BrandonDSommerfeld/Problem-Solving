#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include <map>
#include <utility>
#include "math_unsigned.h"
#include "math_signed.h"
#include "math_rational.h"
#include "math_fast_rational.h"
#include "algorithms.h"

#define limit 18
unsigned long long* factorials;

void createFactorials(unsigned long long working, unsigned long long curr)
{
  if(curr >= limit) return;

  factorials[curr] = working;
  createFactorials(working*(curr+1), curr+1);
}

unsigned long long recurse(int* digits, int used, int min, int leading)
{
  if(used == limit-1)
  {
    //Number of ways to arrange the 17 digits chosen
    unsigned long long ans = factorials[17];
    for(int i = 0; i < 10; i++)
    {
      ans /= factorials[digits[i]];
    } 
    return ans;
  }
  unsigned long long result = 0;
  for(int i = min; i < 10; i++)
  {
    //Account for the leading digit already being there
    if((i != leading && digits[i] < 3) || (i == leading && digits[i] < 2))
    {
      digits[i]++;
      result += recurse(digits, used+1, i, leading);
      digits[i]--;
    }
  }
  return result;
}

int main ()
{
  //How many 18 digits numbers with no leading 0's are there such that no digit occurs more than 3 times?

  factorials = new unsigned long long[18]{};
  createFactorials(1,0);
  unsigned long long total = 0;
  //Simply iterate over all leading digits, and recursively figure out how to use 3 or less digits
  //Then just multiply by how many ways there are to arrange those 17 digits
  for(int leading = 1; leading < 10; leading++)
  {
    int* digits = new int[10]{};
    total += recurse(digits, 0, 0, leading);
    delete[] digits;
  }
  std::cout << total << '\n';
  return 0;
}