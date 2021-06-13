#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <queue>
#include <list>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "math_rational.cpp"
#include "math_fast_rational.cpp"
#include "algorithms.cpp"

struct pair
{
    int num1;
    int num2;
};

bool operator< (const pair& p1, const pair& p2)
{
    if(p1.num1 < p2.num1) return true;
    if(p1.num1 > p2.num1) return false;
    return p1.num2 < p2.num2;
}

struct triple
{
    int num1;
    int num2;
    int num3;
};

bool operator< (const triple& p1, const triple& p2)
{
    if(p1.num1 < p2.num1) return true;
    if(p1.num1 > p2.num1) return false;
    if(p1.num2 < p2.num2) return true;
    if(p1.num2 > p2.num2) return false;
    return p1.num3 < p2.num3;
}

struct four
{
    int num1;
    int num2;
    int num3;
    int num4;
};

bool operator< (const four& p1, const four& p2)
{
    if(p1.num1 < p2.num1) return true;
    if(p1.num1 > p2.num1) return false;
    if(p1.num2 < p2.num2) return true;
    if(p1.num2 > p2.num2) return false;
    if(p1.num3 < p2.num3) return true;
    if(p1.num3 > p2.num3) return false;
    return p1.num4 < p2.num4;
}

static std::vector<std::set<four>> possibleRows{};
static std::vector<std::set<triple>> triples{};
static std::vector<std::set<pair>> pairs{};

unsigned long long solve (int** board, int row, int sum)
{
    unsigned long long total = 0;
    switch(row)
    {
        case 0:
        for(auto iter = possibleRows[sum].begin(); iter != possibleRows[sum].end(); iter++)
        {
            board[0][0] = iter->num1;
            board[0][1] = iter->num2;
            board[0][2] = iter->num3;
            board[0][3] = iter->num4;
            total += solve(board, 1, sum);
        }
        break;
        case 1:
        for(auto iter = possibleRows[sum].begin(); iter != possibleRows[sum].end(); iter++)
        {
            board[1][0] = iter->num1;
            board[1][1] = iter->num2;
            board[1][2] = iter->num3;
            board[1][3] = iter->num4;
            pair p{board[0][0], board[1][0]};
            if(pairs[sum].count(p) > 0)
            {
                p = pair{board[0][1], board[1][1]};
                if(pairs[sum].count(p) > 0)
                {
                    p = pair{board[0][2], board[1][2]};
                    if(pairs[sum].count(p) > 0)
                    {
                        p = pair{board[0][3], board[1][3]};
                        if(pairs[sum].count(p) > 0)
                        {
                            p = pair{board[0][0], board[1][1]};
                            if(pairs[sum].count(p) > 0)
                            {
                                p = pair{board[0][3], board[1][2]};
                                if(pairs[sum].count(p) > 0)
                                {
                                    total += solve(board, 2, sum);
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
        case 2:
        for(auto iter = possibleRows[sum].begin(); iter != possibleRows[sum].end(); iter++)
        {
            board[2][0] = iter->num1;
            board[2][1] = iter->num2;
            board[2][2] = iter->num3;
            board[2][3] = iter->num4;
            triple p{board[0][0], board[1][0], board[2][0]};
            if(triples[sum].count(p) > 0)
            {
                p = triple{board[0][1], board[1][1], board[2][1]};
                if(triples[sum].count(p) > 0)
                {
                    p = triple{board[0][2], board[1][2], board[2][2]};
                    if(triples[sum].count(p) > 0)
                    {
                        p = triple{board[0][3], board[1][3], board[2][3]};
                        if(triples[sum].count(p) > 0)
                        {
                            p = triple{board[0][0], board[1][1], board[2][2]};
                            if(triples[sum].count(p) > 0)
                            {
                                p = triple{board[0][3], board[1][2], board[2][1]};
                                if(triples[sum].count(p) > 0)
                                {
                                    total += solve(board, 3, sum);
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
        case 3:
        for(auto iter = possibleRows[sum].begin(); iter != possibleRows[sum].end(); iter++)
        {
            board[3][0] = iter->num1;
            board[3][1] = iter->num2;
            board[3][2] = iter->num3;
            board[3][3] = iter->num4;
            four p{board[0][0], board[1][0], board[2][0], board[3][0]};
            if(possibleRows[sum].count(p) > 0)
            {
                p = four{board[0][1], board[1][1], board[2][1], board[3][1]};
                if(possibleRows[sum].count(p) > 0)
                {
                    p = four{board[0][2], board[1][2], board[2][2], board[3][2]};
                    if(possibleRows[sum].count(p) > 0)
                    {
                        p = four{board[0][3], board[1][3], board[2][3], board[3][3]};
                        if(possibleRows[sum].count(p) > 0)
                        {
                            p = four{board[0][0], board[1][1], board[2][2], board[3][3]};
                            if(possibleRows[sum].count(p) > 0)
                            {
                                p = four{board[0][3], board[1][2], board[2][1], board[3][0]};
                                if(possibleRows[sum].count(p) > 0)
                                {
                                    total ++;
                                }
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    return total;
}

int main ()
{
    //How many 4x4 grids with numbers 0-9 have all rows, columns, 
    //and both diagonals with the same sum?

    int maxSum = 36;
    for(int i = 0; i <= maxSum; i++)
    {
        possibleRows.push_back(std::set<four>{});
        triples.push_back(std::set<triple>{});
        pairs.push_back(std::set<pair>{});
    }

    for(int num1 = 0; num1 < 10; num1++)
    {
        for(int num2 = 0; num2 < 10; num2++)
        {
            for(int num3 = 0; num3 < 10; num3++)
            {
                for(int num4 = 0; num4 < 10; num4++)
                {
                    four row{num1,num2,num3,num4};
                    possibleRows[num1+num2+num3+num4].insert(row);
                    triple t{num1,num2,num3};
                    triples[num1+num2+num3+num4].insert(t);
                    pair p{num1, num2};
                    pairs[num1+num2+num3+num4].insert(p);
                }
            }
        }
    }

    int** board = (int**) calloc(sizeof(int*), 4);
    for(int i = 0; i < 4; i++)
    {
        board[i] = (int*) calloc(sizeof(int), 4);
    }
    unsigned long long total = 0;
    for(int i = 0; i < 18; i++)
    {
        std::cout << i << '\n';
        total += solve(board, 0, i);
    }
    total *= 2;
    std::cout << total << '\n';
    total += solve(board, 0, 18);
    std::cout << total << '\n';
    return 0;
}