#ifndef ALGORITHMS_H
#define ALGORITHMS_H

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

namespace algorithms
{
    static bool *composite;
    static std::vector<long long> primes;

    void generatePrimes(long long limit)
    {
        composite = new bool[limit];
        for(long long i{2}; i*i < limit; i++)
        {
            if(!composite[i])
            {
                for(long long j{2}; i*j < limit; j++)
                {
                    composite[i*j] = true;
                }
            }
        }

        for(long long i = 2; i < limit; i++)
        {
            if(!composite[i])
            {
                primes.push_back(i);
            }
        }
    }

    long long totient (long long num)
    {
        long long ans = num;
        for(size_t i = 0; i < primes.size () && primes[i] * primes[i] <= num; i++)
        {
            if(num % primes[i] == 0)
            {
                num /= primes[i];
                ans /= primes[i];
                ans *= primes[i]-1;
            }
            while(num % primes[i] == 0)
            {
                num /= primes[i];
            }
        }
        if(num > 1)
        {
            ans /= num;
            ans *= num-1;
        }
        return ans;
    }

    math::Unsigned totient (math::Unsigned num)
    {
        math::Unsigned ans = num;
        for(size_t i = 0; i < primes.size () && primes[i] * primes[i] <= num; i++)
        {
            if(num % primes[i] == 0)
            {
                num /= primes[i];
                ans /= primes[i];
                ans *= primes[i]-1;
            }
            while(num % primes[i] == 0)
            {
                num /= primes[i];
            }
        }
        if(num > 1)
        {
            ans /= num;
            ans *= num-1;
        }
        return ans;
    }

    std::vector<int>* factors (int num)
    {
        std::vector<int> *ans = new std::vector<int>{};
        for(size_t i = 0; i < primes.size() && primes[i] * primes[i] <= num; i++)
        {
            if(num % primes[i] == 0)
            {
                num /= primes[i];
                ans->push_back(primes[i]);
            }
            while(num % primes[i] == 0)
            {
                num /= primes[i];
            }
        }
        if(num > 1)
        {
            ans->push_back(num);
        }
        return ans;
    }

    std::vector<math::Unsigned>* factors (math::Unsigned num)
    {
        std::vector<math::Unsigned> *ans = new std::vector<math::Unsigned>{};
        for(size_t i = 0; i < primes.size() && primes[i] * primes[i] <= num; i++)
        {
            if(num % primes[i] == 0)
            {
                num /= primes[i];
                ans->push_back(primes[i]);
            }
            while(num % primes[i] == 0)
            {
                num /= primes[i];
            }
        }
        if(num > 1)
        {
            ans->push_back(num);
        }
        return ans;
    }

    long long exp(long long base, int exponent, int mod)
    {
        long long ans = 1;
        while(exponent > 0)
        {
            if(exponent % 2 == 1)
            {
                ans = (ans*base) % mod;
            }
            base = (base * base) % mod;
            exponent /= 2;
        }
        return ans;
    }

    long long exp(long long base, int exponent)
    {
        long long ans = 1;
        while(exponent > 0)
        {
            if(exponent % 2 == 1)
            {
                ans = (ans*base);
            }
            base = (base * base);
            exponent /= 2;
        }
        return ans;
    }

    unsigned long long exp(unsigned long long base, int exponent)
    {
        unsigned long long ans = 1;
        while(exponent > 0)
        {
            if(exponent % 2 == 1)
            {
                ans = (ans*base);
            }
            base = (base * base);
            exponent /= 2;
        }
        return ans;
    }

    math::Unsigned exp(math::Unsigned base, math::Unsigned exponent, math::Unsigned mod)
    {
        math::Unsigned ans = 1;
        while(exponent > 0)
        {
            if(exponent % 2 == 1)
            {
                ans *= base;
                ans %= mod;
            }
            base *= base;
            base %= mod;
            exponent /= 2;
        }
        return ans;
    }

    math::Signed exp(math::Signed base, math::Signed exponent)
    {
        math::Signed ans = 1;
        while(exponent > 0)
        {
            if(exponent % 2 == 1)
            {
                ans *= base;
            }
            base *= base;
            exponent /= 2;
        }
        return ans;
    }

    math::Unsigned exp(math::Unsigned base, math::Unsigned exponent)
    {
        math::Unsigned ans = 1;
        while(exponent > 0)
        {
            if(exponent % 2 == 1)
            {
                ans *= base;
            }
            base *= base;
            exponent /= 2;
        }
        return ans;
    }

    math::Unsigned recursiveSqrt(math::Unsigned low, math::Unsigned high,
    math::Unsigned num)
    {
        if(low == high || low == high-1)
        {
            return low;
        }
        math::Unsigned mid = (low+high)/2;
        math::Unsigned guess = mid*mid;
        if(guess < num)
        {
            return recursiveSqrt(mid, high, num);
        }
        if(guess > num)
        {
            return recursiveSqrt(low, mid-1, num);
        }
        return mid;
    }

    math::Unsigned sqrt(math::Unsigned num)
    {
        math::Unsigned guess = 1;
        while(guess*guess < num)
        {
            guess *= 2;
        }
        return recursiveSqrt(guess/2, guess, num);
    }

    bool recursiveIsNthPower(math::Unsigned low, math::Unsigned high,
    math::Unsigned num, int n)
    {
        if(low == high)
        {
            return exp(low, n) == num;
        }
        math::Unsigned mid = (low+high)/2;
        math::Unsigned guess = exp(mid, n);
        if(guess < num)
        {
            return recursiveIsNthPower(mid+1, high, num, n);
        }
        if(guess > num)
        {
            return recursiveIsNthPower(low, mid, num, n);
        }
        return true;
    }

    bool recursiveIsNthPower(unsigned long long low, unsigned long long high,
    unsigned long long num, int n)
    {
        if(low == high)
        {
            return exp(low, n) == num;
        }
        unsigned long long mid = (low+high)/2;
        unsigned long long guess = exp(mid, n);
        if(guess < num)
        {
            return recursiveIsNthPower(mid+1, high, num, n);
        }
        if(guess > num)
        {
            return recursiveIsNthPower(low, mid, num, n);
        }
        return true;
    }

    bool isNthPower(unsigned long long num, int n)
    {
        unsigned long long guess = 1;
        while(exp(guess, n) <= num)
        {
            guess *= 2;
        }
        return recursiveIsNthPower(guess/2, guess, num, n);
    }

    bool isNthPower(math::Unsigned num, int n)
    {
        math::Unsigned guess = 1;
        while(exp(guess, n) <= num)
        {
            guess *= 2;
        }
        return recursiveIsNthPower(guess/2, guess, num, n);
    }

    math::Unsigned recursiveNthRoot(math::Unsigned low, math::Unsigned high,
    math::Unsigned num, int n)
    {
        if(low == high || low == high-1)
        {
            return low;
        }
        math::Unsigned mid = (low+high)/2;
        math::Unsigned guess = exp(mid, n);
        if(guess < num)
        {
            return recursiveNthRoot(mid, high, num, n);
        }
        if(guess > num)
        {
            return recursiveNthRoot(low, mid, num, n);
        }
        return mid;
    }

    math::Unsigned nthRoot(math::Unsigned num, int n)
    {
        math::Unsigned guess = 1;
        while(exp(guess, n) <= num)
        {
            guess *= 2;
        }
        return recursiveNthRoot(guess/2, guess, num, n);
    }

    unsigned long long recursiveNthRoot(unsigned long long low, unsigned long long high,
    unsigned long long num, int n)
    {
        if(low == high || low == high-1)
        {
            return low;
        }
        unsigned long long mid = (low+high)/2;
        unsigned long long guess = exp(mid, n);
        if(guess < num)
        {
            return recursiveNthRoot(mid, high, num, n);
        }
        if(guess > num)
        {
            return recursiveNthRoot(low, mid, num, n);
        }
        return mid;
    }

    unsigned long long nthRoot(unsigned long long num, int n)
    {
        unsigned long long guess = 1;
        while(exp(guess, n) <= num)
        {
            guess *= 2;
        }
        return recursiveNthRoot(guess/2, guess, num, n);
    }

    long long gcd(long long num1, long long num2)
    {
        if(num1 < 0)
        {
            num1 = -num1;
        }
        if(num2 < 0)
        {
            num2 = -num2;
        }
        if(num1 == 0)
        {
            return num2;
        }
        if(num2 == 0)
        {
            return num1;
        }
        if(num1 > num2)
        {
            return gcd(num1 % num2, num2);
        }
        return gcd(num1, num2 % num1);
    }

    unsigned long long gcd(unsigned long long num1, unsigned long long num2)
    {
        if(num1 == 0)
        {
            return num2;
        }
        if(num2 == 0)
        {
            return num1;
        }
        if(num1 > num2)
        {
            return gcd(num1 % num2, num2);
        }
        return gcd(num1, num2 % num1);
    }

    math::Signed gcd(math::Signed num1, math::Signed num2)
    {
        if(num1 < 0)
        {
            num1 = -num1;
        }
        if(num2 < 0)
        {
            num2 = -num2;
        }
        if(num1 == 0)
        {
            return num2;
        }
        if(num2 == 0)
        {
            return num1;
        }
        if(num1 > num2)
        {
            return gcd(num1 % num2, num2);
        }
        return gcd(num1, num2 % num1);
    }

    bool palindrome (std::string num)
    {
        int len = num.length();
        for(int i = 0; i < len/2; i++)
        {
            if(num[i] != num[len-1-i])
            {
                return false;
            }
        }
        return true;
    }

    math::Unsigned choose (int n, int k)
    {
        math::Unsigned ans = 1;
        for(int i = k+1; i <= n; i++)
        {
            ans *= i;
        }
        for(int i = 2; i <= n-k; i++)
        {
            ans /= i;
        }
        return ans;
    }

    bool isPrime(math::Unsigned num)
    {
        for(size_t i = 0; i < primes.size() && primes[i]*primes[i] <= num; i++)
        {
            if(num % primes[i] == 0)
            {
                return false;
            }
        }
        return true;
    }

    bool isPrime(long long num)
    {
        for(size_t i = 0; i < primes.size() && primes[i]*primes[i] <= num; i++)
        {
            if(num % primes[i] == 0)
            {
                return false;
            }
        }
        return true;
    }

    math::Unsigned numFactors(math::Unsigned num)
    {
        math::Unsigned ans = 1;
        int power = 0;
        for(int i = 0; primes[i]*primes[i] <= num; i++)
        {
            while(num % primes[i] == 0)
            {
                num /= primes[i];
                power++;
            }
            ans *= power+1;
            power = 0;
        }
        if(num != 1)
        {
            ans *= 2;
        }
        return ans;
    }


    void addRow(math::Signed ***matrix, int n, 
    int row1, int row2, math::Signed num, math::Signed denom)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[row1][j][0] = denom*matrix[row1][j][0]*matrix[row2][j][1]
                                + num*matrix[row2][j][0]*matrix[row1][j][1];
            matrix[row1][j][1] *= matrix[row2][j][1]*denom;

            math::Signed g = gcd(matrix[row1][j][0], matrix[row1][j][1]);
            matrix[row1][j][0] /= g;
            matrix[row1][j][1] /= g;
        }
    }

    //Scales row by num/denom
    void scaleRow(math::Signed ***matrix, int n, int row,
    math::Signed num, math::Signed denom)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[row][j][0] *= num;
            matrix[row][j][1] *= denom;

            math::Signed g = gcd(matrix[row][j][0], matrix[row][j][1]);
            matrix[row][j][0] /= g;
            matrix[row][j][1] /= g;
        }
    }

    void swapRows(math::Signed ***matrix, int row1, int row2)
    {
        math::Signed **temp = matrix[row1];
        matrix[row1] = matrix[row2];
        matrix[row2] = temp;
    }

    math::Signed ***matrixInverse (math::Signed ***matrix, int n)
    {
        math::Signed ***augmented = new math::Signed**[n];
        for(int i = 0; i < n; i++)
        {
            augmented[i] = new math::Signed*[2*n];
            for(int j = 0; j < n; j++)
            {
                augmented[i][j] = new math::Signed[2];
                augmented[i][j+n] = new math::Signed[2];
                augmented[i][j][0] = matrix[i][j][0];
                augmented[i][j][1] = matrix[i][j][1];
                if(i == j)
                {
                    augmented[i][j+n][0] = 1;
                }
                else
                {
                    augmented[i][j+n][0] = 0;
                }
                augmented[i][j+n][1] = 1;
            }
        }

        //Begin solving
        for(int i = 0; i < n; i++)
        {
            if(augmented[i][i][0] == 0)
            {
                for(int r = i+1; r < n; r++)
                {
                    if(augmented[r][i][0] != 0)
                    {
                        swapRows(augmented, i, r);
                        break;
                    }
                }
            }
            for(int r = 0; r < n; r++)
            {
                if(i == r)
                {
                    scaleRow(augmented, 2*n, r, augmented[i][i][1],
                    augmented[i][i][0]);
                }
                else
                {
                    addRow(augmented, 2*n, r, i, 
                    static_cast<math::Signed>(-1)*augmented[r][i][0]*augmented[i][i][1],
                    augmented[r][i][1]*augmented[i][i][0]);
                }
            }
        }

        math::Signed ***ans = new math::Signed**[n];
        for(int i = 0; i < n; i++)
        {
            ans[i] = new math::Signed*[n];
            for(int j = 0; j < n; j++)
            {
                ans[i][j] = new math::Signed[2];
                ans[i][j][0] = augmented[i][j+n][0];
                ans[i][j][1] = augmented[i][j+n][1];
                delete[] augmented[i][j];
            }
            delete[] augmented[i];
        }
        delete[] augmented;
        return ans;
    }

    bool recursive_square(math::Unsigned num, math::Unsigned low, 
    math::Unsigned high)
    {
        if(low == high)
        {
            return low*low == num;
        }
        math::Unsigned mid = (low+high)/2;
        math::Unsigned guess = mid*mid;
        if(guess < num)
        {
            return recursive_square(num, mid+1, high);
        }
        if(guess > num)
        {
            return recursive_square(num, low, mid);
        }
        return true;
    }

    bool isSquare(math::Unsigned num)
    {
        math::Unsigned guess = 1;
        while(guess*guess <= num)
        {
            guess *= 2;
        }
        return recursive_square(num, guess/2, guess);
    }

    bool recursive_square(unsigned long long num, unsigned long long low, 
    unsigned long long high)
    {
        if(low == high)
        {
            return low*low == num;
        }
        unsigned long long mid = (low+high)/2;
        unsigned long long guess = mid*mid;
        if(guess < num)
        {
            return recursive_square(num, mid+1, high);
        }
        if(guess > num)
        {
            return recursive_square(num, low, mid);
        }
        return true;
    }

    bool isSquare(unsigned long long num)
    {
        unsigned long long guess = 1;
        while(guess*guess <= num)
        {
            guess *= 2;
        }
        return recursive_square(num, guess/2, guess);
    }

    bool recursive_cube(math::Unsigned num, math::Unsigned low, 
    math::Unsigned high)
    {
        if(low == high)
        {
            return low*low == num;
        }
        math::Unsigned mid = (low+high)/2;
        math::Unsigned guess = mid*mid*mid;
        if(guess < num)
        {
            return recursive_cube(num, mid+1, high);
        }
        if(guess > num)
        {
            return recursive_cube(num, low, mid);
        }
        return true;
    }

    bool isCube(math::Unsigned num)
    {
        math::Unsigned guess = 1;
        while(guess*guess*guess <= num)
        {
            guess *= 2;
        }
        return recursive_cube(num, guess/2, guess);
    }

    std::vector<long long> extendedEuclidean(long long num1, long long num2)
    {
        bool positive1 = true;
        if(num1 < 0)
        {
            positive1 = false;
            num1 = -num1;
        }
        bool positive2 = true;
        if(num2 < 0)
        {
            positive2 = false;
            num2 = -num2;
        }
        if(num1 == 0)
        {
            std::vector<long long> ans{};
            ans.push_back(0);
            ans.push_back(1);
            if(!positive2)
            {
                ans[1] *= -1;
            }
            ans.push_back(num2);
            return ans;
        }
        if(num2 == 0)
        {
            std::vector<long long> ans{};
            ans.push_back(1);
            if(!positive1)
            {
                ans[0] *= -1;
            }
            ans.push_back(0);
            ans.push_back(num1);
            return ans;
        }

        if(num1 > num2)
        {
            std::vector<long long> prev = extendedEuclidean(num1%num2, num2);
            prev[1] -= prev[0]*(num1/num2);
            if(!positive1)
            {
                prev[0] *= -1;
            }
            if(!positive2)
            {
                prev[1] *= -1;
            }
            return prev;
        }
        std::vector<long long> prev= extendedEuclidean(num2%num1, num1);
        prev[1] -= prev[0]*(num2/num1);
        long long temp = prev[0];
        prev[0] = prev[1];
        prev[1] = temp;
        if(!positive1)
        {
            prev[0] *= -1;
        }
        if(!positive2)
        {
            prev[1] *= -1;
        }
        return prev;
    }

    long long modularInverse(long long a, long long mod)
    {
        if(gcd(a, mod) != 1)
        {
            return 0;
        }
        std::vector<long long> temp = extendedEuclidean(a, mod);
        temp[0] %= mod;
        if(temp[0] < 0)
        {
            return temp[0] + mod;
        }
        return temp[0];
    }

    std::vector<math::Signed> extendedEuclidean(math::Signed num1, math::Signed num2)
    {
        bool positive1 = true;
        if(num1 < 0)
        {
            positive1 = false;
            num1 = -num1;
        }
        bool positive2 = true;
        if(num2 < 0)
        {
            positive2 = false;
            num2 = -num2;
        }
        if(num1 == 0)
        {
            std::vector<math::Signed> ans{};
            ans.push_back(0);
            ans.push_back(1);
            if(!positive2)
            {
                ans[1] = -ans[1];
            }
            ans.push_back(num2);
            return ans;
        }
        if(num2 == 0)
        {
            std::vector<math::Signed> ans{};
            ans.push_back(1);
            if(!positive1)
            {
                ans[0] = -ans[0];
            }
            ans.push_back(0);
            ans.push_back(num1);
            return ans;
        }

        if(num1 > num2)
        {
            std::vector<math::Signed> prev = extendedEuclidean(num1%num2, num2);
            prev[1] -= prev[0]*(num1/num2);
            if(!positive1)
            {
                prev[0] = -prev[0];
            }
            if(!positive2)
            {
                prev[1] = -prev[1];
            }
            return prev;
        }
        std::vector<math::Signed> prev= extendedEuclidean(num2%num1, num1);
        prev[1] -= prev[0]*(num2/num1);
        math::Signed temp = prev[0];
        prev[0] = prev[1];
        prev[1] = temp;
        if(!positive1)
        {
            prev[0] = -prev[0];
        }
        if(!positive2)
        {
            prev[1] = -prev[1];
        }
        return prev;
    }

    math::Signed modularInverse(math::Signed a, math::Signed mod)
    {
        if(gcd(a, mod) != 1)
        {
            return 0;
        }
        std::vector<math::Signed> temp = extendedEuclidean(a, mod);
        temp[0] %= mod;
        if(temp[0] < 0)
        {
            return temp[0] + mod;
        }
        return temp[0];
    }

    int numDigits(math::Signed num)
    {
        int ans = 0;
        while(num > 0)
        {
            ans++;
            num /= 10;
        }
        return ans;
    }
}

#endif