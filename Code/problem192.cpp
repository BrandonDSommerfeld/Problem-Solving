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

static constexpr unsigned long long limit = 1000000000000ULL;
static constexpr size_t precision = 20;

math::Rational abs(const math::Rational& num)
{
	if(num >= 0) return num;
	return -num;
}

unsigned long long bestApproxDenom (unsigned long long num)
{
	unsigned long long p0 = 0;
	unsigned long long p1 = 1;
	unsigned long long q0 = 1;
	unsigned long long q1 = 0;
	unsigned long long ak = 0, pOld = 0, qOld = 0;
	//The convergents of the sqrt alternate being above or below it, 
	bool above = false;
	int loc = -1, start = -1;
	std::vector<unsigned long long> digits{};
	while(q1 <= limit)
	{
		if(start == -1)
		{
		//Use binary search to determine the next digit:
		//Want to get as close as possible, while still being properly above or below 
		//the square root
		unsigned long long high = 1;
		while(true)
		{
			unsigned long long numerator = p1*high + p0;
			unsigned long long denominator = q1*high+q0;
			if(above)
			{
				if(numerator*numerator <= denominator*denominator*num)
				{
					break;
				}
			}
			else 
			{
				if(numerator*numerator >= denominator*denominator*num)
				{
					break;
				}
			}
			high *= 2;	
		}	
		unsigned long long low = high/2;
		while(low < high-1)
		{
			unsigned long long mid = low + (high-low)/2;
			math::Unsigned numerator = p1*mid + p0;
			math::Unsigned denominator = q1*mid + q0;
			if(above)
			{
				if(numerator*numerator <= denominator*denominator*num)
				{
					high = mid;
				}
				else 
				{
					low = mid;
				}
			}
			else 
			{
				if(numerator*numerator >= denominator*denominator*num)
				{
					high = mid;
				}
				else 
				{
					low = mid;
				}
			}
		}
		ak = low;	
		unsigned long long temp1 = ak*p1 + p0;
		unsigned long long temp2 = ak*q1 + q0;
		qOld = q0;
		pOld = p0;
		p0 = p1;
		q0 = q1;
		p1 = temp1;
		q1 = temp2;
		above = !above;
		
		//Track the digits, and once we see repeats can just read them off 
		//instead of recalculating again
		digits.push_back(ak);
		if(digits.size() > precision)
		{
			for(size_t i = 0; i < digits.size() - precision; i++)
			{
				bool works = true;
				for(size_t j = 0; j < precision && works; j++)
				{
					if(digits[i+j] != digits[digits.size()-precision+j])
					{
						works = false;
					}
				}
				if(works)
				{
					start = i;
					loc = i+precision;
				}
			}
		}
		}
		else 
		{
			ak = digits[loc];
			unsigned long long temp1 = ak*p1 + p0;
			unsigned long long temp2 = ak*q1 + q0;
			qOld = q0;
			pOld = p0;
			p0 = p1;
			q0 = q1;
			p1 = temp1;
			q1 = temp2;
		
			loc++;
			while(static_cast<size_t>(loc) >= digits.size()  - precision)
			{
				loc -= digits.size() - precision-start;
			} 
		}
	}
	//Instead of using the last ak, any number from half of it upwards can be used 
	//instead to get a best rational approximation
	math::Rational best{static_cast<long long>(p0),static_cast<long long>(q0)};
	unsigned long long bestDenom = q0;
	for(unsigned long long i = (ak+1)/2; i < ak; i++)
	{
		unsigned long long numerator = i*p0 + pOld;
		unsigned long long denominator = i*q0 + qOld;
		if(denominator <= limit)
		{
			math::Rational temp{static_cast<long long>(numerator), static_cast<long long>(denominator)};
			if(abs(temp*temp-num) < abs(best*best-num))
			{
				best = temp;
				bestDenom = denominator;
			}
		}
	}
	return bestDenom;
}

int main ()
{
	//For 1 < n <= 100,000 which are not perfect squares, 
	//Let p/q be the best rational approximation of sqrt(n)
	//where q is at most 10^12
	//Find the sum of all such q

	//Best rational approximations can be found using 
	//convergents to the continued fraction of the square root

	unsigned long long ans = 0;
	for(unsigned long long i = 2; i <= 100000; i++)
	{
		unsigned long long s = algorithms::nthRoot(i, 2ULL);
		if(s*s != i)
		{
			unsigned long long temp = bestApproxDenom(i);	
			if(i % 1000 == 0)
			{
				std::cout << i << '\n';
			}
			ans += temp;
		}
	}	
	std::cout << ans << '\n';
	return 0;
}