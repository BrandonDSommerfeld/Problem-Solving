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

static constexpr unsigned long long limit = 20000000;
static constexpr double radiusLimit = 1053779;

double inradius (unsigned long long a, unsigned long long b, unsigned long long c)
{
	double s = static_cast<double>(a+b+c);
	double A = std::sqrt(3) / 2.0;
	A *= a;
	A *= b;
	double r = A/s;
	return r;
}

int main ()
{
	//Find the number of triangles with exactly 1 angle of 60 degrees, 
	//such that the radius of the inscribed circle is at most 
	//1053779
	
	//Just like for Pythagorean triples, these numbers are called 
	//Eisenstein triples and have a way to generate them as 
	//a = m^2 - n^2
	//b = 2mn - n^2
	//c = m^2 - mn + n^2
	//For integers m,n with gcd 1, and n <= m/2
	//Sometimes, this creates triples with gcd 3, where we just divide through by 3
	//From this, and the formula that r = 2A/(a+b+c)
	//We can see that 
	//r = sqrt(3)/2 * (m^2-n^2)*(2mn-n^2) / (m^2-n^2 + 2mn-n^2 + m^2-mn+n^2)
	//= sqrt(3)/2*(2m^3n - m^2n^2 - 2mn^3 + n^4) / (2m^2 + mn - n^2)
	//Derivative is sqrt(3)/2 * (m-2n)
	//This is positive for the range we care about
	//So it always increases, so we can cut it off once the radius gets too large
	unsigned long long ans = 0;
	for(unsigned long long m = 1; m < limit; m++)
	{
		bool done = false;
		for(unsigned long long n = 1; n <= m/2 && !done; n++)
		{
			if(algorithms::gcd(m,n) == 1)
			{
				unsigned long long a = m*m-n*n;
				unsigned long long b = 2*m*n - n*n;
				unsigned long long c = m*m-m*n + n*n;
				if((m+n) % 3 == 0)
				{
					a /= 3;
					b /= 3;
					c /= 3;
				}
				if(a != b)
				{
					double temp = inradius(a,b,c);	
					//Based on the radius of this primitive triple, figure out how many 
					//multiples of it are okay
					ans += static_cast<unsigned long long>(std::llround(std::floor(radiusLimit/temp)));
					if(temp-std::pow(10,-6) >= radiusLimit*3)
					{
						done = true;
					}
				}
			}
		}
	}
	std::cout << ans << '\n';
	return 0;
}