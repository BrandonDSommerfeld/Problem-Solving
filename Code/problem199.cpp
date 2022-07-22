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

int levels = 10;

bool equalish(double x, double y)
{
	return std::abs(x-y) < std::pow(10, -6);
}

double covered(double x1, double y1, double r1, 
			   double x2, double y2, double r2,
			   double x3, double y3, double r3, 
			   int iteration, double firstInside)
{
	if(iteration == levels) return 0.0;
	if(firstInside)
	{
		/*
		(r-r1)^2 = (x1-x)^2 + (y1-y)^2
		(r+r2)^2 = (x2-x)^2 + (y2-y)^2
		(r+r3)^2 = (x3-x)^2 + (y3-y)^2
		*/
		double denom1 = 2*(x3*(y2-y1) + x1*(y3-y2) + x2*(y1-y3));
		double num1 = 2*(x3*(-r1-r2) + x1*(r2-r3) + x2*(r3+r1));
		double num2 = x3*(r1*r1 - x1*x1 - y1*y1 - r2*r2 + x2*x2 + y2*y2)
		+ x1*(r2*r2 - x2*x2 - y2*y2 - r3*r3 + x3*x3 + y3*y3)
		+ x2*(-r1*r1 + x1*x1 + y1*y1 + r3*r3 - x3*x3 - y3*y3);

		//Coefficients for y in terms of r
		double c1 = num1 / denom1;
		double c2 = num2 / denom1;

		double denom2 = 2*(y3*(x2-x1) + y1*(x3-x2) + y2*(x1-x3));
		double num3 = 2*(y3*(-r1-r2) + y2*(r3+r1) + y1*(r2-r3));
		double num4 = y3*(r1*r1 - x1*x2 - y1*y1 - r2*r2 + x2*x2 + y2*y2)
		+ y2*(-r1*r1 + x1*x1 + y1*y1 + r3*r3 - x3*x3 - y3*y3)
		+ y1*(r2*r2 - x2*x2 - y2*y2 - r3*r3 + x3*x3 + y3*y3);

		double c3 = num3 / denom2;
		double c4 = num4 / denom2; 

		/*
		(r+d)^2 = (e - c3*r - c4)^2 + (f-c1*r - c2)^2
		r^2 + 2dr + d^2 = (c3^2 + c1^2)r^2 + (2c3*c4 + 2c1*c2 - 2c1*f - 2c3*e)r + (e^2 + f^2 + c4^2 + c2^2 - 2c4*e - 2c2*f)
		(c3^2 + c1^2 - 1)r^2 + (2c3*c4 + 2c1*c2 - 2c1*f - 2c3*e - 2d)r + (e^2+f^2 + c4^2 + c2^2 - 2c4*e - 2c2*f - d^2)
		*/
		double a = c3*c3 + c1*c1 - 1;
		double b = 2*(c3*c4 + c1*c2 - c1*y2 - c3*x2 - r2);
		double c = (x2*x2 + y2*y2 + c4*c4 + c2*c2 - 2*c4*x2 - 2*c2*y2 - r2*r2); 

		double r = (-b - std::sqrt(b*b - 4*a*c))/(2*a);

		double x = c3*r + c4;
		double y = c1*r + c2;
		
		

		double ans = r*r;
		ans += covered(x1,y1,r1, x2,y2,r2, x,y,r, iteration+1, true);
		ans += covered(x1,y1,r1, x3,y3,r3, x,y,r, iteration+1, true);
		ans += covered(x3,y3,r3, x2,y2,r2, x,y,r, iteration+1, false);
		return ans;
	}
	else 
	{
		/*
		(r+a)^2 = (b-x)^2 + (c-y)^2
		(r+d)^2 = (e-x)^2 + (f-y)^2
		(r+g)^2 = (h-x)^2 + (i-y)^2

		2r(a-d) + a^2 - d^2 = b^2 + c^2 - e^2 - f^2 + 2x(e-b) + 2y(f-c)
		2r(a-g) + a^2 - g^2 = b^2 + c^2 - h^2 - i^2 + 2x(h-b) + 2y(i-c)

		(h-b) first one - (e-b) second one
		2rh(a-d) + ha^2 - hd^2 - 2rb(a-d) - ba^2 + bd^2 - 2re(a-g) - ea^2 + eg^2 + 2rb(a-g) + ba^2 - bg^2
		= hb^2 + hc^2 - he^2 - hf^2 + 2y(f-c)(h-b) - b^3 - bc^2 + be^2 + bf^2
		-eb^2 - ec^2 + eh^2 + ei^2 - 2y(i-c)(e-b) + b^3 + bc^2 - bh^2 - bi^2

		2rha - 2rhd + 2rbd - 2rea + 2reg - 2rbg = 2r(ha-hd+bd-ea+eg-bg)
		ha^2-hd^2+bd^2 - ea^2+eg^2 - bg^2
		= hb^2 + hc^2 - he^2 - hf^2 + be^2 + bf^2
		- eb^2 - ec^2 + eh^2 + ei^2 - bh^2 - bi^2
		+ 2y(fh - ch - bf - ei + ce + bi)

		2y(fh - ch - bf - ei + ce + bi)
		= 2r(ha-hd+bd-ea+eg-bg)
		+ h(a^2-b^2-c^2-d^2+e^2+f^2)
		+ b(d^2-g^2-e^2-f^2+h^2+i^2)
		+ e(g^2-a^2+b^2+c^2-h^2-i^2)

		(i-c) first one, (f-c) second one
		2x(ie - ib - ce - hf + bf + ch)
		= 2r(ia-id-fa + fg+cd - cg)
		+ i(a^2-d^2-b^2-c^2+e^2+f^2)
		+ f(g^2-a^2+b^2+c^2-h^2-i^2)
		+ c(d^2-e^2-f^2-g^2+h^2+i^2)
		
		(r+a)^2 = (b-x)^2 + (c-y)^2
		(r+d)^2 = (e-x)^2 + (f-y)^2
		(r+g)^2 = (h-x)^2 + (i-y)^2

		*/
		double denom1 = 2*(x3*(y2-y1) + x1*(y3-y2) + x2*(y1-y3));
		double num1 = 2*(x3*(r1-r2) + x1*(r2-r3) + x2*(r3-r1));
		double num2 = x3*(r1*r1 - x1*x1 - y1*y1 - r2*r2 + x2*x2 + y2*y2)
		+ x1*(r2*r2 - x2*x2 - y2*y2 - r3*r3 + x3*x3 + y3*y3)
		+ x2*(-r1*r1 + x1*x1 + y1*y1 + r3*r3 - x3*x3 - y3*y3);

		//Coefficients for y in terms of r
		double c1 = num1 / denom1;
		double c2 = num2 / denom1;

		double denom2 = 2*(y3*(x2-x1) + y1*(x3-x2) + y2*(x1-x3));
		double num3 = 2*(y3*(r1-r2) + y2*(r3-r1) + y1*(r2-r3));
		double num4 = y3*(r1*r1 - x1*x1 - y1*y1 - r2*r2 + x2*x2 + y2*y2)
		+ y2*(-r1*r1 + x1*x1 + y1*y1 + r3*r3 - x3*x3 - y3*y3)
		+ y1*(r2*r2 - x2*x2 - y2*y2 - r3*r3 + x3*x3 + y3*y3);

		double c3 = num3 / denom2;
		double c4 = num4 / denom2; 

		/*
		(r+d)^2 = (e - c3*r - c4)^2 + (f-c1*r - c2)^2
		r^2 + 2dr + d^2 = (c3^2 + c1^2)r^2 + (2c3*c4 + 2c1*c2 - 2c1*f - 2c3*e)r + (e^2 + f^2 + c4^2 + c2^2 - 2c4*e - 2c2*f)
		(c3^2 + c1^2 - 1)r^2 + (2c3*c4 + 2c1*c2 - 2c1*f - 2c3*e - 2d)r + (e^2+f^2 + c4^2 + c2^2 - 2c4*e - 2c2*f - d^2)
		*/
		double a = c3*c3 + c1*c1 - 1;
		double b = 2*(c3*c4 + c1*c2 - c1*y2 - c3*x2 - r2);
		double c = (x2*x2 + y2*y2 + c4*c4 + c2*c2 - 2*c4*x2 - 2*c2*y2 - r2*r2); 

		double r = (-b - std::sqrt(b*b - 4*a*c))/(2*a);

		double x = c3*r + c4;
		double y = c1*r + c2;
		

		
		double ans = r*r;
		ans += covered(x1,y1,r1, x2,y2,r2, x,y,r, iteration+1, false);
		ans += covered(x1,y1,r1, x3,y3,r3, x,y,r, iteration+1, false);
		ans += covered(x3,y3,r3, x2,y2,r2, x,y,r, iteration+1, false);
		return ans;
	}
}

int main ()
{
	//Take a circle, then take 3 circles of equal radius and place them inside 
	//tangent, and centered
	//Then in the gaps, we place the largest possible tangent circle inside, 
	//and iterate this 10 times
	//At the end, what fraction of the original circle is uncovered?

	//If large circle has radius 1, the 3 inner circles have radius 
	//2 = 1 + r + 2/3 r*sqrt(3)
	//r = 1/(1 + 2/sqrt(3))

	//For circles to be tangent, distance between centers must be sum of the radii
	//Except for being inside the large circle, in which case it must be difference of radii
	double r = 1.0 / (1.0 + 2.0/std::sqrt(3));
	double x1 = 0.0;
	double y1 = r*2.0 / std::sqrt(3);
	double x2 = r;
	double y2 = y1 - r*std::sqrt(3);
	double x3 = -r;
	double y3 = y2;
	double ans = 3*r*r;
	ans += covered(x1,y1,r,x2,y2,r,x3,y3,r,0,false);
	ans += covered(0,0,1, x2,y2,r,x3,y3,r,0,true);
	ans += covered(0,0,1, x1,y1,r,x3,y3,r,0,true);
	ans += covered(0,0,1, x2,y2,r,x1,y1,r,0,true);
	std::cout << 1-ans << '\n';
	return 0;
}