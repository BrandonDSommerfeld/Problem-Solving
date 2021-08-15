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
  //Suppose we wanted to create a square with a square shaped hole in the center
  //out of small 1x1 squares. If we have up to 1,000,000 such small squares to used, 
  //how many such shapes can we form?
  //The shapes must be symmetric in both directions, so we can't have an odd sized hole 
  //in an even square, and vice versa

  //Just asking how many differences of squares are less than 1,000,000, easy iteration

  unsigned long long ans = 0;
  for(unsigned long long i = 1; i <= 1000000; i++)
  {
    //Ensure that i and j have the same parity for symmetry, and just compute difference of squares
    for(unsigned long long j = i+2; (j+i)*(j-i) <= 1000000; j += 2)
    {
      ans++;
    }
  }
  std::cout << ans << '\n';
  return 0;
}