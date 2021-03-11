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
    //the Torricelli point
    //This is found by creating an equilateral triangle from each side
    //facing outwards, then circumscribing each of them, and they intersect
    //at the point
    //Find the sum of all distinct distance sums where all side lengths
    //and the interior distances to vertices are all integers

    //Takes a little while, answer is 30758397
    //This comes from helpful wikipedia, which 
    //notes that if you draw the lines from the vertices 
    //to the Torricelli point, they meet at 60 degree angles
    //Then by the law of cosines, if we denote the the distances 
    //to the Torricelli point as p,q,r, we can compute the 
    //side lengths a,b,c in terms of them.
    //Finally, we have a check on a,b,c to ensure 
    //the triangle actually has no angle bigger than 120 degrees
    //using the law of cosines

    int limit = 120000;
    long long total = 0;
    bool* used = (bool*) calloc(limit, sizeof(bool));
    for(long long p = 1; p < limit; p++)
    {
        for(long long q = 1; q <= p && q+p < limit; q++)
        {
            long long c = (long long)
            std::sqrt(p*p+p*q+q*q);
            if(c*c == p*p+p*q+q*q)
            {
                long long start = 1;
                while (c*c < q*q+q*start+p*p+p*start+2*start*start)
                {
                    start *= 2;
                }
                start /= 2;
                start++;
                for(long long r = start; r <= q && p+q+r < limit; r++)
                {
                    long long a = (long long) std::sqrt(q*q+q*r+r*r);
                    long long b = (long long) std::sqrt(p*p+p*r+r*r);
                    if(!used[p+q+r]
                    && c*c <= a*a+b*b+a*b
                    && a*a == q*q+q*r+r*r
                    && b*b == p*p+p*r+r*r
                    )
                    {
                        std::cout << p << ' ' << q << ' ' << r << '\n';
                        total += p+q+r;
                        used[p+q+r] = true;
                    }
                }
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}