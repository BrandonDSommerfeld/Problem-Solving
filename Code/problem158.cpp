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

math::Unsigned permutations (unsigned long long length, unsigned long long current,
unsigned int* nums)
{
  if(current == length)
  {
    return 1;
  }
  math::Unsigned total = 0;
  for(unsigned int i = 0; i < length; i++)
  {
    //Make sure i has not already been used
    bool works = true;
    for(unsigned int j = 0; j < current && works; j++)
    {
      if(nums[j] == i) works = false;
    }
    if(works)
    {
      //Case: we are placing the one letter which comes before its neighbor
      if(current != 0 && i < nums[current-1])
      {
        //If this is a valid placement, we add one because the rest of the 
        //letters have to be in order

        //This is only valid if the smallest remaining letter comes after i, 
        //because otherwise we would have a second out of order letter
        //Thus, we check that every number below i is used
        bool* works2 = (bool*) calloc(sizeof(bool), i);
        for(unsigned int j = 0; j < current-1; j++)
        {
          if(nums[j] < i) works2[nums[j]] = true;
        }
        works = true;
        for(unsigned int j = 0; j < i; j++)
        {
          if(!works2[j]) works = false;
        }
        free(works2);
        if(works) total++;
      }
      else
      {
        nums[current] = i;
        total += permutations(length, current+1, nums);
      }
    }
  }
  return total;
}

int main ()
{
  //Consider strings of distinct characters, like 'abc'
  //In this string, every letter comes after its neighbor to the left
  //We are interested in strings which have exactly one letter come 
  //after its left neighbor, like 'bac'
  //Find the length which has the most such strings, and find that number of strings
  

  //This takes a while to run, thus the print statement to see the 
  //progress, because the best occurs at 18 pretty quickly, but then 
  //my function above takes a while for the larger numbers, 
  //But you can still quickly see the best
  math::Unsigned best = 0;
  for(unsigned long long i = 2; i <= 26; i++)
  {
    math::Unsigned c = algorithms::choose(26, i);
    unsigned int* temp = (unsigned int*) calloc(sizeof(unsigned int), i);
    //Subtract one because the function above counts the in order 
    //word with 0 out of place letters, even though it shouldn't
    math::Unsigned current = c * (permutations(i, 0, temp) - 1);
    free(temp);
    if(current > best)
    {
      best = current;
    }
    std::cout << i << ' ' << best << '\n';
  }
  std::cout << best << '\n';
  return 0;
}