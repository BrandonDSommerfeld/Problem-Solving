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
	//Let (x1,x2,...xm) be a tuple of positive real numbers, with their sum equal to m
	//Let Pm be the tuple for which x1^1 * x2^2 * x3*3 * ... * xm^m is maximized
	//Find the sum of the floor of Pm for 2 <= m <= 15

	//This is just constrained optimiziation, so we use Langrange multipliers
	//The constraint of the sum has gradient (1,1,1...)
	//Thus, to maximize, we want the gradient of our product to be a multiple of 
	//If we solve the gradient of the product, we get 
	//x2 = 2*x1, ... xm = m*x1
	//With the sum being equal to m, it is easy to divide m up into these values
  	long long ans = 0;
	for(int i = 2; i <= 15; i++)
	{
		long long denom = (i*(i+1))/2;
		double x = static_cast<double>(i)/(static_cast<double>(denom));
		double val = 1.0;
		for(int j = 1; j <= i; j++)
		{
			val *= std::pow(j*x, j);
		}
		std::cout << val << '\n';
		ans += std::lround(std::floor(val));
	}
	std::cout << ans << '\n';
	return 0;
}