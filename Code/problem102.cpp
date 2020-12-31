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

inline int crossProduct(int x1, int y1, int x2, int y2)
{
    return x1*y2 - x2*y1;
}

int main ()
{
    //Problem has a file with a lot of triangles:
    //Determine how many contain the origin

    //Use some cross product stuff to determine whether the
    //origin is on the left or right of each side
    //Only inside if it is left of all sides, or right of all sides
    //Which means all cross products must be the same sign

    std::ifstream inf{"p102_triangles.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }

    int total = 0;
    for(std::string in; std::getline(inf, in); )
    {
        int points[6];
        int current{};
        bool positive = true;
        int loc = 0;
        for(int i = 0; i < 6; i++)
        {
            while(loc < in.length() && in[loc] != ',')
            {
                if(in[loc] == '-')
                {
                    positive = false;
                }
                else
                {
                    current = current*10 + in[loc]-48;
                }
                loc++;
            }
            points[i] = current;
            if(!positive)
            {
                points[i] *= -1;
            }
            current = 0;
            positive = true;
            loc++;
        }

        int c1 = crossProduct(points[0], points[1], points[2], points[3]);
        int c2 = crossProduct(points[2], points[3], points[4], points[5]);
        int c3 = crossProduct(points[4], points[5], points[0], points[1]);

        if(c1 >= 0 && c2 >= 0 && c3 >= 0)
        {
            total++;
        }
        else if(c1 <= 0 && c2 <= 0 && c3 <= 0)
        {
            total++;
        }
    }
    std::cout << total << '\n';
    return 0;
}