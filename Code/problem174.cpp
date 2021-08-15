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

#define limit 1000000

int main ()
{
  //Just like in 173, we consider squares with square holes that are symmetric

  //For a given number of tiles, there may be multiple ways to create such shapes
  //Find how many numbers t <= 1,000,000 such that there are 1 to 10 ways to create such shapes using
  //exactly t 1x1 tiles, 1 and 10 inclusive



  int* ways = new int[limit+1]{};
  //Iterate over the size of the outer square and the hole, and add one to the number of tiles used
  for(unsigned long long i = 1; i <= limit; i++)
  {
    for(unsigned long long j = i+2; (j+i)*(j-i) <= limit; j += 2)
    {
      ways[(j+i)*(j-i)]++;
    }
  }
  int total = 0;
  //Count how many have the right number of ways
  for(int i = 1; i <= limit; i++)
  {
    if(ways[i] >= 1 && ways[i] <= 10)
    {
      total++;
    }
  }
  std::cout << total << '\n';
  return 0;
}