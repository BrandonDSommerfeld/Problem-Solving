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

bool contains200(unsigned long long num)
{
	while(num >= 200)
	{
		if(num % 1000 == 200)
		{
			return true;
		}
		num /= 10;
	}
	return false;
}

bool helper(unsigned long long num, unsigned long long pos)
{
	unsigned long long digit = (num / pos) % 10;
	num -= pos*digit;
	for(unsigned long long i = 0; i < 10; i++)
	{
		if(algorithms::isPrime(num + pos*i)) 
		{	
			return false;
		}
	}	
	return true;
}

bool primeProof(unsigned long long num)
{
	//Consider each digit, and try to change it
	unsigned long long pos = 1;
	while(pos <= num)
	{
		if(!helper(num,pos)) return false;
		pos *= 10;
	}
	return true;
}

int main ()
{
	//A sqube is a number of the form p^2*q^3 for prime p,q which are different
	//A number is prime proof if there is no way to create a prime number by 
	//changing a single digit of the number
	//Find the 200th prime proof sqube which contains the string "200" somewhere in it 

	unsigned long long limit = 1000000000000ULL;
	algorithms::generatePrimes(1000000);
	std::priority_queue<unsigned long long, std::vector<unsigned long long>, std::greater<unsigned long long>> squbes{};
	unsigned long long cube = 8;
	for(size_t i = 1; 4*cube < limit; i++)
	{
		unsigned long long square = 4;
		for(size_t j = 1; square*cube < limit; j++)
		{
			if(contains200(square*cube))
			{
				if(primeProof(square*cube))
				{
					squbes.emplace(square*cube);
				}
			}
			square = algorithms::primes[j]*algorithms::primes[j];
		}
		cube = algorithms::primes[i]*algorithms::primes[i]*algorithms::primes[i];
	}
	unsigned long long counter = 0;
	unsigned long long curr = 0;
	while(counter < 200 && !squbes.empty()) 
	{
		curr = squbes.top();
		squbes.pop();
		counter++;
	}
	std::cout << curr << '\n';
	return 0;
}