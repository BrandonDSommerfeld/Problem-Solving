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

int main ()
{
	//How many numbers below 10^8 have exactly 2 prime factors, not necessarily distinct?
	//Just generate primes and look at all ways to multiply them together
	unsigned long long limit = 100000000;
	bool *twoFactors = static_cast<bool*>(calloc(sizeof(bool), limit));
	algorithms::generatePrimes(limit/2);
	for(size_t i = 0; i < algorithms::primes.size(); i++)
	{
		for(size_t j = i; j < algorithms::primes.size() && algorithms::primes[i]*algorithms::primes[j] < limit; j++)
		{
			twoFactors[algorithms::primes[i]*algorithms::primes[j]] = true;
		}
	}
	unsigned long long ans = 0;
	for(unsigned long long i = 0; i < limit; i++)
	{
		if(twoFactors[i])
		{
			ans++;
		}
	}
	std::cout << ans << '\n';
	free(twoFactors);
	return 0;
}