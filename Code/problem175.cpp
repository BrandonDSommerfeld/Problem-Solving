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
#include <set>
#include "math_unsigned.h"
#include "math_signed.h"
#include "math_rational.h"
#include "math_fast_rational.h"
#include "algorithms.h"

/*
Number is stored backwards with small digits on left side, 
side that allows for easily adding digits on to the right side later
*/
std::string binary(unsigned long long num)
{
  std::string ans{};
  while(num > 0)
  {
    if(num % 2 == 0)
    {
      ans += "0";
    }
    else
    {
      ans += "1";
    }
    num /= 2;
  }
  return ans;
}

std::vector<int> compressedBinary(const std::string& s)
{
  int num{0};
  char last{'2'};
  std::vector<int> ans{};
  for(size_t i{0}; i < s.length(); i++)
  {
    if(s[i] == last)
    {
      num++;
    }
    else 
    {
      if(last != '2')
      {
        ans.push_back(num);
      }
      num = 1;
      last = s[i];
    }
  }
  ans.push_back(num);
  return ans;
}

math::Unsigned compressedBinaryToWays(const std::vector<int>& bin)
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
  
  size_t start{0};
  if(bin.size() % 2 == 1)
  {
    start = 1;
  }
  math::Unsigned notFullyExpanded{1};
  math::Unsigned fullyExpanded{0};
  while(start < bin.size())
  {
    math::Unsigned temp1 = notFullyExpanded;
    math::Unsigned temp2 = fullyExpanded;
    int ones = bin[start+1];
    int zeroes = bin[start];
    fullyExpanded = zeroes*(temp1+temp2) + temp2;
    notFullyExpanded = ((ones-1)*zeroes+1)*temp1 + ((ones-1)*(zeroes+1)+1)*temp2;
    start += 2;
  }
  return fullyExpanded + notFullyExpanded;
}

math::Rational abs(math::Rational num)
{
  if(num < 0) return -num;
  return num;
}

/*
Calculates the fraction of expressions of num which use 1's, 
which is precisely how many ways that num+1 can be represented
Same formula for expansion as above function

One very important note is that by adding more digits onto the 
end of the number, the ratio only ever decreases
*/  
math::Rational ratio(std::vector<int> num)
{
  if(num.size() % 2 == 1)
  {
    std::cout << "Odd number in ratio\n";
    return math::Rational{-1,1};
  }
  math::Unsigned fullyExpandedWith1{1};
  math::Unsigned notFullyExpandedWith1{num[1]-1};
  math::Unsigned fullyExpandedWithout1{num[0]-1};
  math::Unsigned notFullyExpandedWithout1{(num[1]-1)*(num[0]-1)+1};

  for(size_t i = 2; i < num.size(); i += 2)
  {
    int zeroes = num[i];
    int ones = num[i+1];
    math::Unsigned temp1 = notFullyExpandedWith1;
    math::Unsigned temp2 = fullyExpandedWith1;
    math::Unsigned temp3 = notFullyExpandedWithout1;
    math::Unsigned temp4 = fullyExpandedWithout1;
    fullyExpandedWith1 = zeroes*(temp1+temp2) + temp2;
    notFullyExpandedWith1 = ((ones-1)*zeroes + 1)*temp1 + ((ones-1)*(zeroes+1)+1)*temp2;
    fullyExpandedWithout1 = zeroes*(temp3+temp4) + temp4;
    notFullyExpandedWithout1 = ((ones-1)*zeroes + 1)*temp3 + ((ones-1)*(zeroes+1)+1)*temp4; 
  }
  math::Rational ans{fullyExpandedWithout1 + notFullyExpandedWithout1,
   fullyExpandedWith1+notFullyExpandedWith1+fullyExpandedWithout1+notFullyExpandedWithout1};
  return ans;
}

math::Rational continuedFraction(std::vector<int> num)
{
  math::Rational ans{0,1};
  for(size_t i = num.size() - 1; i > 0; i--)
  {
    ans = 1/(num[i] + ans);
  }
  ans = 1/(num[0] + ans);
  return ans;
  //1,1 : 1/2
  //1,2 : 2/3
  //2,1 : 1/3
  //1,3 : 3/4
  //3,1 : 1/4
  //1,4 : 4/5
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

  //The ratios converge as you add more digits, like a continued fraction
  //Ratio is 1- the continued fraction for some reason
  
  math::Rational goal{123456789,987654321};
  math::Rational create{1-goal}; 
  std::vector<int> frac{};
  while(create > 0)
  {
    math::Signed num = create.get_numerator();
    math::Signed denom = create.get_denominator();
    int digit = (denom/num).to_int();
    frac.push_back(digit);
    create = math::Rational(denom,num) - digit;
  }
  frac[frac.size()-1]--;
  frac.push_back(1);
  for(size_t i = frac.size()-1; i > 0; i--)
  {
    std::cout << frac[i] << ',';
  }
  std::cout << frac[0] << '\n';
  std::cout << ratio(frac) << ' ' << continuedFraction(frac) << '\n';
  std::cout << goal << '\n';

  std::cout << compressedBinaryToWays(frac) << '\n';
  std::vector<int> one{};
  one.push_back(8);
  one.push_back(13717420);
  one.push_back(1);
  std::cout << compressedBinaryToWays(one) << '\n';
  //The answer is the value of one
  return 0;
}