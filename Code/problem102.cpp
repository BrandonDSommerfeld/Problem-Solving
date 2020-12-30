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

int main ()
{
    //Problem has a file with a lot of triangles:
    //Determine how many contain the origin

    //Use some cross product stuff to determine whether the
    //origin is on the left or right of each side

    std::ifstream inf{"p102_triangles.txt"};
    if(!inf)
    {
        std::cout << "Couldn't find file\n";
        return 1;
    }

    for(std::string in; std::getline(inf, in); )
    {
        
    }
    return 0;
}