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

long f(double x)
{
	double p = std::pow(2, 30.403243784 - x*x);
	long fl = std::lround(std::floor(p));
	return fl;
}

int main ()
{
	//Define f(0) = -1
	//f(n) = floor(2^(30.403243784 - (f(n-1))^2)) * 10^-9
	//Compute f(10^12) + f((10^12)+1)
	
	//Quite simply, keep track of all of the floors that we see, 
	//and as soon as we see a repeat we can use that
	std::vector<long> seen{};
	long long start = -1; 
	seen.push_back(-1);
	double curr = -1;
	while(start == -1)
	{
		long fl = f(curr);
		for(size_t i = 0; i < seen.size(); i++)
		{
			if(seen[i] == fl)
			{
				start = static_cast<long long>(i);
			}
		} 
		seen.push_back(fl);
		curr = static_cast<double>(fl) * std::pow(10,-9);
	}
	size_t goal = 1000000000000ULL;
	goal -= seen.size();
	goal %= (seen.size() - start);
	long ans = seen[start+goal];
	ans += seen[start+goal+1];
	//Real answer is this times 10^-9, but have issues with double precision
	std::cout << ans << '\n';
	return 0;
}