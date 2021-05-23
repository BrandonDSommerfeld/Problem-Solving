#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include <algorithm>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "math_rational.cpp"
#include "algorithms.cpp"

int exp (int base, int e)
{
  int ans = 1;
  for(int i = 0; i < e; i++)
  {
    ans *= base; 
  }
  return ans;
}

struct guess
{
  int next;
  math::Rational sum;
};

int main ()
{
  //Find how many ways you can write 1/2 as the sum of inverse squares, using 
  //numbers from 1/2^2 to 1/80^2, each only used once

 
  std::queue<guess*> Q{};
  guess* start{new guess};
  start->next = 2;
  start->sum = 0;
  Q.push(start);
  int num = 0;

  unsigned int limit = 80;
  int two = 3;
  int three = 2;
  int five = 1;
  int seven = 1;
  int eleven = 1;

  std::set<unsigned long long> choices{};
  choices.insert(1);
  std::set<unsigned long long> copy{choices};
  for(int i = 1; i <= two; i++)
  {
    for(auto iter = copy.begin(); iter != copy.end(); iter++)
    {
      if(*iter * exp(2,i) <= limit)
      choices.insert(*iter * exp(2,i));
    }
  }
  
  copy.clear();
  copy = choices;
  for(int i = 1; i <= three; i++)
  {
    for(auto iter = copy.begin(); iter != copy.end(); iter++)
    {
      if(*iter * exp(3,i) <= limit)
      choices.insert(*iter * exp(3,i));
    }
  }

  copy.clear();
  copy = choices;
  for(int i = 1; i <= five; i++)
  {
    for(auto iter = copy.begin(); iter != copy.end(); iter++)
    {
      if(*iter * exp(5,i) <= limit)
      choices.insert(*iter * exp(5,i));
    }
  }

  copy.clear();
  copy = choices;
  for(int i = 1; i <= seven; i++)
  {
    for(auto iter = copy.begin(); iter != copy.end(); iter++)
    {
      if(*iter * exp(7,i) <= limit)
      choices.insert(*iter * exp(7,i));
    }
  }
  
  copy.clear();
  copy = choices;
  for(int i = 1; i <= eleven; i++)
  {
    for(auto iter = copy.begin(); iter != copy.end(); iter++)
    {
      if(*iter * exp(11,i) <= limit)
      choices.insert(*iter * exp(11,i));
    }
  }
  
  math::Rational* sumRemaining = (math::Rational*) calloc(sizeof(math::Rational), 82);
  sumRemaining[81] = 0;
  for(int i = 80; i >= 2; i--)
  {
    sumRemaining[i] = sumRemaining[i+1];
    if(choices.count(i) != 0)
    {
      //std::cout << i << '\n';
      sumRemaining[i] += math::Rational(1,i*i);
    }
  }
  math::Rational half{1,2};
  int on = 1;
  while(!Q.empty())
  {
    guess* curr = Q.front();
    if(curr->next != on)
    {
      on++;
      std::cout << on << '\n';
    }
    Q.pop();
    if(curr->sum == half)
    {
      num++;
      delete curr;
    }
    else if(choices.count(curr->next) == 0 && 
    static_cast<unsigned int>(curr->next) != limit+1)
    {
      curr->next++;
      Q.push(curr);
    }
    else if (curr->sum < half && 
    curr->sum + sumRemaining[curr->next] >= half
    && static_cast<unsigned int>(curr->next) != limit+1)
    {
      if(curr->sum + sumRemaining[curr->next+1] >= half)
      {
        guess* temp{new guess};
        temp->next = curr->next+1;
        temp->sum = curr->sum;
        Q.push(temp);
      }      
      curr->sum += math::Rational(1, curr->next*curr->next);
      curr->next++;
      Q.push(curr);
    }
    else
    {
      delete curr;
    }
    
  }

  std::cout << num << '\n';
  free(sumRemaining);
  
  return 0;
}