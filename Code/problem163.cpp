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

static constexpr int len = 1;

//The various directions that lines can go, measured from 
//the negative x axis
enum class direction
{
    THIRTY,
    SIXTY,
    NINETY,
    ONETWENTY,
    ONEFIFTY,
    STRAIGHT
};


int main ()
{
    //Consider an equilateral triangle with lines drawn from each vertex to the midpoint
    //If we consider these lines, there are 16 different triangles 
    //which can be selected from within this

    //Then consider stacking these triangles into larger equilateral triangles
    //If the starting triangle has side length 1, stack them until you have
    //an equilateral triangle with side length 36
    //Find the number of sub triangles within this

    unsigned long long total = 0;
    //Need to be careful for the columns
    std::cout << total << '\n';
    return 0;
}