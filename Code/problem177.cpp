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

double toRadian (int angle)
{
	return (static_cast<double>(angle) * M_PI) / 180.0;
}

double toDegrees(double angle)
{
	return (angle * 180.0) / M_PI;
}

bool isInteger(double angle)
{
	return std::abs(angle - std::round(angle)) <= std::pow(10, -9);
}

bool before(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	if(a1 != a5)
	{
		return a1 < a5;
	}
	if(a2 != a6)
	{
		return a2 < a6;
	}
	if(a3 != a7)
	{
		return a3 < a7;
	}
	return a4 <= a8;
}

bool newQuad(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	//Make sure this is the first time this quadrilateral is created, and 
	//that no other configuration of 4 angles has seen it before
	return before(a1,a2,a3,a4,a2,a1,a4,a3) 
	&& before(a1,a2,a3,a4,a3,a4,a1,a2)
	&& before(a1,a2,a3,a4,a4,a3,a2,a1)
	&& before(a1,a2,a3,a4,a5,a8,a6,a7)
	&& before(a1,a2,a3,a4,a6,a7,a5,a8)
	&& before(a1,a2,a3,a4,a7,a6,a8,a5)
	&& before(a1,a2,a3,a4,a8,a5,a7,a6);
}

int main ()
{
	//Find the number of non-similar quadrilaterals such that when the 
	//diagonals are drawn, all 8 corner angles are within 10^-9 
	//of begin an integer number of degrees

	//Picture: angle1 and 2 are paired together at vertex A, 3 and 4 at vertex C
	//angle1 is between diagonal and AB, 2 with diagonal and AD
	//3 is with BC and diagonal, and 4 is CD and diagonal
	
	//We force AB to have length 1, and then use law of sines and 
	//law of cosines to calculate other side lengths and 
	//angles, and check if angles are integers
	unsigned long long ans{0}, ans2{0};
	for(int angle1 = 1; angle1 < 180; angle1++)
	{
		double radian1 = toRadian(angle1);
		for(int angle2 = 1; angle1 + angle2 < 180; angle2++)
		{
			double radian2 = toRadian(angle2);
			for(int angle3 = 1; angle3 < 180; angle3++)
			{	
				double radian3 = toRadian(angle3);
				double side1 = 1.0; 
				double side2 = std::sin(radian1) / std::sin(radian3);
				double diagonal1 = std::sin(M_PI-radian1-radian3) / std::sin(radian3); 
				for(int angle4 = 1; angle3+angle4 < 180; angle4++)
				{	
					double radian4 = toRadian(angle4);
					double side3 = std::sin(radian2)*diagonal1 / std::sin(M_PI-radian2-radian4);
					double side4 = std::sin(radian4)*diagonal1 / std::sin(M_PI - radian2 - radian4);
					double diagonal2 = std::sqrt(side1*side1 + side4*side4 - 2*side1*side4*std::cos(radian1+radian2));

					double radian5 = std::acos((side1*side1 - diagonal2*diagonal2 - side4*side4) / (-2*diagonal2*side4)); 
					double radian6 = std::acos((side4*side4 - diagonal2*diagonal2 - side1*side1) / (-2*diagonal2*side1)); 
					double radian7 = std::acos((side3*side3 - diagonal2*diagonal2 - side2*side2) / (-2*diagonal2*side2)); 
					double radian8 = std::acos((side2*side2 - diagonal2*diagonal2 - side3*side3) / (-2*diagonal2*side3)); 
					if(isInteger(toDegrees(radian5)) && isInteger(toDegrees(radian6)) 
					   && isInteger(toDegrees(radian7)) && isInteger(toDegrees(radian8)))
					{
						int angle5 = static_cast<int>(std::llround(toDegrees(radian5)));		
						int angle6 = static_cast<int>(std::llround(toDegrees(radian6)));		
						int angle7 = static_cast<int>(std::llround(toDegrees(radian7)));		
						int angle8 = static_cast<int>(std::llround(toDegrees(radian8)));			
						if(newQuad(angle1, angle2, angle3, angle4, angle5, angle6, angle7, angle8)
						&& angle1+angle2+angle3+angle4+angle5+angle6+angle7+angle8 == 360)
						{
							ans++;
						}
					}
				}
			}
		}
	}
	std::cout << ans << ' ' << ans2 << '\n';	
	return 0;
}