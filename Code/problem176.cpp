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

struct contain
{
	std::vector<int> primePowers;
};

unsigned long long val (const struct contain& x)
{
	unsigned long long ans = 1;
	for(size_t i = 0; i < x.primePowers.size(); i++)
	{
		ans *= algorithms::exp(algorithms::primes[i], static_cast<unsigned long long>(x.primePowers[i]));
	}
	return ans;
}

bool operator< (const struct contain& x, const struct contain& y)
{
	return val(x) > val(y);
}

unsigned long long choose (std::vector<int> primePowers, size_t pick, size_t start, unsigned long long accum)
{
	if(pick == 0) return accum;
	unsigned long long ans = 0;
	for(size_t i = start; i < primePowers.size(); i++)
	{
		if(primePowers[i] != 0)
		{
			if(i == 0)
			{
				if(primePowers[i] > 1)
				{
					ans += choose(primePowers, pick-1, i+1, accum*(primePowers[i]-1));
				}
			}
			else
			{
				ans += choose(primePowers, pick-1, i+1, accum*primePowers[i]);
			}
		}
	}
	return ans;
}

/*
Fundamentally, if we have a primitive triple 
x^2+y^2=z^2, then 
x=2st and y=s^2-t^2
for s,t with gcd 1. Therefore, the number of 
primitive triples a number is in depends on how many 
prime factors it has, since that gives the ways to factor 
it into relatively prime numbers

In particular, if there are n factors, we have 2^(n-1) triples, 
since for each prime we can send it to either s or t, 
and then divide by 2 to always make s bigger.

Then on top of that, we also consider how many triples the factors 
appear in, since we can have multiples of primitive triples as well.
To do this, we count how many factors have a certain number of prime 
factors, and count all of their triples at once.
*/
unsigned long long numTriples (std::vector<int> primePowers)
{
	unsigned long long ans{0};
	for(size_t i = 1; i <= primePowers.size(); i++)
	{
		unsigned long long c = choose(primePowers, i, 0, 1);
		ans += c * algorithms::exp(2ULL, i-1);
	}
	return ans;
}

size_t firstZero(std::vector<int> p)
{
	for(size_t i = 0; i < p.size(); i++)
	{
		if(p[i] == 0) return i;
	}
	return p.size();
}

int main ()
{
	//Find the smallest integer such that there are 
	//exactly 47547 different right triangles with 
	//integer sides lengths, such that this integer is one of the 
	//legs of the triangle

	/*
	Fundamentally, this just needs the number theoretic formula that 
	every primitive pythagorean triple is of the form
	x^2+y^2=z^2:
	x = 2st, y = s^2-t^2, z=s^2+t^2, 
	for gcd(s,t)=1 and they are not both odd
	Then we are simply looking for an integer 
	such that there are 47547 ways to factor it as either 
	x,y, or potentially some multiple of these
	*/

	//Number of primitive triples depends on prime factorization of number
	//Brute force numbers consisting of small primes until we find one which works.

	unsigned long long goal = 47547;
	unsigned long long numPrimes = 12;
	int maxPow = 10;
	algorithms::generatePrimes(1000);
	std::priority_queue<struct contain> q{};
	std::vector<int> primePowers{};
	for(unsigned long long i = 0; i < numPrimes; i++)
	{
		primePowers.push_back(0);
	}
	struct contain x{primePowers};
	q.push(x);
	unsigned long long max = 0;
	while(!q.empty())
	{
		struct contain curr = q.top();
		q.pop();
		size_t loc = firstZero(curr.primePowers);
		if(loc < numPrimes)
		{
			for(int i = 1; i <= maxPow && (loc == 0 || i <= curr.primePowers[loc-1]); i++)
			{
				std::vector<int> copy{curr.primePowers};
				copy[loc] = i;
				unsigned long long num = numTriples(copy);
				if(num == goal)
				{
					for(unsigned long long j = 0; j < numPrimes; j++)
					{
						std::cout << copy[j] << ' ';
					}
					std::cout << '\n'; 
					unsigned long long ans = 1;
					for(unsigned long long k = 0; k < numPrimes; k++)
					{
						ans *= algorithms::exp(algorithms::primes[k], static_cast<unsigned long long>(copy[k]));
					}
					std::cout << ans << '\n';
				}
				else if(num < goal)
				{
					struct contain y{copy};
					q.push(y);
					if(num > max)
					{
						max = num;
						std::cout << num << '\n';
					}
				}
			}
		}
	}	
	return 0;
}