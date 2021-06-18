#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include "math_unsigned.h"
#include "math_signed.h"
#include "math_rational.h"
#include "math_fast_rational.h"
#include "algorithms.h"

static constexpr int accuracy = 25;

int repeating(const std::vector<unsigned long long> nums)
{
    for(int start = static_cast<int>(nums.size()) - accuracy; start > 0 && 
    start >= static_cast<int>(nums.size()) - 2*accuracy; start--)
    {
        bool works = true;
        for(int i = 0; i < accuracy && works; i++)
        {
            if(nums[i] != nums[start+i])
            {
                works = false;
            }
        }
        if(works)
        {
            return start;
        }
    }
    return -1;
}

int main ()
{
  //An Ulam sequence starts with 2 numbers, and then each number is the smallest 
  //integer which can be written as the sum of 2 distinct previous numbers in the sequence 
  //in exactly 1 way

  //For the sequences which start with 2,5 , 2,7 , up to 2,21 
  //find the sum of the 10^11th entries in each sequence

  //Had to do some research for this, because I definitely would not have found
  //the answer on my own
  //It was proven that for sequences starting with (2,v) for odd v >= 5, 
  //the successive differences between terms is eventually periodic

  //Furthermore, there are only 2 even terms, which allows me to calculate 
  //enough terms quickly: for v=21, the period is around 2,100,000
  
  //Because of this, the last part is on the slow side
  //Answer is 3916160068885
  
  unsigned long long total = 0;
  unsigned long long goal = 100000000000ULL;
  for(unsigned long long v = 5; v <= 21; v += 2)
  {
    //Second even term is v + (v+2)
    unsigned long long even = 2*v+2;
    std::vector<unsigned long long> differences{};
    unsigned long long sum = 0;
    //The starting differences between odd terms.
    //Until we get to the second even number, all odds are included, 
    //so that many 2's
    for(unsigned long long i = v+2; i < even; i += 2)
    {
      differences.push_back(2);
      sum += 2;
    }
    size_t last = 0;
    int loc = -1;
    unsigned long long t = 0;
    //Until we find a repeating string of digits
    while(loc == -1)
    {
      //We would like the next difference to be 2, unless there is a number 
      //which is even back, in which case there are 2 ways to make the number
      unsigned long long next = 2;
      //If there are 2 ways, then the next number is the next one which can be 
      //made with even, since we can't make things with 2 anymore
      //Thus, we check how far back the next number is
      if(sum + next == even)
      {
        sum -= differences[last];
        last++;
        next = even-sum;
      }
      differences.push_back(next);
      //Sum attempts to stay as close to even as possible while being below it, 
      //so that we can track if the next number has one which is even below it
      sum += next;
      while(sum >= even)
      {
        sum -= differences[last];
        last++;
      }
      //Only check for repeating digits rarely, since it is expensive
      t++;
      if(t % accuracy == 0)
      {
         loc = repeating(differences);
      }
    }
    //Find the total length of the repeating portion
    unsigned long long period = 0;
    for(int i = 0; i < loc; i++)
    {
      period += differences[i];
    }
    
    unsigned long long repetitions = goal/loc;
    unsigned long long guess = v + period*repetitions;
    //The +3 and the following loop account for the 2 even terms, 
    //and the fact that we start counting at 1, not 0
    for(unsigned long long i = 0; i+3 < goal-(repetitions*loc); i++)
    {
      guess += differences[i];
    }
    for(unsigned long long i = 3; i > goal-repetitions*loc; i--)
    {
      guess -= differences[loc - 1 - (3-i)];
    }
    total += guess;
    std::cout << total << '\n';
  }
  std::cout << total << '\n';
  
  return 0;
}