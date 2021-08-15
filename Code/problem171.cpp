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

#define last9 1000000000
#define limit 20

unsigned long long* factorials;

void createFactorials(unsigned long long working, unsigned long long curr)
{
  if(curr >= 20) return;

  factorials[curr] = working;
  createFactorials(working*(curr+1), curr+1);
}

unsigned long long sumPermutations(int* digits)
{
  unsigned long long result = 0;
  //Iterate through the digits
  //0 doesn't contribute anything, so ignore it
  for(int i = 1; i < 10; i++)
  {
    if(digits[i] > 0)
    {
      unsigned long long multiplier = factorials[19];
      //Calculate number of ways to arrange other digits
      for(int j = 0; j < 10; j++)
      {
        if(i == j)
        {
          multiplier /= factorials[digits[j]-1];
        }
        else
        {
          multiplier /= factorials[digits[j]];
        }
      }
      multiplier %= last9;
      unsigned long long pow10 = 1;
      //Place digit in units digit through 9th to last digit
      for(int j = 0; j < 9; j++, pow10 *= 10)
      {
        result = (result + i*pow10*multiplier) % last9;
      }
    }
  }
  return result;
}

unsigned long long reachGoal (int goal, int* digits, int used, int min)
{
  //We have to use up all 20 digits, since we pad with 0's if we already reached
  if(used == limit)
  {
    if(goal == 0) 
    {
      return sumPermutations(digits);
    }
    return 0;
  }
  //Early termination, can't reach the goal
  if(goal > 81*(limit-used))
  {
    return 0;
  }
  unsigned long long total = 0;

  for(int i = min; i < 10 && i*i <= goal; i++)
  {
    digits[i]++;
    total = (total + reachGoal(goal-i*i, digits, used+1, i)) % last9;
    digits[i]--;
  }
  return total;
}

int main()
{
  //Find the last 9 digits of the sum of all n, 0 < n < 10^limit, 
  //such that the sum of the squares of the digits of n is also a square number

  factorials = new unsigned long long[20]{};
  createFactorials(1, 0); 
  unsigned long long total = 0;
  //For each square number, we try to find a combination of 20 digits 
  //whose squares sum to that square, 0's allowed
  //Then we just sum all permuations of those digits, allowing leading 0's
  for(int i = 0; i*i < 81*limit; i++)
  {
    int* temp = new int[10]{};
    total = (total + reachGoal(i*i, temp, 0, 0)) % last9;
    delete[] temp;
  }
  std::cout << total << '\n';
  return 0;
}