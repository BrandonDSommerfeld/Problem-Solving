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
#include "algorithms.cpp"

int main ()
{
    //Given a triangle, there is a point in the middle for which
    //The sum of the distances to each vertex is minimized, known as
    //the Toriicelli point
    //This is found by creating an equilateral triangle from each side
    //facing outwards, then circumscribing each of them, and they intersect
    //at the point
    //Find the sum of all distinct distance sums where all side lengths
    //and the interior distances to vertices are all integers

    static constexpr int limit = 120000;
    static constexpr int max = 1000;
    int total = 0;
        
    int a = 399;
    int b = 455;
    int c = 511;


    return 0;
}