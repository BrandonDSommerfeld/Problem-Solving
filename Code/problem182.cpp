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

bool correctOrder(int b, int e, unsigned long long m)
{
	for(int i = 1; i < e; i++)
	{
		if(algorithms::exp(static_cast<unsigned long long>(b),static_cast<unsigned long long>(i),m) == 1)
		{
			std::cout << b << ' ' << e << ' ' << m << ' ' << i << '\n';
			return false;
		}
	}
	return algorithms::exp(static_cast<unsigned long long>(b),static_cast<unsigned long long>(e),m) == 1;
}

int main ()
{
	//Consider RSA encryption, where you raise a message m to the power of e mod pq 
	//to encrypt it. 
	//Given p=1009, q=3643, find the sum of all e such that the number of 
	//messages from 0 to n-1 which remain themselves when raised to the e is minimized
	//We also require that gcd(e, phi(pq)=(p-1)(q-1))=1
	unsigned long long p = 1009;
	unsigned long long q = 3643;
	unsigned long long n = p*q;
	unsigned long long phi = (p-1)*(q-1);

	//Because of gcd condition and Euler's theorem, 
	//only need to raise multiples of p or q to the power, 
	//Also, calculate
	//m^e = m mod pq
	//(kp)^e = kp + rpq
	//k (kp)^(e-1) = k + rq
	//(kp)^(e-1) = 1 mod q
	//That is, e-1 must be a multiple of the order
	std::vector<int> ps{};
	std::vector<int> qs{};
	for(int i = 1; static_cast<unsigned long long>(i) < n; i++)
	{
		if(i % p == 0)
		{
			ps.push_back(i);
		}
		if(i % q == 0)
		{
			qs.push_back(i);
		}
	}
	std::vector<int> pOrders{};
	std::vector<int> qOrders{};
	for(size_t i = 0; i < ps.size(); i++)
	{
		unsigned long long ord = q-1;
		for(unsigned long long j = 2; j <= ord; j++)
		{
			while(ord % j == 0)
			{
				ord /= j;
				if(algorithms::exp(ps[i], ord, q) != 1)
				{
					ord *= j;
					break;
				}
			}
		}	
		pOrders.push_back(static_cast<int>(ord));
	}
	for(size_t i = 0; i < qs.size(); i++)
	{
		unsigned long long ord = p-1;
		for(unsigned long long j = 2; j <= ord; j++)
		{
			while(ord % j == 0)
			{
				ord /= j;
				if(algorithms::exp(qs[i], ord, p) != 1)
				{
					ord *= j;
					break;
				}
			}
		}	
		qOrders.push_back(static_cast<int>(ord));
	}	

	unsigned long long *count = static_cast<unsigned long long*>(calloc(sizeof(unsigned long long), phi));
	for(size_t i = 0; i < pOrders.size(); i++)
	{
		for(size_t j = 1; pOrders[i]*j < phi-1; j++)
		{
			count[pOrders[i]*j+1]++;
		}
	}
	for(size_t i = 0; i < qOrders.size(); i++)
	{
		for(size_t j = 1; qOrders[i]*j < phi-1; j++)
		{
			count[qOrders[i]*j+1]++;
		}
	}
	unsigned long long ans{0}, best{n};
	count[1] = n;
	for(unsigned long long e = 1; e < phi; e++)
	{
		if(algorithms::gcd(e, phi) == 1)
		{
			if(count[e] == best)
			{
				ans += e;
			}
			if(count[e] < best)
			{
				best = count[e];
				ans = e;
			}
		}
	}	
	std::cout << ans << '\n';
	return 0;
}