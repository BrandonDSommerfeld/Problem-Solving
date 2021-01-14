#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include "math_unsigned.cpp"
#include "math_signed.cpp"

struct frame
{
    int multiplications;
    int val;
    std::vector<int> used;
};

bool operator< (frame f1, frame f2)
{
    return f1.multiplications > f2.multiplications;
}

int main ()
{
    //For numbers 1 to 200, what is the most efficient way to compute
    // x^n
    //Generally, binary where you computing x^2, x^4, x^8, ...
    //and combining is pretty good, but it isn't always the best

    //Try using some kind of djikstra's
    //from n on this

    //Compute the "distance" from n for each value
    //With a BFS algorithm
    //Allow for ties to go in because sometimes the
    //multiplications used to get there matter
    
    int required[201];
    for(int i = 0; i <= 200; i++)
    {
        required[i] = 0;
    }
    int total = 0;
    std::priority_queue<frame> q{};
    frame start;
    start.multiplications = 0;
    start.val = 1;
    start.used = *(new std::vector<int>{});
    start.used.push_back(1);
    q.push(start);
    while(!q.empty())
    {
        frame current = q.top();
        q.pop();
        if(required[current.val] == 0 ||
        required[current.val] >= current.multiplications)
        {
            required[current.val] = current.multiplications;

            for(int i = 0; i < current.used.size(); i++)
            {
                frame temp{};
                temp.multiplications = current.multiplications+1;
                temp.val = current.val + current.used[i];
                if(temp.val <= 200)
                {
                    temp.used = *(new std::vector<int>{});
                    for(int j = 0; j < current.used.size(); j++)
                    {
                        temp.used.push_back(current.used[j]);
                    }
                    temp.used.push_back(temp.val);
                    q.push(temp);
                }
            }
        }
    }

    for(int i = 1; i <= 200; i++)
    {
        total += required[i];
    }
    std::cout << total << '\n';

    return 0;
}