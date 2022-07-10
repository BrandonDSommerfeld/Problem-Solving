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

static constexpr unsigned long long limit = 1ULL << 50;
static constexpr unsigned long long s = 1ULL << 25;

unsigned long long helper(unsigned long long num, size_t start, unsigned long long val)
{
	if(val >= limit) return 0;
	if(num == 0) 
	{
		return limit/val;
	}
	if(start >= algorithms::primes.size()) return 0;
	unsigned long long ans = 0;
	for(size_t i = start; i < algorithms::primes.size(); i++)
	{
		unsigned long long temp = helper(num-1, i+1, val*algorithms::primes[i]*algorithms::primes[i]);
		if(temp == 0) return ans;
		ans += temp;
	}
	return ans;
}

unsigned long long choose(unsigned long long num)
{
	return helper(num, 0, 1);
}

int main ()
{
	//How many numbers below 2^50 are not divisible by the square of any prime number?
	//Use the principle of inclusion-exclusion to remove numbers divisible by 1 prime square,
	//add back in those divisible by 2, remove 3, and so on
	algorithms::generatePrimes(s);
	unsigned long long ans = limit;
	bool subtract = true;
	unsigned long long val = 1;
	unsigned long long num = 1;
	while(val != 0)
	{
		val = choose(num);
		if(subtract)
		{
			ans -= val;
		}
		else 
		{
			ans += val;
		}
		subtract = !subtract;
		num++;
	}
	std::cout << ans << '\n';
	return 0;
}