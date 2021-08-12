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

std::map<std::pair<math::Unsigned, math::Unsigned>, math::Unsigned> dict;

math::Unsigned numWays(const math::Unsigned& num, const math::Unsigned& pow)
{
  if(pow == 1 && num <= 2)
  {
    return 1;
  }
  auto iter = dict.find(std::pair<math::Unsigned, math::Unsigned>(num, pow));
  if(iter != dict.end())
  {
    return (*iter).second;
  }
  math::Unsigned total = 0;
  if(2*pow-1 >= num)
  {
    total += numWays(num, pow/2);
  }
  if(num >= pow && 3*pow-1 >= num)
  {
    total += numWays(num-pow, pow/2);
  }
  if(num >= 2*pow && 4*pow-1 >= num)
  {
    total += numWays(num-2*pow, pow/2);
  }
  std::pair<math::Unsigned, math::Unsigned> temp{num, pow};
  std::pair<std::pair<math::Unsigned, math::Unsigned>, math::Unsigned> temp2{temp, total};
  dict.insert(temp2);
  return total;
}

int main ()
{
  //Find the number of ways to express 10^25 as the sum of powers of 2, using each power at most twice
  math::Unsigned num = 1;
  for(int i = 0; i < 25; i++)
  {
    num *= 10;
  }
  math::Unsigned pow = 1;
  while(pow < num)
  {
    pow *= 2;
  }
  pow /= 2;
  //Simple brute force recursive search, with memoization for speed up
  std::cout << numWays(num, pow) << '\n';
  return 0;
}