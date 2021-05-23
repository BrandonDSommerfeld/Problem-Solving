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

struct guess
{
  int next;
  math::Rational sum;
};

int main ()
{
  //Find how many ways you can write 1/2 as the sum of inverse squares, using 
  //numbers from 1/2^2 to 1/80^2, each only used once
  
  //Used for early termination, if adding the rest will not get to 
  // 1/2, lookup table for efficiency
  math::Rational* sumRemaining = (math::Rational*) calloc(sizeof(math::Rational),82);
  sumRemaining[81] = 0;
  for(int i = 80; i >= 2; i--)
  {
    sumRemaining[i] = sumRemaining[i+1];
    sumRemaining[i] += math::Rational(1, i*i);
  }
  std::queue<guess*> Q{};
  guess* start = (guess*) calloc(sizeof(guess), 1);
  start->next = 2;
  start->sum = 0;
  int num = 0;
  Q.push(start);
  int on = 1;
  algorithms::generatePrimes(100);
  while(!Q.empty())
  {
    guess* curr = Q.front();
    if(curr->next != on)
    {
      on = curr->next;
      std::cout << on << '\n';
    }
    Q.pop();
    if(curr->sum == math::Rational(1,2))
    {
      num++;
    }
    else if ((curr->next > 15 && algorithms::isPrime(curr->next)) || curr->next % 11 == 0 || 
    curr->next % 13 == 0 || curr->next % 17 == 0 || curr->next % 19 == 0 
    || curr->next % 23 == 0 || curr->next % 29 == 0 || curr->next % 31 == 0 
    || curr->next % 37 == 0)
    {
       guess* temp2 = (guess*) calloc(sizeof(guess), 1);
       temp2->next = curr->next+1;
       temp2->sum = curr->sum;
       Q.push(temp2);
    }
    else if (curr->sum + sumRemaining[curr->next] > math::Rational(1,2)
    && curr->next != 81)
    {
      guess* temp1 = (guess*) calloc(sizeof(guess), 1);
      temp1->next = curr->next+1;
      temp1->sum = curr->sum + math::Rational(1,curr->next*curr->next);
      Q.push(temp1);

      if(curr->sum + sumRemaining[curr->next+1] >= math::Rational(1,2))
      {
        guess* temp2 = (guess*) calloc(sizeof(guess), 1);
        temp2->next = curr->next+1;
        temp2->sum = curr->sum;
        Q.push(temp2);
      }
    }
    free(curr);
  }
  free(sumRemaining);
  std::cout << num << '\n';
  return 0;
}