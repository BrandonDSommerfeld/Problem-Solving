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

  //In particular, it was proven that the largest period is for 21, with about 2,100,000 terms
  //before it repeats itself

  //Thus, for each sequence compute enough terms to find this period, and just 
  //extrapolate out to the 10^11th entry
  return 0;
}