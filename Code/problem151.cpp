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
#include "algorithms.cpp"

struct P
{
  math::Rational probability;
  std::vector<int> sizes;
};

bool same_list (const std::vector<int>& list1, const std::vector<int>& list2)
{
  if(list1.size() != list2.size()) return false;
  int* count1 = (int*) calloc(sizeof(int),5);
  int* count2 = (int*) calloc(sizeof(int),5);
  for(int i = 0; i < list1.size(); i++)
  {
    count1[list1[i]]++;
    count2[list2[i]]++;
  }
  for(int i = 0; i < 5; i++)
  {
    if(count1[i] != count2[i])
    {
      free(count1);
      free(count2);
      return false;
    }
  }
  free(count1);
  free(count2);
  return true;

}

int main ()
{
  //A person places a piece of paper into a bag
  //Throughout the week, they take a piece of paper at random, 
  //and if it is 1/16 of the paper it is used, otherwise the 
  //picked paper is cut in half, and then one of those halves is 
  //cut until you get 1/16, and the leftovers go back in the bag for later 
  
  //Find the expected number of times, excluding the first day 
  //when there is just the sheet, and the last time when there is just 
  //1/16 left, that they reach into the bag and there is only a single 
  //piece of paper remaining.

  math::Rational expected{};

  std::vector<P> possibilities{};
  P start{};
  start.probability = 1;
  start.sizes.push_back(1);
  possibilities.push_back(start);
  //Stop early to not count the last draw
  //Literally just simulate all possible ways to draw 
  //a piece of paper, and keep track of the probability 
  //of each configuration occurring
  for(int i = 0; i < 14; i++)
  {
    std::vector<P> next{};
    for(int j = 0; j < possibilities.size(); j++)
    {
      P current = possibilities[j];
      for(int k = 0; k < current.sizes.size(); k++)
      {
        P temp{};
        for(int a = 0; a < current.sizes.size(); a++)
        {
          if(a != k) temp.sizes.push_back(current.sizes[a]);
        }
        int t = current.sizes[k];
        while(t < 5)
        {
          t++;
          temp.sizes.push_back(t);
        }
        temp.probability = current.probability*(math::Rational(1,current.sizes.size()));

        bool found = false;
        for(int a = 0; a < next.size(); a++)
        {
          if(same_list(next[a].sizes, temp.sizes))
          {
            next[a].probability += temp.probability;
            found = true;
          }
        }
        if(!found)
        {
          next.push_back(temp);
        }
      }
    }
    possibilities = next;
    for(int j = 0; j < possibilities.size(); j++)
    {
      if(possibilities[j].sizes.size() == 1 && i != 15)
      {
        expected += possibilities[j].probability;
      }
    }
  }
  std::cout << expected << '\n';
  //Wolfram alpha was used to turn this into a decimal approximation, 
  //because at this point I am too lazy to write such a function for myself
  return 0;
}