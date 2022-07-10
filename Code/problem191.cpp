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
	//On a given day, a child can either be absent, late, or on time
	//If they are late more than once overall, or absent more than 
	//2 days in a row, they are a bad student
	//How many possible ways are there to be a good student 
	//for a total of 30 days?

	//Simple dynamic programming problem on the number of days
	//Keep track of ways with last day absent, last 2 absent, 
	//and last one not absent, as well as having a late or not
	unsigned long long days = 30;
	unsigned long long *late0Absent0 = static_cast<unsigned long long*>(malloc(sizeof(unsigned long long) * days));
	unsigned long long *late0Absent1 = static_cast<unsigned long long*>(malloc(sizeof(unsigned long long) * days));
	unsigned long long *late0Absent2 = static_cast<unsigned long long*>(malloc(sizeof(unsigned long long) * days));
	unsigned long long *late1Absent0 = static_cast<unsigned long long*>(malloc(sizeof(unsigned long long) * days));
	unsigned long long *late1Absent1 = static_cast<unsigned long long*>(malloc(sizeof(unsigned long long) * days));
	unsigned long long *late1Absent2 = static_cast<unsigned long long*>(malloc(sizeof(unsigned long long) * days));
	late0Absent0[0] = 1;
	late0Absent1[0] = 1;
	late0Absent2[0] = 0;
	late1Absent0[0] = 1;
	late1Absent1[0] = 0;
	late1Absent2[0] = 0;
	for(unsigned long long i = 1; i < days; i++)
	{
		late0Absent0[i] = late0Absent0[i-1] + late0Absent1[i-1] + late0Absent2[i-1];
		late0Absent1[i] = late0Absent0[i-1];
		late0Absent2[i] = late0Absent1[i-1];
		late1Absent0[i] = late0Absent0[i-1] + late0Absent1[i-1] + late0Absent2[i-1]
						+ late1Absent0[i-1] + late1Absent1[i-1] + late1Absent2[i-1];
		late1Absent1[i] = late1Absent0[i-1];
		late1Absent2[i] = late1Absent1[i-1];
	}
	std::cout << late0Absent0[days-1] + late0Absent1[days-1] + late0Absent2[days-1]
			   + late1Absent0[days-1] + late1Absent1[days-1] + late1Absent2[days-1] << '\n';
	return 0;
}