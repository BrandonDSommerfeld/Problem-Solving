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

std::vector<int>* reachGoal (unsigned long long goal, int* best, int total, 
std::vector<int> working)
{
  unsigned long long curr = compressedBinaryToWays(working);
  if(curr == goal)
  {
    std::vector<int>* res = new std::vector<int>;
    *res = working;
    return res;
  }
  if(curr > goal)
  {
    return NULL;
  }

  working.push_back(1);
  working.push_back(1);
  for(int combined = 2; compressedBinaryToWays(working) <= goal && combined+total <= *best; combined++)
  {
    for(int first = 1; first < combined; first++)
    {
      working[working.size()-2] = first;
      working[working.size()-1] = combined-first;
      std::vector<int>* res = reachGoal(goal, best, total+combined, working);
      if(res != NULL)
      {
        for(size_t i = 0; i+1 < res->size(); i++)
        {
          std::cout << (*res)[i] << ',';
        }
        std::cout << (*res)[res->size()-1] << '\n';
        return res;
      }
    }
  }
  return NULL;
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
  
  /*
  math::FastRational goal{123456789, 987654321};
  for(int i = 0; i < 100; i++)
  {
    std::vector<int> temp = compressedBinary(algorithms::binary(i));
    for(size_t j = 0; j+1 < temp.size(); j++)
    {
      std::cout << temp[j] << ',';
    }
    if(temp.size() > 0)
    {
      std::cout << temp[temp.size()-1];
    }
    std::cout << ' ' << compressedBinaryToWays(temp) << '\n';
  }

  */ 
  /*
  Relationship between f(n-1) and f(n) depends on how many expansions of f(n-1)
  are not full
  For example, 10 has
  8+2
  8+1+1
  4+4+2
  4+2+2+1+1

  11: 1011
  8+2+1
  4+4+2+1
  Each expansion where the 2nd to last 1's are not fully expanded has n combinations,
  and those that are fully expanded have n-1
  
  8+4
  8+2+2
  8+2+1+1
  4+4+2+2
  4+4+2+1+1

  Every expansion with less than 2 1's can just have a 1 added to it
  Futhermore, as long as there is only a single one of each power, they can be combined
  For example, 4+2+1+1 can become 4+2+2 or 4+4, depending on how far you combine
  The number of such trailing single powers depends on the trailing 1's in the binary expansion
  */

  int* temp = new int{};
  *temp = 20;
  std::vector<int> temp2{};
  reachGoal(17, temp, 0, temp2);
  return 0;
}