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
  //Consider making a Pascal's triangle like shape using pseudorandom numbers
  //Then find the subtriangle which has the minimum sum, where a subtriangle 
  //takes any number, and the 2 below it, and the 3 below those, for as many layers 
  //as you want

  //Random numbers:
  //t = 0
  //t = (615949*t + 797807) mod 2^20
  //s(k) = t - 2^19

  long long limit = 1000;
  long long* triangle =  (long long*) malloc(sizeof(long long) * limit * limit);

  long long t = 0;
  for(int i = 0; i < 1000; i++)
  {
    for(int j = 0; j <= i; j++)
    {
      t = (615949*t+797807) % (1 << 20);
      triangle[i*limit+j] = (t - (1 << 19));
    }
  }
  

  //For each side of the triangle, look at it and see if 
  //it is worth removing. Also gradually increase the offset, 
  //potentially shaving off 2 or more rows at a time if 
  //they have a positive sum overall
  //Have to be careful to go around the triangle, considering 
  //1, then 2, then 3 rows removed, you can't just remove 
  //any row which is positive because sometimes 
  //other removals make that first removal a bad idea
  int top = 0;
  int left = 0;
  int bottom = limit-1;
  int right = limit-1;
  bool changed = true;
  while(changed)
  {
    changed = false;
    for(int offset = 0; offset <= right-left; offset++)
    {
      long long leftSum = 0;
      for(int i = 0; i <= offset; i++)
      {
      for(int row = top+i; row <= bottom; row++)
      {
        leftSum += triangle[row*limit+left+i];
      }
      }
      long long rightSum = 0;
      for(int i = 0; i <= offset; i++)
      {
      for(int col = right-i; col >= left; col--)
      {
        rightSum += triangle[(bottom-i)*limit+col];
      }
      }      
      long long sum = 0;
      for(int i = 0; i <= offset; i++)
      {
      for(int along = 0; along <= bottom-top-i; along++)
      {
        sum += triangle[(top+along+i)*limit+along+left];
      }
      }
      if(sum > 0 && sum >= leftSum && sum >= rightSum)
      {
        changed = true;
        top = top+offset+1;
        right = right-offset-1;
        break;
      }
      if(leftSum > 0 && leftSum >= sum && leftSum >= rightSum)
      {
        changed = true;
        top = top+offset+1;
        left = left+offset+1;
        break;
      }
      if(rightSum > 0 && rightSum >= sum && rightSum >= leftSum)
      {
        changed = true;
        bottom = bottom-offset-1;
        right = right-offset-1;
        break;
      }


    }
  }    

  long long best = 0;
  std::cout << top << ' ' << bottom << ' ' << left << ' ' << right << '\n';
  for(int row = top; row <= bottom; row++)
  {
    for(int col = left; col <= left + row - top; col++)
    {
      best += triangle[row*limit+col];
    }
  }
  std::cout << best << '\n';
  return 0;
}