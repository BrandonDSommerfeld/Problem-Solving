#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include "math_unsigned.cpp"

int main ()
{
    //Find the most likely squares to end up on in
    //monopoly if you roll 2 4 sided dice

    int visited[40];
    for(int i = 0; i < 40; i++)
    {
        visited[i] = 0;
    }

    std::mt19937 rng{};
    

    //Run simulations of a bunch of moves
    //Honestly hardest part was properly seeding and
    //Not missing any cases
    int loc = 0;
    int pairs = 0;
    for(int j = 0; j < 10; j++)
    {
        rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
        for(int i = 0; i < 100000; i++)
        {
            int roll1 = (rng() % 4)+1;
            int roll2 = (rng() % 4)+1;
            if(roll1 == roll2)
            {
                pairs++;
                if(pairs == 3)
                {
                    pairs = 0;
                    loc = 10;
                    visited[10]++;
                    continue;
                }
            }
            else
            {
                pairs = 0;
            }
            loc = (loc+roll1+roll2) % 40;
            if(loc == 2 || loc == 17 || loc == 33)
            {
                int card = rng() % 16;
                if(card == 0)
                {
                    loc = 0;
                }
                else if (card == 1)
                {
                    loc = 10;
                }
            }
            else if(loc == 30)
            {
                loc = 10;
            }
            else if (loc == 7)
            {
                int card = rng() % 16;
                switch(card)
                {
                    case 0:
                        loc = 0;
                        break;
                    case 1:
                        loc = 10;
                        break;
                    case 2:
                        loc = 11;
                        break;
                    case 3:
                        loc = 24;
                        break;
                    case 4:
                        loc = 39;
                        break;
                    case 5:
                        loc = 5;
                        break;
                    //Next railroad, depends
                    case 6:
                    case 7:
                        loc = 15;
                        break;
                    //Next utility, depends
                    case 8:
                        loc = 12;
                        break;
                    case 9:
                        loc -= 3;
                        break;
                }
            }
            else if (loc == 22)
            {
                int card = rng() % 16;
                switch(card)
                {
                    case 0:
                        loc = 0;
                        break;
                    case 1:
                        loc = 10;
                        break;
                    case 2:
                        loc = 11;
                        break;
                    case 3:
                        loc = 24;
                        break;
                    case 4:
                        loc = 39;
                        break;
                    case 5:
                        loc = 5;
                        break;
                    //Next railroad, depends
                    case 6:
                    case 7:
                        loc = 25;
                        break;
                    //Next utility, depends
                    case 8:
                        loc = 28;
                        break;
                    case 9:
                        loc -= 3;
                        break;
                }
            }
            else if (loc == 36)
            {
                int card = rng() % 16;
                switch(card)
                {
                    case 0:
                        loc = 0;
                        break;
                    case 1:
                        loc = 10;
                        break;
                    case 2:
                        loc = 11;
                        break;
                    case 3:
                        loc = 24;
                        break;
                    case 4:
                        loc = 39;
                        break;
                    case 5:
                        loc = 5;
                        break;
                    //Next railroad, depends
                    case 6:
                    case 7:
                        loc = 5;
                        break;
                    //Next utility, depends
                    case 8:
                        loc = 12;
                        break;
                    case 9:
                        loc -= 3;
                        break;
                }
            }
            visited[loc]++;
        }
    }
    
    int first = 0;
    int second = 0;
    int third = 0;
    int loc1 = 0;
    int loc2 = 0;
    int loc3 = 0;
    for(int i = 0; i < 40; i++)
    {
        std::cout << i << ' ' << visited[i] << '\n';
        if(visited[i] > first)
        {
            third = second;
            second = first;
            first = visited[i];
            loc3 = loc2;
            loc2 = loc1;
            loc1 = i;
        }
        else if(visited[i] > second)
        {
            third = second;
            second = visited[i];
            loc3 = loc2;
            loc2 = i;
        }
        else if (visited[i] > third)
        {
            third = visited[i];
            loc3 = i;
        }
    }
    std::cout << loc1 << ' ' << loc2 << ' ' << loc3 << '\n';
    return 0;
}