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



int main ()
{
  //Define f(0) = 1, and f(n) is the number of ways to write n using powers of 2, 
  //using each power at most twice

  //For every fraction p/q, there exists some n such that f(n)/f(n-1) = p/q

  //Find the smallest n such that f(n)/f(n-1) = 123456789/987654321

  //Express this number in shortened binary notation
  //That is, for the number 11110001, it consists of 4 1's, 3 0's, then 1 1, so it looks like
  //4,3,1 in shortened binary notation


  //The shortened binary notation is a big hint, since the value of f(n) depends on the shortened 
  //binary notation of the number 
  static constexpr int limit = 100;
  int ways[limit][10]{};
  ways[0][0] = 1;
  int pow2 = 1;
  for(int i = 0; i < 10; i++, pow2 *= 2)
  {
    for(int j = limit-1; j >= 0; j--)
    {
      if(i > 0)
      {
        ways[j][i] += ways[j][i-1];
      }
      if(j+pow2 < limit && ways[j][i] > 0)
      {
        ways[j+pow2][i] += ways[j][i];
      }
      if(j+2*pow2 < limit && ways[j][i] > 0)
      {
        ways[j+2*pow2][i] += ways[j][i];
      }
    }
  }

  for(int i = 0; i < limit; i++)
  {
    std::cout << algorithms::binary(i) << ' ' << ways[i][9] << '\n';
  }
  return 0;
}