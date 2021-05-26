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

unsigned long long exp (unsigned long long base, unsigned long long e)
{
  unsigned long long ans = 1;
  for(unsigned long long i = 0; i < e; i++)
  {
    ans *= base; 
  }
  return ans;
}

struct guess
{
  int next;
  unsigned long long sum;
};

int main ()
{
  //Find how many ways you can write 1/2 as the sum of inverse squares, using 
  //numbers from 1/2^2 to 1/80^2, each only used once

  //Basically do educated guessing and checking: 
  //Include 1/4 in the sum, see if it works, and try without it 
  //Which is what the queue is for 

  //However, also note that the numbers used should share some common 
  //factors, otherwise they don't add together nicely 
  //Therefore, we only use numbers with a certain number of 2's, 3's, etc 
  //Had to play around with these values a little bit, but got it to work
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
  int eleven = 0;
  int thirteen = 1;

  unsigned long long denom = exp(2,two)*exp(3,three)*exp(5,five)
  *exp(7,seven)*exp(11,eleven)*exp(13, thirteen);
  denom *= denom;

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

  copy.clear();
  copy = choices;
  for(int i = 1; i <= thirteen; i++)
  {
    for(auto iter = copy.begin(); iter != copy.end(); iter++)
    {
      if(*iter * exp(13,i) <= limit)
      choices.insert(*iter * exp(13,i));
    }
  }
  
  //Used for early termination: 
  //If adding everything else doesn't get you to 1/2, no point in 
  //continuing to try it
  unsigned long long* sumRemaining = (unsigned long long*) calloc(sizeof(unsigned long long), 82);
  sumRemaining[81] = 0;
  for(int i = 80; i >= 2; i--)
  {
    sumRemaining[i] = sumRemaining[i+1];
    if(choices.count(i) != 0)
    {
      sumRemaining[i] += (denom / i / i);
    }
  }
  //Just iterate and try all combinations
  while(!Q.empty())
  {
    guess* curr = Q.front();
    Q.pop();
    if(curr->sum == denom/2)
    {
      num++;
      delete curr;
    }
    //Not one of the numbers with nice factors
    else if(choices.count(curr->next) == 0 && 
    static_cast<unsigned int>(curr->next) != limit+1)
    {
      curr->next++;
      Q.push(curr);
    }
    //Early termination check, if we are already over or 
    //if adding everything else doesn't get us to 1/2, 
    //no point in trying
    else if (curr->sum < denom/2 && 
    curr->sum + sumRemaining[curr->next] >= denom/2
    && static_cast<unsigned int>(curr->next) != limit+1)
    {
      //See if we want to consider a sum without this number, 
      //once again only if we can reach 1/2
      if(curr->sum + sumRemaining[curr->next+1] >= denom/2)
      {
        guess* temp{new guess};
        temp->next = curr->next+1;
        temp->sum = curr->sum;
        Q.push(temp);
      }      
      curr->sum += (denom / curr->next / curr->next);
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