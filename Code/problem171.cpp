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

//Recursive function which sums all permutations of te 9 digits given recursively
unsigned long long helper (int* digits, int loc, unsigned long long partial, bool allowZero, int max)
{
  if(loc == max) return partial;

  unsigned long long total = 0;
  for(int i = 0; i < 10; i++)
  {
    if(digits[i] > 0 && (loc > 0 || i > 0 || allowZero))
    {
      digits[i]--;
      total += helper(digits, loc+1, partial*10+i, true, max);
      digits[i]++;
    }
  }
  return total;
}

unsigned long long helper2 (int* digits, int* working, int more)
{
  if(more == 0) return helper(working, 0, 0, false, more);
}

unsigned long long sumPermutations(int* digits, int used)
{
  if(used <= 9) return helper(digits, 0, 0, false, used); 
}



int main()
{
  //Find the last 9 digits of the sum of all n, 0 < n < 10^20, 
  //such that the sum of the squares of the digits of n is also a square number
  int* temp = new int[10]{};
  return 0;
}