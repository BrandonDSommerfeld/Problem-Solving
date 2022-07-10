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

static constexpr unsigned long long mod = 100000000ULL;

math::Unsigned ways(unsigned long long a, unsigned long long b, unsigned long long colors)
{
	math::Unsigned ans = colors*(colors-1);
	//This is dynamic programming problem
	//We advanced from left to right, placing all of the A's first, and then the B's,
	//the order doesn't really matter so we multiply to account for rearranging later
	//At each step, there are 3 ways to build a new solution based on an existing one
	for(unsigned long long i = 0; i < a; i++)
	{
		//Make diagonals have the same colors
		//Then of the middle 3, we can give the top and bottom one the same color
		//in colors-2 ways, in which case the middle one has colors-1 options
		//Otherwise, they are different for the rest, and the middle one has colors-2 options
		ans = ((colors-2)*(colors-1) + (colors-2)*(colors-3)*(colors-2)) * ans
		//Make one diagonal the same, and one different, same counting argument, but 2*colors-4 ways to do this
		  	  + (2*colors-4)*((colors-3)*(colors-1) + ((colors-2)*(colors-2) - (colors-3))* (colors-2))*ans
		//Make all 4 different
		  	  + ((colors-2)*(colors-3))*((colors-4)*(colors-1) + ((colors-2)*(colors-2) - (colors-4))* (colors-2))*ans;
		ans %= mod;  
	}
	for(unsigned long long i = 0; i < b; i++)
	{
		ans = ((colors-2)*(colors-1) + (colors-2)*(colors-3)*(colors-2)) * ans
		  	  + (2*colors-4)*((colors-3)*(colors-1) + ((colors-2)*(colors-2) - (colors-3))* (colors-2))*ans
		  	  + ((colors-2)*(colors-3))*((colors-4)*(colors-1) + ((colors-2)*(colors-2) - (colors-4))* (colors-2))*ans
		//Addiationally, in B we can have the bottom 2 vertices have the same color, but the same 
		//counting argument once again
		  	  + ((colors-2))*((colors-3)*(colors-1) + ((colors-2)*(colors-1) - (colors-3))* (colors-2))*ans;
		ans %= mod;
	}
	return ans;
}

math::Unsigned wrapper (int a, int b, int colors)
{
	return (ways(a,b,colors) * algorithms::choose(a+b, a)) % mod;
}

int main ()
{
	//We have 2 components in our graph:
	//Type A:
	/*
	o---------o
	|  \   /  |
    |    o    |
    |    |    |
    |    o    |
    |    |    |
    |    o    |
	| /     \ |
    o---------o
	And type B:
	o---------o
	|  \   /  |
    |    o    |
    |    |    |
    |    o    |
    |    |    |
    |    o    |
	| /     \ |
    o         o

	We then create graphs by putting a bunch of these components in a line, 
	connecting corner vertices

	Find the last 8 digits of how many distinct graphs can be created 
	using 25 A's, 75 B's, and up to 1985 different colors for the vertices 
	so that adjacent vertices are different colors	
	*/	

	std::cout << wrapper(25,75,1984) << '\n';
	return 0;
}