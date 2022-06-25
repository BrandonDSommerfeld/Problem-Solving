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

//Encode/decode colorations as base 3 numbers
unsigned long long index (const std::vector<int>& nums)
{
	unsigned long long ans = 0;
	for(size_t i = 0; i < nums.size(); i++)
	{
		ans *= 3;
		ans += nums[i];
	}
	return ans;
}

std::vector<int> colors (unsigned long long num, int numDigits)
{
	std::vector<int> ans{};
	for(int i = 0; i < numDigits; i++)
	{
		ans.push_back(static_cast<int>(num % 3));
		num /= 3;
	}
	return ans;
}

unsigned long long insert2(const std::vector<int>& colors, unsigned long long *ways, size_t loc, std::vector<int>& curr)
{
	//Given a coloration on the lower level, find colorations on the 
	//level above which are valid to use
	if(loc == colors.size())
	{
		return ways[index(curr)];
	}
	unsigned long long ans = 0;
	for(int i = 0; i < 3; i++)
	{
		if(i != colors[loc])
		{
			curr[loc] = i;
			ans += insert2(colors, ways, loc+1, curr);
		}
	}
	return ans;
}

unsigned long long insert(const std::vector<int>& colors, unsigned long long *ways, size_t loc, std::vector<int>& curr)
{
	//At current level, colors represents possible colorations of every other triangle
	//Colors are 0,1,2
	//This function figures out allowed colors to go in between these triangles
	if(loc == colors.size() - 1)
	{
		std::vector<int> temp{curr};
		return insert2(curr, ways, 0, temp);
	}
	unsigned long long ans = 0;
	for(int i = 0; i < 3; i++)
	{
		if(i != colors[loc] && i != colors[loc+1])
		{
			curr[loc] = i;
			ans += insert(colors, ways, loc+1, curr);
		}
	}
	return ans;
}

unsigned long long numWays (const std::vector<int>& colors, unsigned long long *ways)
{
	std::vector<int> temp{};
	for(size_t i = 0; i < colors.size()-1; i++)
	{
		temp.push_back(0);
	}
	return insert(colors, ways, 0, temp);
}

int main ()
{
	//Consider an equilateral triangle, which is made out of 64 smaller 
	//equilateral triangles.
	//How many ways are there to color it with 3 colors to that 
	//adjacent triangles are not the same color
	
	//Move down level by level, and keep track of how many ways there are
	//to get each coloration on the current level
	
	unsigned long long *ways = static_cast<unsigned long long*>(malloc(sizeof(unsigned long long) * 3));
	ways[0] = 1;
	ways[1] = 1;
	ways[2] = 1;
	unsigned long long pow3 = 9;
	for(int i = 0; i < 7; i++, pow3 *= 3)
	{
		unsigned long long *temp = static_cast<unsigned long long*>(malloc(sizeof(unsigned long long) * pow3));
		for(unsigned long long j = 0; j < pow3; j++)
		{
			temp[j] = numWays(colors(j, i+2), ways);
		}
		free(ways);
		ways = temp;
	}
	unsigned long long ans = 0;
	for(unsigned long long i = 0; i < pow3/3; i++)
	{
		ans += ways[i];
	}
	std::cout << ans << '\n';
	return 0;
}