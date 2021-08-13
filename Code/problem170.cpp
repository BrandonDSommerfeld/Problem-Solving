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

static constexpr unsigned long long limit = 1000000;
static unsigned long long** digits;
unsigned long long* digitCount(unsigned long long num)
{
  unsigned long long* ans = new unsigned long long[10]{};
  while(num > 0)
  {
    ans[num%10]++;
    num /= 10;
  }
  return ans;
}

unsigned long long combine(std::vector<unsigned long long>& nums)
{
  std::vector<unsigned long long> copies{};
  std::vector<unsigned long long> multipliers{};
  std::vector<size_t> indices{};
  for(size_t i = 0; i < nums.size(); i++)
  {
    indices.push_back(i);
    copies.push_back(nums[i]);
    multipliers.push_back(1);
    while(copies[i] > 10)
    {
      multipliers[i] *= 10;
      copies[i] /= 10;
    }
    multipliers[i] *= 10;
  }
  //Selection sort
  for(size_t i = 0; i < nums.size(); i++)
  {
    unsigned long long smallest = copies[i];
    size_t loc = i;
    for(size_t j = i+1; j < nums.size(); j++)
    {
      if(copies[j] < smallest)
      {
        smallest = copies[j];
        loc = j;
      }
    }
    if(loc != i)
    {
      unsigned long long temp = copies[i];
      copies[i] = copies[loc];
      copies[loc] = temp;
      temp = multipliers[i];
      multipliers[i] = multipliers[loc];
      multipliers[loc] = temp;
      size_t temp2 = indices[i];
      indices[i] = indices[loc];
      indices[loc] = temp2;
    }
  }

  unsigned long long ans = 0;
  unsigned long long m = 1;
  for(size_t i = 0; i < nums.size(); i++)
  {
    ans += nums[indices[i]] * m;
    m *= multipliers[i];
  }
  return ans;
}

unsigned long long numDigits(unsigned long long num)
{
  if(num == 0) return 1;
  unsigned long long ans = 0;
  while(num > 0)
  {
    ans++;
    num /= 10;
  }
  return ans;
}

unsigned long long recurse(unsigned long long i, unsigned long long upper, unsigned long long totalDigits,
std::vector<unsigned long long>& nums, std::vector<int>& digitsUsed)
{
  if(totalDigits >= 10) return 0;
  unsigned long long best = 0;
  unsigned long long num = 1;
  //Stop early if we have too many digits, or we exceed the limit
  for(unsigned long long j = 0; j < upper && i*j < limit && totalDigits+num <= 10; j++)
  {
    num = numDigits(j);
    int temp; 
    bool stopNow = true;
    bool keepGoing = true;
    for(int k = 0; k < 10 && (stopNow || keepGoing); k++)
    {
      temp = digitsUsed[k] + digits[j][k];
      if(temp != 1)
      {
        stopNow = false;
      }
      if(temp > 1)
      {
        keepGoing = false;
      }
    }
    if(stopNow)
    {
      for(int k = 0; k < 10 && stopNow; k++)
      {
        temp = digits[i*j][k];
        for(size_t t = 0; t < nums.size(); t++)
        {
          temp += digits[nums[t]][k];
        }
        if(temp != 1)
        {
          stopNow = false;
        }
      }
      if(stopNow)
      {
        std::vector<unsigned long long> copy2{};
        for(size_t k = 0; k < nums.size(); k++)
        {
          copy2.push_back(nums[k]);
        }
        copy2.push_back(i*j);
        unsigned long long temp2 = combine(copy2);
        if(temp2 > best)
        {
          best = temp2;
        }
      }
    }
    if(keepGoing)
    {
      std::vector<unsigned long long> copy2{};
      for(size_t k = 0; k < nums.size(); k++)
      {
        copy2.push_back(nums[k]);
      }
      copy2.push_back(i*j);
      std::vector<int> copy{};
      for(int k = 0; k < 10; k++)
      {
        copy.push_back(digitsUsed[k] + digits[j][k]);
      }
      unsigned long long temp2 = recurse(i, j, totalDigits+num, copy2, copy);
      if(temp2 > best)
      {
        best = temp2;
      }
    }
  }
  return best;
}

int main ()
{
  /*
  Consider the products:
  6 * 1273 = 7638
  6 * 9853 = 59214

  That is, both the right and left hand side us all digits 1-9 exactly once
  This is denoted by concatenating the right side into 763859214

  Find the largest such concatenation that is possible using all digits from 0-9 
  once on both sides of the equation

  There can be more than 2 equations, but the same integer must be the left multiplier in 
  all of them
  */

  digits = new unsigned long long*[limit];
  for(unsigned long long i = 0; i < limit; i++)
  {
    digits[i] = digitCount(i);
  }
  digits[0][0]++;
  unsigned long long best = 0;
  for(unsigned long long i = 3; i < 100; i++)
  {
    unsigned long long num1 = numDigits(i);
    if(i % 11 != 0)
    {
      std::vector<unsigned long long> nums{};
      std::vector<int> digit{};
      for(int j = 0; j < 10; j++)
      {
        digit.push_back(digits[i][j]);
      }
      //Perform a simple recursive search with some optimiziations
      unsigned long long temp = recurse(i, limit, num1, nums, digit);
      if(temp > best)
      {
        best = temp;
      }
    }
  }
  std::cout << best << '\n';
  return 0;
}