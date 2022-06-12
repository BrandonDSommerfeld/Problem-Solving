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

unsigned long long numDivisors(const std::vector<int>& powers)
{
	unsigned long long ans = 1;
	for(size_t i = 0; i < powers.size(); i++)
	{
		ans *= (powers[i] + 1);
	}
	return ans;
}

int main ()
{
	//How many numbers n from 1 to 10^7 exclusive have the same number of divisors as n+1
	//Just look at prime factorization, and the powers of the primes to calculate 
	//the number of divisors

	algorithms::generatePrimes(10000);
	constexpr unsigned long long limit = 10000000;
	unsigned long long *divisors = static_cast<unsigned long long*>(malloc(sizeof(unsigned long long) * limit));
	for(unsigned long long i = 2; i < limit; i++)
	{
		std::vector<int> temp{};
		unsigned long long copy = i;
		for(unsigned long long j = 0; j < algorithms::primes.size() && algorithms::primes[j]*algorithms::primes[j] <= copy; j++)
		{
			int count = 0;
			while(copy % algorithms::primes[j] == 0)
			{
				copy /= algorithms::primes[j];
				count++;
			}
			if(count != 0)
			{
				temp.push_back(count);
			}
		}
		if(copy != 1)
		{
			temp.push_back(1);
		}
		divisors[i] = numDivisors(temp);
	}

	unsigned long long ans{0};	
	for(unsigned long long i = 2; i < limit-1; i++)
	{
		if(divisors[i] == divisors[i+1]) ans++;
	}
	std::cout << ans << '\n';
	return 0;
}