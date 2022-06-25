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

unsigned long long hyper(unsigned long long base, unsigned long long exp, unsigned long long mod)
{
	if(exp == 1) return base;
	if(base == 0) return 0;
	if(base == 1) return 1;
	//If not in an easy case, just take the exponent mod the totient 
	//since raising to the totient always gives 1
	if(algorithms::gcd(base,mod) == 1) return algorithms::exp(base, hyper(base, exp-1, algorithms::totient(mod)), mod);
	return 0;
}

int main ()
{
	//Define the hyperexponentation of a number by 
	//a**1 = a
	//a**k = a^(a**(k-1))
	//Find the last 8 digits of 1777**1855
	algorithms::generatePrimes(1000000);
	unsigned long long mod = 100000000;
	unsigned long long base = 1777;
	unsigned long long exp = 1855;
	std::cout << hyper(base,exp,mod) << '\n';	
	return 0;
}