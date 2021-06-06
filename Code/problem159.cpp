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
  //Define the digit root of a number to be the sum of its digits:
  //if that is still above 10, repeat until you get to a number below 10

  //Then for a given number, consider all ways of factoring it, without extra 1's
  //Take the digit root of each factor, and add those together
  //For each number, find the factorization which maximizes this sum

  //Find the sum of all such maximum digit root sums for 1 < n < 1,000,000

  unsigned int limit = 1000000;
  //Keep track of the best digit root sum for that number
  int* digitRoots = (int*) calloc(sizeof(int), limit);
  unsigned long long total = 0;
  for(unsigned long long i = 2; i < limit; i++)
  {
    digitRoots[i] = algorithms::digitalRoot(i);
    //For each factor of the current number, see if 
    //we can do better by splitting the number into that factor and the paired factor
    //Further splitting of this pair is already handled, since we have saved 
    //the best way to split these factors already
    for(unsigned long long j = 2; j*j <= i; j++)
    {
      if(i % j == 0)
      {
        if(digitRoots[j] + digitRoots[i/j] > digitRoots[i])
        {
          digitRoots[i] = digitRoots[j] + digitRoots[i/j];
        }
      }
    }
    total += digitRoots[i];
  }
  std::cout << total << '\n';
  return 0;
}