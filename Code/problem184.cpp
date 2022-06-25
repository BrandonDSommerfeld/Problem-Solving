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

struct wrapper
{
	double angle;
};

bool operator< (const struct wrapper& x, const struct wrapper& y)
{
	return x.angle+std::pow(10,-6) < y.angle;
}

bool equalish(double x, double y)
{
	return std::abs(x-y) < std::pow(10,-6);
}

int main ()
{
	//Consider all points (x,y) which are closer than 105 units to (0,0)
	//Using just these points, how many distinct triangles contain the origin in the interior?
	//Note, the origin being a vertex or on a side does not count

	//The origin is contained in a triangle if for each vertex, 
	//when we draw a line through the origin, the other 2 vertices 
	//are on opposite sides of this line


	//For angles around the circle, count how many points have angles 
	//between 0 and that angle, so that given 2 angles, 
	//we can easily look them up and subtract them to find out how 
	//many points are between those angles
	std::map<struct wrapper, unsigned long long> numPoints{};
	long long radius = 105;
	struct wrapper whatever{-1.0};
	numPoints.insert({whatever, 0});
	for(long long x = -radius+1; x < radius; x++)
	{
		for(long long y = -radius+1; y < radius; y++)
		{
			if(x*x+y*y < radius*radius && (x != 0 || y != 0))
			{
				double angle = y < 0 ? 2*M_PI-std::acos(static_cast<double>(x)/std::sqrt(x*x+y*y))
				: std::acos(static_cast<double>(x)/std::sqrt(x*x+y*y));
				struct wrapper temp{angle};
				auto iter = numPoints.find(temp);	
				if(iter == numPoints.end())
				{
					numPoints.insert({temp, 0});
					iter = numPoints.find(temp);
					iter--;
					unsigned long long val = iter->second;
					iter++;
					numPoints.at(temp) = val;
				}
				while(iter != numPoints.end())
				{
					numPoints.at(iter->first) = iter->second+1;
					iter++;
				}					
			}
		}
	}	
	//Once that is done, just iterate over pairs of angles for the first 2 vertices 
	//to be at, and then use the map to count how many 
	//possible third points satisfy the line being drawn condition mentioned above
	//Triangles are counted twice, as first vertex to 
	//second and second to third, thanks 
	//to how the angles are restricted.
	unsigned long long ans{0};
	auto angle1 = numPoints.begin();
	angle1++;
	for(; angle1 != numPoints.end(); angle1++)
	{
		unsigned long long on1 = angle1->second;
		angle1--;
		on1 -= angle1->second;
		angle1++;
		auto angle2 = angle1;
		angle2++;
		while(angle2 != numPoints.end() && !equalish(angle2->first.angle-M_PI, angle1->first.angle))
		{
			if(!equalish(angle1->first.angle+M_PI, angle2->first.angle))
			{
				unsigned long long on2 = angle2->second;
				angle2--;
				on2 -= angle2->second;
				angle2++;
				unsigned long long between = angle2->second - angle1->second - on2;
				ans += on1*on2*between;
			}	
			angle2++;
		}	
	}	
	std::cout << ans/2 << '\n';
	return 0;	
}