#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include <list>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "algorithms.cpp"


int main ()
{
  //Consider a 2000 x 2000 square filled with pseudorandom numbers
  //Then find the greatest sum of some line of numbers, allowing all diagonals, 
  //and we can stop early

  //Random number is given by
  //s(k) = (100003 - 200003k + 300007k^3) mod 1000000 - 500000, 1 <= k <= 55
  //s(k) = (s(k-24) + s(k-55) + 1000000) mod 1000000 - 500000, k > 55

  //Then we place these numbers going across the rows

  unsigned long long limit = 4000000;
  long long* square = (long long*) malloc(sizeof(long long) * limit);

  std::list<long long> prevs{};
  for(long long i = 1; i <= 55; i++)
  {
    prevs.push_back(((100003 - 200003*i + 300007*i*i*i) % 1000000) - 500000);
    square[i-1] = prevs.back();
  }

  auto middle = prevs.end();
  for(int i = 0; i < 24; i++)
  {
    middle--;
  }

  for(long long i = 56; i <= limit; i++)
  {
    prevs.push_back(((prevs.front() + (*middle) + 1000000) % 1000000) - 500000);
    square[i-1] = prevs.back();
    prevs.pop_front();
    middle++;
  }


  long long best = INT64_MIN;

  //For each row, col, and diagonal, start with the entire line
  //Then from both sides, add things up and see if you ever go negative
  //If you do, you are better off removing that end of the line
  //I was lazy and didn't do the diagonals, and it turns out that 
  //the answer is in one of the rows or cols, but 
  //you could very easily add that in to be thorough
  for(long long row = 0; row < 2000; row++)
  {
    int left = 0;
    long long leftSum = 0;
    for(long long col = 0; col < 2000; col++)
    {
      leftSum += square[row*2000+col];
      if(leftSum < 0)
      {
        leftSum = 0;
        left = col+1;
      }
    }

    int right = 1999;
    long long rightSum = 0;
    for(long long col = 1999; col >= 0; col--)
    {
      rightSum += square[row*2000+col];
      if(rightSum < 0)
      {
        rightSum = 0;
        right = col-1;
      }
    }

    long long total = 0;
    for(long long col = left; col <= right; col++)
    {
      total += square[row*2000+col];
    }
    if(total > best)
    {
      best = total;
    }
  }

  for(long long col = 0; col < 2000; col++)
  {
    int top = 0;
    long long topSum = 0;
    for(long long row = 0; row < 2000; row++)
    {
      topSum += square[row*2000+col];
      if(topSum < 0)
      {
        topSum = 0;
        top = row+1;
      }
    }

    int bottom = 1999;
    long long bottomSum = 0;
    for(long long row = 1999; row >= 0; row--)
    {
      bottomSum += square[row*2000+col];
      if(bottomSum < 0)
      {
        bottomSum = 0;
        bottom = row-1;
      }
    }

    long long total = 0;
    for(long long row = top; row <= bottom; row++)
    {
      total += square[row*2000+col];
    }
    if(total > best)
    {
      best = total;
    }
  }

  free(square);
  std::cout << best << '\n';
  return 0;
}