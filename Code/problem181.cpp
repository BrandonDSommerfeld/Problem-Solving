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

static constexpr int totalBlack = 60;
static constexpr int totalWhite = 40;

unsigned long long index(int black, int white, int lastBlack, int lastWhite)
{
	return black + (totalBlack+1)*white + (totalBlack+1)*(totalWhite+1)*lastBlack + (totalBlack+1)*(totalBlack+1)*(totalWhite+1)*lastWhite;
}

//For a given grouping, we count it by arranging groups with the most blacks on the left,
//and within the same number of blacks, more white to the left
//Using dynamic programming, we create a leftmost group, and recurse with the remaining 
//objects, along with the restriction on the maximum black and white we can use
unsigned long long ways(int black, int white, int lastBlack, int lastWhite, unsigned long long *table)
{
	if(black == 0 && white == 0) return 1;
	if(table[index(black,white,lastBlack,lastWhite)] != 0) return table[index(black,white,lastBlack,lastWhite)];
	if(black < lastBlack || (black==lastBlack && white < lastWhite))
	{
		if(table[index(black,white,black,white)] != 0)
		{
			return table[index(black,white,black,white)];
		}
	}
	unsigned long long ans{0};
	int start = black == 0 ? 0 : 1;
	int limit = (lastBlack <= black) ? lastBlack : black;
	for(int b = limit; b >= start; b--)
	{
		int start2 = b == 0 ? 1 : 0;
		int limit2 = (b == lastBlack && lastWhite <= white) ? lastWhite : white;
		for(int w = limit2; w >= start2; w--)
		{
			ans += ways(black-b, white-w, b, w, table);
		}
	}
	table[index(black,white,lastBlack,lastWhite)] = ans;
	if(black < lastBlack || (black == lastBlack && white < lastWhite))
	{
		table[index(black,white,black,white)] = ans;
	}
	return ans;
}

int main ()
{
	//How many ways can 60 black objects and 40 white objects be grouped
	//That is, we create groups of objects, and it only matters how many of each there 
	//are in each group, so for example if we have 3 black and 1 white, we have 
	//(BBBW), (B,BBW), (B,B,B,W), (B,B,BW), (B,BB,W), (BBB,W), (BB,BW)

	//Fix number of groups, and then balls and urns the black objects into them
	//Need to somehow make number of blacks decreasing to prevent double counting
	unsigned long long* table = static_cast<unsigned long long*>(calloc(sizeof(unsigned long long), 
	(totalBlack+1)*(totalBlack+1)*(totalWhite+1)*(totalWhite+1)));
	std::cout << ways(totalBlack, totalWhite, totalBlack, totalWhite, table) << '\n';
	free(table);
	return 0;
}