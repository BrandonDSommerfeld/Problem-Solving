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

unsigned long long search (unsigned long long lowerBound, unsigned long long lowerCount,
unsigned long long upperBound, unsigned long long upperCount, 
unsigned long long toAdd, int prevNumDigit, int digit, int pow)
{
  //std::cout << lowerBound << ' ' << lowerCount << ' ' << upperBound << ' ' << upperCount << '\n';
  //Search between the upper and lower bound for places where the count is equal to 
  //them recursively, starting from the leftmost digit, and narrowing in
  unsigned long long total = 0;
  
  if(lowerBound == upperBound-1)
  {
    if(lowerCount == lowerBound)
    {
      total += lowerBound;
    }
    return total;
  }
  
  //Only search if between the upper and lower bound we either go from 
  //overcounting to undercounting, or the other way around
  if((lowerCount <= lowerBound && upperCount >= upperBound)
  || (lowerCount >= lowerBound && upperCount <= upperBound))
  {
    //Figure out the next digit of the number
    for(int i = 0; i < 10; i++)
    {
      //Special case, need to add more stuff in this case
      if(i == digit)
      {
        unsigned long long newLowerBound = lowerBound + i*toAdd;
        //All i*toAdd numbers we are skipping over have prevNumDigit occurences
        //For the right digits, 1/10 of the numbers we skip have the digit we want, 
        //Once again there are i*toAdd such numbers, and we take 1/10, and pow is the 
        //number of such digits
        //Finally, we add 1 because we are currently at i==digit, which is an extra occurrence
        unsigned long long newLowerCount = lowerCount+i*(prevNumDigit*toAdd) + i*(toAdd / 10)*pow+1;
        unsigned long long newUpperBound = newLowerBound + toAdd;
        //The prevNumDigit and pow parts are the same as above
        //The extra toAdd is because i==digit, so all toAdd numbers have an 
        //extra occurence of the digit
        //Subtract 1 because we already counted 1 of those occurences of the digit 
        //in the current position with the +1 above
        unsigned long long newUpperCount = newLowerCount + 
        prevNumDigit*toAdd + (toAdd/10)*pow+toAdd-1;
        total += search(newLowerBound, newLowerCount, newUpperBound, newUpperCount,
        toAdd/10, prevNumDigit+1, digit, pow-1);           
      }
      else
      {
        unsigned long long newLowerBound = lowerBound + i*toAdd;
        unsigned long long newLowerCount = lowerCount+i*(prevNumDigit*toAdd) + i*(toAdd / 10)*pow;
        //Add in extra occurences when i was digit
        if(i > digit)
        {
          newLowerCount += toAdd;
        }
        unsigned long long newUpperBound = newLowerBound + toAdd;
        unsigned long long newUpperCount = newLowerCount+prevNumDigit*toAdd+(toAdd/10)*pow;
        //If the upper bound has digit occur in the current position, that is 
        //an extra 1 occurence for it
        if(i == digit-1)
        {
          newUpperCount++;
        }
        total += search(newLowerBound, newLowerCount, newUpperBound, newUpperCount,
        toAdd/10, prevNumDigit, digit, pow-1);           
      }
    }
  }
  return total;
}

unsigned long long count (int digit)
{
  return search(0, 0, 1000000000000ULL, 1200000000001ULL, 100000000000ULL, 0, digit, 11);
}

int main ()
{
  //Consider counting how many times a digit appears
  //For the digit 1, it appears 1 time at 1, 1 time in 10, 2 times at 11, 
  //then another at 12-19, and then again at 21, and so on

  //Consider counting the total number of 1's which have occurred:
  //This would go 1,2,4,5,6,... in the above example
  //Find the sum of all numbers where the number of 1's in numbers below or equal to it 
  //is equal to that number.
  //Furthermore, actually do this for all digits 1-9, and sum all of those numbers
  //If a number works for multiple digits, add it each time
  
  unsigned long long total = 0;
  for(int i = 1; i < 10; i++)
  {
    total += count(i);
  }
  std::cout << total << '\n';
  return 0;
}