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
  //Find the last 5 digits of 1,000,000,000,000!, excluding the trailing 0's

  unsigned long long limit = 1000000000000ULL;
  unsigned long long ans = 1;
  unsigned long long digit = 100000;
  unsigned long long totient = 40000;

  //We will keep track of powers of 2 and 5 separately, since they cancel each 
  //other to create trailing 0's
  unsigned long long* relativelyPrime = (unsigned long long*) malloc(sizeof(unsigned long long) * totient); 
  unsigned long long current = 0;
  for(unsigned long long i = 1; i < digit; i++)
  {
    if(i % 2 != 0 && i % 5 != 0)
    {
      relativelyPrime[current] = i;
      current++;
    }
  }

  //First of all, we actually only need to consider each factor mod 100,000 since further 
  //digits don't matter
  //Then we note that we actually are looking for (100,000!)^10,000,000
  //But all numbers which are relatively prime to 100,000 will be canceled out 
  //by their inverse

  //Then for numbers which have 1 factor of 2, the non-factor of 2 part 
  //will have its inverse come up later in a later repetition, and since 
  //there are an even number of repetitions everything except for the powers of 2 
  //will cancel cleanly

  //Then we don't need to care about the relatively prime numbers 
  //until the power of 2 does not cleanly divide 10,000,000

  //Same thing for powers of 5, and also numbers which mix powers 
  //of 2 and 5
  unsigned long long pow2 = 0;
  unsigned long long pow5 = 0;
  for(unsigned long long p = 2; p < limit; p *= 2)
  {
    pow2 += limit/p;
    unsigned long long notRepeated = (limit/digit) % p; 
    for(unsigned long long i = 0; p*relativelyPrime[i] < notRepeated*digit; i++)
    {
      ans = (ans * relativelyPrime[i]) % digit;
    }
  }
  for(unsigned long long p = 5; p < limit; p *= 5)
  {
    pow5 += limit/p;
    unsigned long long notRepeated = (limit/digit) % p; 
    for(unsigned long long i = 0; p*relativelyPrime[i] < notRepeated*digit; i++)
    {
      ans = (ans * relativelyPrime[i]) % digit;
    }
  }
  for(unsigned long long two = 2; two < limit; two *= 2)
  {
    for(unsigned long long five = 5; five*two < limit; five *= 5)
    {
      unsigned long long notRepeated = (limit/digit) % (two*five);
      for(unsigned long long i = 0; two*five*relativelyPrime[i] < notRepeated*digit; i++)
      {
        ans = (ans * relativelyPrime[i]) % digit;
      }
    }
  }
  //Finally, add in powers of 2 which are not cancelled by a power of 5
  std::cout << (ans * algorithms::exp(2, pow2-pow5, digit)) % digit << '\n';

  return 0;
}