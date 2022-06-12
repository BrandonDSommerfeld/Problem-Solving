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
	//Consider fn(x,y,z) = (x+y+z)(x^n+y^n - z^n)
	//We want to find all rational solutions with 
	//the numerator and denominator all between 1 and 35 inclusive, 
	//such that the triple is a 0 for some n.
	//From here, we consider all distinct sums of x,y,z and add those 
	//all up

	//In order to be 0 with positive numbers, we need x^n + y^n = z^n
	//By Fermat's last theorem, n must be -1,-2, 1, or 2, or else we could multiply 
	//through by the denominator and get a counter example
	std::set<math::FastRational> seen{};
	constexpr int limit = 35;
	math::Rational ans{};
	for(int a = 1; a <= limit; a++)
	{
		for(int b = a+1; b <= limit; b++)
		{
			if(algorithms::gcd(static_cast<long long>(a),static_cast<long long>(b)) == 1)
			{
				math::FastRational x{a,b};
				for(int c = 1; c <= limit; c++)
				{
					for(int d = c+1; d <= limit; d++)
					{
						if(algorithms::gcd(static_cast<long long>(c), static_cast<long long>(d)) == 1)
						{
							math::FastRational y{c,d};
							math::FastRational z1 = x+y;
							if(z1.get_denominator() <= limit && z1.get_numerator() <= limit
							&& z1 < 1)
							{
								if(seen.count(x+y+z1) == 0)
								{
									seen.insert(x+y+z1);
									ans += x+y+z1;
								}
							}
							math::FastRational temp = x*x+y*y;
							long long num = std::llround(std::floor(std::sqrt(temp.get_numerator())));
							long long denom = std::llround(std::floor(std::sqrt(temp.get_denominator())));

							math::FastRational z2{num, denom};
							if(num*num == temp.get_numerator() && denom*denom == temp.get_denominator()
							&& z2.get_denominator() <= limit && z2.get_numerator() <= limit && z2 < 1)
							{
								if(seen.count(x+y+z2) == 0)
								{
									seen.insert(x+y+z2);
									ans += x+y+z2;
								}
							}
							math::FastRational z3 = 1/(1/x + 1/y);
							if(z3.get_denominator() <= limit && z3.get_numerator() <= limit && z3 < 1)
							{
								if(seen.count(x+y+z3) == 0)
								{
									seen.insert(x+y+z3);
									ans += x+y+z3;
								}
							}
							math::FastRational temp2 = (1/(x*x) + 1/(y*y));
							long long num2 = std::llround(std::floor(std::sqrt(temp2.get_numerator())));
							long long denom2 = std::llround(std::floor(std::sqrt(temp2.get_denominator())));
							math::FastRational z4{denom2, num2};
							if(z4.get_denominator() <= limit && z4.get_numerator() <= limit
							&& num2*num2 == temp2.get_numerator() && denom2*denom2 == temp2.get_denominator()
							&& z4 < 1)
							{
								if(seen.count(x+y+z4) == 0)
								{
									seen.insert(x+y+z4);
									ans += x+y+z4;
								}
							}
						}
					}
				}
			}
		}
	}
	std::cout << ans << '\n';
	std::cout << ans.get_denominator() + ans.get_numerator() << '\n';
	return 0;

}