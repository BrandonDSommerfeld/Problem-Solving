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

std::vector<int> compressedBinary(const std::string& s)
{
  int num{0};
  char last{'1'};
  std::vector<int> ans{};
  for(size_t i{0}; i < s.length(); i++)
  {
    if(s[i] == last)
    {
      num++;
    }
    else
    {
      ans.push_back(num);
      num = 1;
      last = s[i];
    }
  }
  ans.push_back(num);
  return ans;
}

unsigned long long compressedBinaryToWays(const std::vector<int>& bin)
{
  //Product plus 1 for 2 digits, just 1 for 1 digit

  //If it is odd, it is the same as the case with 1 less than it, because trailing 1's don't make more ways
  //Since if the units is 1, you have to have 1 1, and so on up for each trailing 1

  //Thus, for 3 digits, it is the product of the first 2 plus 1
  //Pattern: If you have n 1's followed by m 0's, that is mn+1 ways. +1 for not splitting, and 
  //you can choose any number of the n 1's to split, and split as far into the m 0's as you want
  
  
  //For 4 digits, the same pattern holds for the left 2 digits, but there is also 
  //extra room to split if you fully split the rightmost 1's completely
  //There are mn+1 ways on the left, times m(n-1)+1 ways to split the right without going all the way, 
  //11001100
  //If we put this in compressed binary, we get
  //a,b,c,d
  //(ab+1)*(d(c-1)+1) + (a(b+1)+1)*(d)
  //(ab+1)*temp1 + (a(b+1)+1)*temp2
  //For number of ways which do not fully split, and then those that do

  int start = bin.size()-1;
  if(bin.size() % 2 == 1)
  {
    start = bin.size()-2;
  }
  unsigned long long notFullyExpanded = 1;
  unsigned long long fullyExpanded = 0;
  while(start > 0)
  {
    unsigned long long temp1 = notFullyExpanded;
    unsigned long long temp2 = fullyExpanded;
    int ones = bin[start-1];
    int zeroes = bin[start];
    fullyExpanded = zeroes*(temp1+temp2) + temp2;
    notFullyExpanded = ((ones-1)*zeroes+1)*temp1 + ((ones-1)*(zeroes+1)+1)*temp2;
    start -= 2;
  }
  return fullyExpanded + notFullyExpanded;
}

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

  math::FastRational goal{123456789, 987654321};
  
  return 0;
}