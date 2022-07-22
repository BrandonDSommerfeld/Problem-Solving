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

unsigned long long sum (unsigned long long row)
{
	unsigned long long lower1 = (row-2)*(row-3)/2+1;
	//unsigned long long upper1 = (row-2)*(row-1)/2;
	unsigned long long lower2 = (row-1)*(row-2)/2+1;
	unsigned long long upper2 = (row-1)*(row)/2;
	unsigned long long lower3 = (row)*(row-1)/2+1;
	unsigned long long upper3 = (row)*(row+1)/2;
	unsigned long long lower4 = (row+1)*(row)/2+1;
	unsigned long long upper4 = (row+1)*(row+2)/2;
	//unsigned long long lower5 = (row+2)*(row+1)/2+1;
	unsigned long long upper5 = (row+2)*(row+3)/2;

	//Efficiently determine which numbers in the relevant 5 rows are prime
	bool *primes = static_cast<bool*>(malloc(sizeof(bool) * (upper5-lower1+1)));
	for(unsigned long long i = lower1; i <= upper5; i++)
	{
		primes[i-lower1] = true;
	}
	for(size_t i = 0; i < algorithms::primes.size() && algorithms::primes[i]*algorithms::primes[i] <= upper5; i++)
	{
		unsigned long long start = ((lower1-1) / algorithms::primes[i]) + 1;
		for(unsigned long long j = start; algorithms::primes[i]*j <= upper5; j++)
		{
			primes[algorithms::primes[i]*j-lower1] = false;
		}
	}	
	//Count prime neighbors in the middle 3 rows
	int *numPrimeNeighbors = static_cast<int*>(calloc(sizeof(int), upper4-lower2+1));
	for(unsigned long long i = lower2; i <= upper2; i++)
	{
		if(primes[i-lower1])
		{
			if(i < upper2 && primes[i-lower1 - (row-2)]) numPrimeNeighbors[i-lower2]++;
			if(i > lower2 && primes[i-lower1 - (row-1)]) numPrimeNeighbors[i-lower2]++;
			if(i < upper2-1 && primes[i-lower1 - (row-3)]) numPrimeNeighbors[i-lower2]++;

			if(primes[i-lower1 + (row-1)]) numPrimeNeighbors[i-lower2]++;
			if(primes[i-lower1 + (row)]) numPrimeNeighbors[i-lower2]++;
			if(primes[i-lower1 + (row-2)]) numPrimeNeighbors[i-lower2]++;
		}
	}
	for(unsigned long long i = lower3; i <= upper3; i++)
	{
		if(primes[i-lower1])
		{
			if(i < upper3 && primes[i-lower1 - (row-1)]) numPrimeNeighbors[i-lower2]++;
			if(i > lower3 && primes[i-lower1 - (row)]) numPrimeNeighbors[i-lower2]++;
			if(i < upper3-1 && primes[i-lower1 - (row-2)]) numPrimeNeighbors[i-lower2]++;

			if(primes[i-lower1 + (row)]) numPrimeNeighbors[i-lower2]++;
			if(primes[i-lower1 + (row+1)]) numPrimeNeighbors[i-lower2]++;
			if(primes[i-lower1 + (row-1)]) numPrimeNeighbors[i-lower2]++;
		}
	}
	for(unsigned long long i = lower4; i <= upper4; i++)
	{
		if(primes[i-lower1])
		{
			if(i < upper4 && primes[i-lower1 - (row)]) numPrimeNeighbors[i-lower2]++;
			if(i > lower4 && primes[i-lower1 - (row+1)]) numPrimeNeighbors[i-lower2]++;
			if(i < upper4-1 && primes[i-lower1 - (row-1)]) numPrimeNeighbors[i-lower2]++;

			if(primes[i-lower1 + (row+1)]) numPrimeNeighbors[i-lower2]++;
			if(primes[i-lower1 + (row+2)]) numPrimeNeighbors[i-lower2]++;
			if(primes[i-lower1 + (row)]) numPrimeNeighbors[i-lower2]++;
		}
	}
	//Count primes with many neighbors, or one of their neighbors has many neighbors
	unsigned long long ans = 0;
	for(unsigned long long i = lower3; i <= upper3; i++)
	{
		if(primes[i-lower1])
		{
			if(numPrimeNeighbors[i-lower2] >= 2) ans += i;
			else if (numPrimeNeighbors[i-lower2+(row-1)] >= 2) ans += i;
			else if (numPrimeNeighbors[i-lower2+(row)] >= 2) ans += i;
			else if (numPrimeNeighbors[i-lower2+(row+1)] >= 2) ans += i;
			else if (i < upper3 && numPrimeNeighbors[i-lower2-(row-1)] >= 2) ans += i;
			else if (i > lower3 && numPrimeNeighbors[i-lower2-(row)] >= 2) ans += i;
			else if (i < upper3-1 && numPrimeNeighbors[i-lower2-(row-2)] >= 2) ans += i;
		}
	}
	return ans;
}

int main ()
{
	//Place the positive integers in a triangle as 
	//1
	//2 3
	//4 5 6
	//7 8 9 10
	//...
	//When viewed this way, each number may have up to 8 neighbors
	//A set of 3 prime numbers is called a prime triplet if 2 of the primes 
	//are neighbors of the third
	//Let S(n) be the sum of all primes in row n, starting from 1, 
	//which are contained in some prime triplet
	//Compute S(5678027) + S(7208785)
	algorithms::generatePrimes(10000000);

	constexpr unsigned long long row1size = 5678027;
	constexpr unsigned long long row2size = 7208785;	
	std::cout << sum(row1size) + sum(row2size) << '\n';
	return 0;
}