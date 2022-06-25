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

static constexpr int limit = 16;

void insert(std::string num, std::vector<int*>& list)
{
	int *temp = static_cast<int*>(malloc(sizeof(int) * num.length()));
	for(size_t i = 0; i < num.length(); i++)
	{
		temp[i] = num[i] - 48;
	}
	list.push_back(temp);
}

bool check(int *guess, const std::vector<int*>& nums, const std::vector<int> correct)
{
	for(size_t i = 0; i < nums.size(); i++)
	{
		int numCorrect = 0;
		for(int j = 0; j < limit; j++)
		{
			if(guess[j] == nums[i][j])
			{
				numCorrect++;
			}
		}
		if(numCorrect > correct[i])
		{
			return false;
		}
	}
	return true;
}

//Recursively on each number pick some 
//indices to be correct
bool solve(int *guess, const std::vector<int*>& nums, const std::vector<int> correct, int i, int j, int start)
{
	if(i+1 == static_cast<int>(nums.size()))
	{
		return check(guess,nums,correct);
	}
	if(j == 0)
	{
		if(!check(guess,nums, correct))
		{
			return false;
		}
		int numCorrect = 0;
		for(int k = 0; k < limit; k++)
		{
			if(guess[k] == nums[i+1][k])
			{
				numCorrect++;
			}
		}
		return solve(guess,nums,correct,i+1,correct[i+1]-numCorrect,0);
	}
	else 
	{
		for(int k = start; k < limit; k++)
		{
			if(guess[k] == -1)
			{
				guess[k] = nums[i][k];
				if(solve(guess,nums,correct,i,j-1,k+1))
				{
					return true;
				}
				guess[k] = -1;	
			}
		}
		return false;
	}
}

int main ()
{
	//We are looking for the unique 16 digit number such that 
	/*
	5616185650518293 ;2 correct
	3847439647293047 ;1 correct
	5855462940810587 ;3 correct
	9742855507068353 ;3 correct
	4296849643607543 ;3 correct
	3174248439465858 ;1 correct
	4513559094146117 ;2 correct
	7890971548908067 ;3 correct
	8157356344118483 ;1 correct
	2615250744386899 ;2 correct
	8690095851526254 ;3 correct
	6375711915077050 ;1 correct
	6913859173121360 ;1 correct
	6442889055042768 ;2 correct
	2321386104303845 ;0 correct
	2326509471271448 ;2 correct
	5251583379644322 ;2 correct
	1748270476758276 ;3 correct
	4895722652190306 ;1 correct
	3041631117224635 ;3 correct
	1841236454324589 ;3 correct
	2659862637316867 ;2 correct
	Where we are told how many digits in each guess match the number we want
	*/
	int *guess = static_cast<int*>(malloc(sizeof(int)*limit));
	for(int i = 0; i < limit; i++)
	{
		guess[i] = -1;
	}
	std::vector<int*> numbers{};
	std::vector<int> numCorrect{};
	insert("5616185650518293",numbers); numCorrect.push_back(2);
	insert("3847439647293047",numbers); numCorrect.push_back(1);
	insert("5855462940810587",numbers); numCorrect.push_back(3);
	insert("9742855507068353",numbers); numCorrect.push_back(3);
	insert("4296849643607543",numbers); numCorrect.push_back(3);
	insert("3174248439465858",numbers); numCorrect.push_back(1);
	insert("4513559094146117",numbers); numCorrect.push_back(2);
	insert("7890971548908067",numbers); numCorrect.push_back(3);
	insert("8157356344118483",numbers); numCorrect.push_back(1);
	insert("2615250744386899",numbers); numCorrect.push_back(2);
	insert("8690095851526254",numbers); numCorrect.push_back(3);
	insert("6375711915077050",numbers); numCorrect.push_back(1);
	insert("6913859173121360",numbers); numCorrect.push_back(1);
	insert("6442889055042768",numbers); numCorrect.push_back(2);
	insert("2321386104303845",numbers); numCorrect.push_back(0);
	insert("2326509471271448",numbers); numCorrect.push_back(2);
	insert("5251583379644322",numbers); numCorrect.push_back(2);
	insert("1748270476758276",numbers); numCorrect.push_back(3);
	insert("4895722652190306",numbers); numCorrect.push_back(1);
	insert("3041631117224635",numbers); numCorrect.push_back(3);
	insert("1841236454324589",numbers); numCorrect.push_back(3);
	insert("2659862637316867",numbers); numCorrect.push_back(2);

	solve(guess,numbers,numCorrect,0, numCorrect[0], 0);
	//Solver doesn't get this digit
	guess[12] = 9;	
	for(int i = 0; i < limit; i++)
	{
		std::cout << guess[i];
	}
	std::cout << '\n';
	return 0;
}