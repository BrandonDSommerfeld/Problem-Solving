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
  return 0;
}