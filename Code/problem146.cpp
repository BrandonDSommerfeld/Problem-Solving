#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <list>
#include <random>
#include <chrono>
#include <set>
#include <queue>
#include "math_unsigned.cpp"
#include "math_signed.cpp"
#include "algorithms.cpp"

int main ()
{
    //Find the sum of all numbers n below 150 million such that 
    //n^2+1, n^2+3, n^2+7, n^2+9, n^2+13, and n^2+27 are consecutive primes

    //For each prime, figure out acceptable remainders that when squared have none of the 
    //above divisible by that prime using modular arithmetic

    long long limit = 150000000;

    std::list<long long> acceptable{};

    algorithms::generatePrimes(150000000);

    acceptable.push_back(0);

    long long mod = 2;

    long long stopped = 0;
    for(long long i = 1; i < algorithms::primes.size() && mod < limit; i++)
    {
        bool* squarable = (bool*) malloc(sizeof(bool) * algorithms::primes[i]);
        for(long long j = 0; j < algorithms::primes[i]; j++)
        {
            bool works = true;
            long long square = j*j;
            if((square+1 != algorithms::primes[i] &&
                (square+1)%algorithms::primes[i] == 0)
                || (i == 2 && square == 4))
            {
                works = false;
            }
            if(square+3 != algorithms::primes[i] &&
                (square+3)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+7 != algorithms::primes[i] &&
                (square+7)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+9 != algorithms::primes[i] &&
                (square+9)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+13 != algorithms::primes[i] &&
                (square+13)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+27 != algorithms::primes[i] &&
                (square+27)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            squarable[j] = works;
        }

        //do mod stuff
        std::list<long long> temp{};
        for(auto iter = acceptable.begin(); iter != acceptable.end(); iter++)
        {
            for(int k = 0; k < algorithms::primes[i]; k++)
            {
                if(*iter + k*mod  < limit
                && squarable[(*iter + k*mod) % algorithms::primes[i]]
                )
                {
                    temp.push_back(*iter + k*mod);
                }
            }
        }
        acceptable = temp;
        mod *= algorithms::primes[i];
        stopped = i;
    }

    //We have now found all possible candidates, but some were 
    //Kept in by the "not equal to the prime check" when they should 
    //have been removed, so we go through and take those out
    for(long long i = 1; i <= stopped; i++)
    {
        bool* squarable = (bool*) malloc(sizeof(bool) * algorithms::primes[i]);
        for(auto iter = acceptable.begin(); iter != acceptable.end();)
        {
            bool works = true;
            long long square = (*iter) * (*iter);
            if((square+1 != algorithms::primes[i] &&
                (square+1)%algorithms::primes[i] == 0))
            {
                works = false;
            }
            if(square+3 != algorithms::primes[i] &&
                (square+3)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+7 != algorithms::primes[i] &&
                (square+7)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+9 != algorithms::primes[i] &&
                (square+9)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+13 != algorithms::primes[i] &&
                (square+13)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+27 != algorithms::primes[i] &&
                (square+27)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(!works)
            {
                iter = acceptable.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }

    //Remove numbers based on other primes dividing them
    for(long long i = stopped+1; i < algorithms::primes.size(); i++)
    {
        for(auto iter = acceptable.begin(); iter != acceptable.end();)
        {
            bool works = true;
            long long square = (*iter)*(*iter);
            if(square+1 != algorithms::primes[i] &&
                (square+1)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+3 != algorithms::primes[i] &&
                (square+3)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+7 != algorithms::primes[i] &&
                (square+7)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+9 != algorithms::primes[i] &&
                (square+9)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+13 != algorithms::primes[i] &&
                (square+13)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(square+27 != algorithms::primes[i] &&
                (square+27)%algorithms::primes[i] == 0)
            {
                works = false;
            }
            if(!works)
            {
                iter = acceptable.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }

    long long total = 0;
    //Ensure that the primes are actually consecutive
    //Everything else is already checked by other things, such as 
    //the +5 cannot be prime because only numbers which are 0 mod 
    //5 are still in at this stage
    for(auto iter = acceptable.begin(); iter != acceptable.end(); )
    {
        if(algorithms::isPrime((*iter) * (*iter) + 21))
        {
            iter = acceptable.erase(iter);
        }
        else
        {
            std::cout << *iter << '\n';
            total += *iter;
            iter++;
        }
    }
    std::cout << total << '\n';

    return 0;
}