#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include <map>
#include <utility>
#include <set>
#include "math_unsigned.h"
#include "math_signed.h"
#include "math_rational.h"
#include "math_fast_rational.h"
#include "algorithms.h"

unsigned long long denomLimit = 100000000;
unsigned long long upperDenom = 100;

unsigned long long count (unsigned long long num1, unsigned long long denom1,
						  unsigned long long num2, unsigned long long denom2, 
						  unsigned long long accum)
{
	if(2*denom1*denom2 > denomLimit) return accum;
	if(num1*100 > denom1) return accum;
	unsigned long long mediantNum = num1 + num2;
	unsigned long long mediantDenom = denom1 + denom2;

	unsigned long long add = (num1*denom2 + num2*denom1)*100 < 2*denom1*denom2 ? 1 : 0;
	if(denom1*mediantDenom*2 > denomLimit)
	{
		return count(mediantNum, mediantDenom, num2, denom2, accum + add);
	}
	return count(num1,denom1,mediantNum,mediantDenom, count(mediantNum,mediantDenom, num2, denom2, accum + add));	
}

int main ()
{
	//See problem 192 for the definition of best rational approximation for a given denominator bound
	//We call a number ambiguous if for a given bound, there are 2 rationals, one above and one below, 
	//which are both the best rational approximation for that bound
	//Find how many ambiguous numbers 0 < x < 1/100 exist with denominators <= 10^8

	//As noted in problem 192, best approximations can be computed from the continued 
	//fraction of the number, so we just check that for being ambiguous 

	//Use the Farey sequence: start with 0/1 and 1/1, and for each pair repeatedly take the 
	//mediant as a/b and c/d adds in (a+c)/(b+d)
	//This creates fractions in increasing denominator order
	//In this sequence, mean always has denominator 2bd and 
	//Mediant never reduces, just store num and denom so not doing gcd to reduce
	//Then we just use a recursive function to generate mediants and take means
	//Structured tail recursively with an accumulator because it can make a LOT 
	//of recursive calls in 1 direction, so would get stack overflow otherwisegg
	std::cout << count(0,1,1,1,0) << '\n';
	return 0;
}