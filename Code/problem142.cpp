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
    //Find the numbers x,y,z with x > y > z > 0 such that
    //each pairwise sum and difference is a perfect square
    //Find the triplet with minimum sum

    //The differences x-y, y-z, x-z form a pythagorean triple
    //Then, we have the numbers z, z+a^2, z+c^2
    //Thus, once the triple is formed, look for z such that
    //2z+a^2, 2z+c^2, and 2z+a^2+c^2 are all square
    //Do this by considering square numbers above c^2, and using
    //the z needed to reach that square, then check other 2
    //Also, do this with z, z+b^2, z+c^2
    //because the order of a,b does not matter
    
    int best = 3000000;
    for(int m = 2; m*m*m*m < best; m++)
    {
        for(int n = 1; n < m; n++)
        {
            if((m+n)%2 == 1 && algorithms::gcd(m,n) == 1)
            {
                for(int k = 1; 2*k*k*(m*m*m*m+n*n*n*n) < best; k++)
                {
                    //std::cout << m << ' ' << n << ' ' << k << '\n';
                    int a = k*(m*m-n*n);
                    int b = 2*k*m*n;
                    int c = k*(m*m+n*n);
                    int z = 2;
                    int count = 0;
                    while(3*z+a*a+c*c < best)
                    {
                        if(algorithms::isSquare(2*z+a*a) &&
                        algorithms::isSquare(2*z+a*a+c*c))
                        {
                            std::cout << z << ' ' << z+a*a << ' ' << z+c*c << '\n';
                            if(best > 3*z+a*a+c*c)
                            {
                                best = 3*z+a*a+c*c;
                            }
                        }
                        count += 2;
                        z = count*c + count*count/2;
                    }

                    z = 2;
                    count = 0;
                    while(3*z+b*b+c*c < best)
                    {
                        if(algorithms::isSquare(2*z+b*b) &&
                        algorithms::isSquare(2*z+b*b+c*c))
                        {
                            std::cout << z << ' ' << z+b*b << ' ' << z+c*c << '\n';
                            if(best > 3*z+b*b+c*c)
                            {
                                best = 3*z+b*b+c*c;
                            }
                        }
                        count += 2;
                        z = count*c + count*count/2;
                    }
                }
            }
        }
    }
    std::cout << best << '\n';
    return 0;
}