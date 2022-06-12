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
	//A pandigital number has all digits from 0-9
	//A step number has each digit 1 more or 1 less than the last
	//How many pandigital step numbers are there below 10^40?

	math::Unsigned *allDigits = static_cast<math::Unsigned*>(malloc(sizeof(math::Unsigned) * 10));
	math::Unsigned *no0 = static_cast<math::Unsigned*>(malloc(sizeof(math::Unsigned) * 10));
	math::Unsigned *no9 = static_cast<math::Unsigned*>(malloc(sizeof(math::Unsigned) * 10));
	math::Unsigned *no0or9 = static_cast<math::Unsigned*>(malloc(sizeof(math::Unsigned) * 10));
	math::Unsigned ans{0};
	for(int i = 0; i < 10; i++)
	{
		allDigits[i] = 1;
		if(i > 0)
		{
			no0[i] = 1;
			if(i < 9)
			{
				no0or9[i] = 1;
				no9[i] = 1;
			}
			else 
			{
				no0or9[i] = 0;
				no9[i] = 0;
			}
		}
		else
		{
			no0[i] = 0;
			no9[i] = 1;
			no0or9[i] = 0;
		}
	}
	//Just build numbers recursively based on their furthest left digit
	//Ensure pandigital by subtracting out those which use only 0-8 or less, and 1-9, 
	//and add back in 1-8 since it was removed twice
	for(int i = 0; i < 39; i++)
	{
		math::Unsigned *newAllDigits = static_cast<math::Unsigned*>(calloc(sizeof(math::Unsigned), 10));
		math::Unsigned *newNo0 = static_cast<math::Unsigned*>(calloc(sizeof(math::Unsigned), 10));
		math::Unsigned *newNo9 = static_cast<math::Unsigned*>(calloc(sizeof(math::Unsigned), 10));
		math::Unsigned *newNo0or9 = static_cast<math::Unsigned*>(calloc(sizeof(math::Unsigned), 10));	
		for(int j = 0; j < 10; j++)
		{
			if(j > 0)
			{
				newAllDigits[j] += allDigits[j-1];
				if(j > 1)
				{
					newNo0[j] += no0[j-1];
					if(j < 9)
					{
						newNo0or9[j] += no0or9[j-1];
					}
				}
				if(j < 9)
				{
					newNo9[j] += no9[j-1];
				}
			}
			if(j < 9)
			{
				newAllDigits[j] += allDigits[j+1];
				if(j > 0)
				{
					newNo0[j] += no0[j+1];
					if(j < 8)
					{
						newNo0or9[j] += no0or9[j+1];
					}
				}
				if(j < 8)
				{
					newNo9[j] += no9[j+1];
				}
			}
		}
		free(allDigits);
		free(no0);
		free(no9);
		free(no0or9);
		allDigits = newAllDigits;
		no0 = newNo0;
		no9 = newNo9;
		no0or9 = newNo0or9;
		for(int j = 1; j < 10; j++)
		{
			ans += allDigits[j];
			ans += no0or9[j];
			ans -= no0[j];
			ans -= no9[j];
		}
		std::cout << ans << '\n';
	}
}