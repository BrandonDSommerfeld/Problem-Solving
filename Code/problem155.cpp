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

int main ()
{
  //Given 18 capacitors with the same capacitance, 
  //how many different capacitances can you create by 
  //placing them in series or in parallel? 
  //Note that you don't need to use all of them

  unsigned long long limit = 18;
  //Holds the different values using that many or less capacitors
  std::set<math::FastRational>* possible{new std::set<math::FastRational>[limit+1]};
  possible[0].insert(0);
  for(size_t i = 1; i <= limit; i++)
  {
    //Basic configuration of putting all in series or all in parallel
    possible[i].insert(i);
    possible[i].insert(math::FastRational(1,i));
    //Iterate over all ways to connect 2 smaller circuits 
    //to create a bigger one
    for(size_t j = 1; j <= i/2; j++)
    {
      for(auto iter = possible[i-j].begin(); iter != possible[i-j].end(); iter++)
      {
        //Carry over smaller circuits for counting purposes
        possible[i].insert(*iter);
        for(auto iter2 = possible[j].begin(); iter2 != possible[j].end(); iter2++)
        {
          possible[i].insert(*iter2);
          //Combine the circuits in series or in parallel
          possible[i].insert(*iter + *iter2);
          possible[i].insert(1 / ((1/ *iter) + (1 / *iter2)));
        }
      }
    }
  }
  std::cout << possible[limit].size() << '\n';
  delete[] possible;
  return 0;
}