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
    //For all lattice points from 0 <= x,y <= 50, 
    //how many right triangles can be formed
    //from 2 points, and the origin

    //Iterate over all placements of the points, 
    //And use dot product to look for right angles

    static constexpr int limit = 50;
    int total = 0;
    for(int x1 = 0; x1 <= limit; x1++)
    {
        for(int y1 = 0; y1 <= limit; y1++)
        {
            if(x1 != 0 || y1 != 0)
            {
                for(int x2 = x1; x2 <= limit; x2++)
                {
                    //Ensures we don't count twice
                    int start = 0;
                    if(x1 == x2)
                    {
                        start = y1;
                    }
                    for(int y2 = start; y2 <= limit; y2++)
                    {
                        if((x1 != x2 || y1 != y2) && !(x2 == 0 && y2==0))
                        {
                            if(x1*x2+y1*y2==0)
                            {
                                
                                total++;
                            }
                            else if (x1*(x2-x1)+y1*(y2-y1)==0)
                            {
                                
                                total++;
                            }
                            else if (x2*(x2-x1)+y2*(y2-y1)==0)
                            {
                                
                                total++;
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << total << '\n';
    return 0;
}