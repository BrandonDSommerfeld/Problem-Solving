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

math::Rational exp(math::Rational b, long long e)
{
	math::Rational ans{1};
	while(e > 0)
	{
		if(e % 2 == 1)
		{
			ans *= b;
		}
		e /= 2;
		b *= b;
	}
	return ans;
}

double f(long long x, long long n)
{
	return x * (std::log(n) - std::log(x));
}

long long d(long long num)
{
	double val = static_cast<double>(num);
	double guess = val/M_E;
	long long lower = std::llround(std::floor(guess));
	long long upper = lower+1;
	math::Rational larger{num, lower};
	math::Rational smaller{num, upper};

	int denom = smaller.get_denominator().to_int();
	//Maximizing x*(ln n - ln x)
	if(f(lower, num) > f(upper, num))
	{
		denom = larger.get_denominator().to_int();
	}
	while(denom % 2 == 0)
	{
		denom /= 2;
	}
	while(denom % 5 == 0)
	{
		denom /= 5;
	}
	if(denom == 1) return -num;
	return num;
} 

int main ()
{
	//Given a number n, consider taking (n/m)^m for integer m > 0
	//Let x be the maximum value we can get by doing this
	//D(n) = n if this maximum value is a terminating decimal, and -n if it is infinite
	//Find the sum of D(n) from 5 to 10,000 inclusive

	//We want integer points near the real-value maximum of (n/x)^x,
	//which is e^(ln(n/x))^x = e^(x(ln n - ln x))
	//Which comes down to maximizing the exponent, and we take its derivative to get 
	//ln n - ln x - 1
	//Thus, we want the derivative to be 0, so x = n/e is optimal
	long long ans{0};
	for(long long i = 5; i <= 10000; i++)
	{
		ans += d(i);
	}
	std::cout << ans << '\n';
	return 0;
	
}