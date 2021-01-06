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

struct pair
{
    int vertex;
    int weight;
};

bool operator< (pair p1, pair p2)
{
    return p1.weight > p2.weight;
}


int main ()
{
    //Problem has a text file, which stores a graph as a matrix
    //Find the weight of the minimum spanning tree of the graph

    //Use Prim's algorithm for minimum spanning trees

    std::priority_queue<pair> q{};
    
    std::ifstream inf{"p107_network.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }

    int graph[40][40];
    int row = 0;
    for(std::string in; std::getline(inf, in); )
    {
        int current = 0;
        int loc = 0;
        for(int i = 0; i < in.length(); i++)
        {
            if(in[i] == ',')
            {
                graph[row][loc] = current;
                current = 0;
                loc++;
            }
            else if (in[i] != '-')
            {
                current *= 10;
                current += in[i]-48;
            }
        }
        graph[row][loc] = current;
        row++;
    }

    int other = 0;
    for(int i = 0; i < 40; i++)
    {
        for(int j = i; j < 40; j++)
        {
            other += graph[i][j];
        }
    }
    int total = 0;
    bool visited[40];
    for(int i = 0; i < 40; i++)
    {
        if(graph[0][i] != 0)
        {
            pair temp{};
            temp.vertex = i;
            temp.weight = graph[0][i];
            q.push(temp);
        }
        visited[i] = false;
    }
    visited[0] = true;
    while(!q.empty())
    {
        pair current = q.top();
        q.pop();
        if(!visited[current.vertex])
        {
            visited[current.vertex] = true;
            total += current.weight;
            for(int i = 0; i < 40; i++)
            {
                if(!visited[i] && graph[i][current.vertex] != 0)
                {
                    pair temp{};
                    temp.vertex = i;
                    temp.weight = graph[i][current.vertex];
                    q.push(temp);
                }
            }
        }
    }
    std::cout << other << '\n';
    std::cout << other - total << '\n';
    return 0;
}