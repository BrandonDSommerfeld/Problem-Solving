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

static constexpr int limit = 1000000;
int find (int *unionFind, int i)
{
	if(unionFind[i] < 0) return i;
	return unionFind[i] = find(unionFind, unionFind[i]);
}

void connect(int *unionFind, int i, int j, int *numConnected)
{
	int parent1 = find(unionFind, i);
	int parent2 = find(unionFind, j);
	if(parent1 == parent2) return;
	if(unionFind[parent1] < unionFind[parent2])
	{
		unionFind[parent2] = parent1;
		numConnected[parent1] += numConnected[parent2];
		return;
	}
	if(unionFind[parent2] == unionFind[parent1])
	{
		unionFind[parent2]--;
	}
	numConnected[parent2] += numConnected[parent1]; 
	unionFind[parent1] = parent2;
}

int main ()
{
	//Consider a sequence of edges defined by the following formula:
	//for 1 <= k <= 55, sk = 100003 - 200003k + 300007k^3 mod 1000000
	//for larger, sk = s(k-24) + s(k-55) mod 1000000
	//Then in our graph, edge n goes between s(2n-1) and s(2n)
	//The vertices are the numbers from 0 to 999999
	//After how many edges will 99% of the vertices be connected 
	//to vertex 524287

	//Just use a union find data structure to track which vertices are 
	//connected to each other, and keep adding edges

	int goal = 524287;
	int threshold = 990000;
	int maintain = 55;
	unsigned long long ans = 0;
	int *unionFind = static_cast<int*>(malloc(sizeof(int) * limit));
	int *numConnected = static_cast<int*>(malloc(sizeof(int) * limit));
	for(int i = 0; i < limit; i++)
	{
		unionFind[i] = -1;
		numConnected[i] = 1;
	}
	int *fibs = static_cast<int*>(malloc(sizeof(int) * maintain));
	for(unsigned long long i = 1; i <= 55; i++)
	{
		fibs[i-1] = static_cast<int>((100003 - 200003*i + 300007*i*i*i) % limit);
	}
	for(int i = 0; i+1 < maintain; i += 2)
	{
		connect(unionFind, fibs[i], fibs[i+1], numConnected);
		if(fibs[i] != fibs[i+1])
		{
			ans++;
		}
	}
	int fib1 = (fibs[0] + fibs[maintain-24]) % limit;
	for(int i = 0; i < maintain-1; i++)
	{
		fibs[i] = fibs[i+1];
	}
	fibs[maintain-1] = fib1;
	connect(unionFind, fibs[maintain-2], fibs[maintain-1], numConnected);
	if(fibs[maintain-2] != fibs[maintain-1])
	{
		ans++;
	}
	while(numConnected[find(unionFind, goal)] < threshold)
	{
		fib1 = (fibs[0] + fibs[maintain-24]) % limit;
		for(int i = 0; i < maintain-1; i++)
		{
			fibs[i] = fibs[i+1];
		}
		fibs[maintain-1] = fib1;
		int fib2 = (fibs[0] + fibs[maintain-24]) % limit;
		for(int i = 0; i < maintain-1; i++)
		{
			fibs[i] = fibs[i+1];
		}
		fibs[maintain-1] = fib2;
		connect(unionFind, fib1, fib2, numConnected);
		if(fib1 != fib2)
		{
			ans++;
		}
	}
	free(unionFind);
	free(numConnected);
	free(fibs);
	std::cout << ans << '\n';
	return 0;
}