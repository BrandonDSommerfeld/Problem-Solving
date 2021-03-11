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
    /*
    We have the ellipse defined by 4x^2+y^2 = 100
    and the top section for -0.01 <= x <= 0.01 has been cut out 
    Then we take a beam of light starting at (0,10.1) 
    which goes to (1.4,-9.6) before it bounces off. 
    Find how many times it bounces before it leaves
    */

    /*
    We use the law of reflection, that the angle made with the 
    normal vector coming in is equal to the 
    angle going out. The normal vector to the ellipse 
    has slope y/4x by easy calculus, so the loop repeatedly 
    follows a given direction until it hits the ellipse 
    again, using quadratic formula. Then, it calculates 
    the slope after it reflects using the dot product, 
    and finding the unit vector which has the 
    same dot product, and thus same angle, with the 
    normal vector as the incoming slope.
    */

    double x = 1.4;
    double y = -9.6;
    double slope = (-9.6-10.1)/1.4;
    long long count = 0;
    
    double normal = y/(4*x);

    double len = std::sqrt(1+slope*slope);
    double unitSx = -1 / len;
    double unitSy = -slope / len;

    double dot = unitSx + unitSy*normal;

    double dis = std::sqrt(normal*normal-dot*dot+1);
    double y1 = (normal*dot+dis)/(normal*normal+1);
    double y2 = (normal*dot-dis)/(normal*normal+1);
    if(std::abs(unitSy - y1) < 0.0001)
    {
        slope = (y2) / (dot-y2*normal);
    }
    else
    {
        slope = (y1) / (dot-y1*normal);
    }
    while(true)
    {
        if(-0.01 <= x && x <= 0.01 && y > 0)
        {
            std::cout << count << '\n';
            break;
        }

        double a = slope*slope+4;
        double b = 2*slope*(y-slope*x);
        double c = (slope*slope*x*x-2*slope*x*y+y*y-100);

        dis = std::sqrt(b*b-4*a*c);
        double x1 = (-b+dis)/(2*a);
        double x2 = (-b-dis)/(2*a);
        if(std::abs(x-x1) < 0.0001)
        {
            y = slope*(x2-x) + y;
            x = x2;
        }
        else
        {
            y = slope*(x1-x) + y;
            x = x1;
        }

        

        normal = y/(4*x);

        len = std::sqrt(1+slope*slope);
        unitSx = -1 / len;
        unitSy = -slope / len;

        dot = unitSx + unitSy*normal;

        dis = std::sqrt(normal*normal-dot*dot+1);
        y1 = (normal*dot+dis)/(normal*normal+1);
        y2 = (normal*dot-dis)/(normal*normal+1);
        if(std::abs(unitSy - y1) < 0.0001)
        {
            slope = (y2) / (dot-y2*normal);
        }
        else
        {
            slope = (y1) / (dot-y1*normal);
        }

        count++;
    }

    return 0;
}