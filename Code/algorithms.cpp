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
#include "math_unsigned.h"
#include "math_signed.h"
#include "math_rational.h"
#include "algorithms.h"

namespace algorithms
{
    std::vector<unsigned long long> primes;
    void generatePrimes(unsigned long long limit)
    {
        primes = std::vector<unsigned long long>{};
        bool* composite = new bool[limit]{};
        for(unsigned long long i{2}; i*i < limit; i++)
        {
            if(!composite[i])
            {
                for(unsigned long long j{2}; i*j < limit; j++)
                {
                    composite[i*j] = true;
                }
            }
        }

        for(unsigned long long i = 2; i < limit; i++)
        {
            if(!composite[i])
            {
                algorithms::primes.push_back(i);
            }
        }
        delete[] composite;
    }

    unsigned long long totient (unsigned long long num)
    {
        unsigned long long ans = num;
        for(size_t i = 0; i < algorithms::primes.size () && algorithms::primes[i] * algorithms::primes[i] <= num; i++)
        {
            if(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
                ans /= algorithms::primes[i];
                ans *= algorithms::primes[i]-1;
            }
            while(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
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
        for(size_t i = 0; i < algorithms::primes.size () && algorithms::primes[i] * algorithms::primes[i] <= num; i++)
        {
            if(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
                ans /= algorithms::primes[i];
                ans *= algorithms::primes[i]-1;
            }
            while(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
            }
        }
        if(num > 1)
        {
            ans /= num;
            ans *= num-1;
        }
        return ans;
    }

    std::vector<unsigned int>* factors (unsigned int num)
    {
        std::vector<unsigned int> *ans = new std::vector<unsigned int>{};
        for(size_t i = 0; i < algorithms::primes.size() && algorithms::primes[i] * algorithms::primes[i] <= num; i++)
        {
            if(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
                ans->push_back(algorithms::primes[i]);
            }
            while(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
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
        for(size_t i = 0; i < algorithms::primes.size() && algorithms::primes[i] * algorithms::primes[i] <= num; i++)
        {
            if(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
                ans->push_back(algorithms::primes[i]);
            }
            while(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
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

    unsigned long long exp(unsigned long long base, unsigned long long exponent)
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
    
    unsigned long long exp(unsigned long long base, unsigned long long exponent, unsigned long long mod)
    {
        unsigned long long ans = 1;
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
    unsigned long long num, unsigned long long n)
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

    bool isNthPower(unsigned long long num, unsigned long long n)
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
    unsigned long long num, unsigned long long n)
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

    unsigned long long nthRoot(unsigned long long num, unsigned long long n)
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

    math::Unsigned choose (unsigned long long n, unsigned long long k)
    {
        math::Unsigned ans = 1;
        for(unsigned long long i = k+1; i <= n; i++)
        {
            ans *= i;
        }
        for(unsigned long long i = 2; i <= n-k; i++)
        {
            ans /= i;
        }
        return ans;
    }

    bool isPrime(math::Unsigned num)
    {
        for(size_t i = 0; i < algorithms::primes.size() && algorithms::primes[i]*algorithms::primes[i] <= num; i++)
        {
            if(num % algorithms::primes[i] == 0)
            {
                return false;
            }
        }
        return true;
    }

    bool isPrime(unsigned long long num)
    {
        for(size_t i = 0; i < algorithms::primes.size() && algorithms::primes[i]*algorithms::primes[i] <= num; i++)
        {
            if(num % algorithms::primes[i] == 0)
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
        for(size_t i = 0; algorithms::primes[i]*algorithms::primes[i] <= num; i++)
        {
            while(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
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
    
    unsigned long long numFactors(unsigned long long num)
    {
        unsigned long long ans = 1;
        int power = 0;
        for(int i = 0; algorithms::primes[i]*algorithms::primes[i] <= num; i++)
        {
            while(num % algorithms::primes[i] == 0)
            {
                num /= algorithms::primes[i];
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

    void addRow(math::Rational **matrix, int n, 
    int row1, int row2, const math::Rational& num)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[row1][j] += num*matrix[row2][j];
        }
    }

    //Scales row by num/denom
    void scaleRow(math::Rational **matrix, int n, int row,
    const math::Rational& num)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[row][j] *= num;
        }
    }

    void swapRows(math::Rational **matrix, int row1, int row2)
    {
        math::Rational *temp = matrix[row1];
        matrix[row1] = matrix[row2];
        matrix[row2] = temp;
    }

    math::Rational **matrixInverse (math::Rational **matrix, int n)
    {
        math::Rational **augmented = new math::Rational*[n];
        for(int i = 0; i < n; i++)
        {
            augmented[i] = new math::Rational[2*n];
            for(int j = 0; j < n; j++)
            {
                augmented[i][j] = matrix[i][j];
                if(i == j)
                {
                    augmented[i][j+n] = 1;
                }
                else
                {
                    augmented[i][j+n] = 0;
                }
            }
        }

        //Begin solving
        for(int i = 0; i < n; i++)
        {
            if(augmented[i][i] == 0)
            {
                for(int r = i+1; r < n; r++)
                {
                    if(augmented[r][i] != 0)
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
                    scaleRow(augmented, 2*n, r, 1/augmented[i][i]);
                }
                else
                {
                    addRow(augmented, 2*n, r, i, 
                    -augmented[r][i]/augmented[i][i]);
                }
            }
        }

        math::Rational **ans = new math::Rational*[n];
        for(int i = 0; i < n; i++)
        {
            ans[i] = new math::Rational[n];
            for(int j = 0; j < n; j++)
            {
                ans[i][j] = augmented[i][j+n];
            }
            delete[] augmented[i];
        }
        delete[] augmented;
        return ans;
    }

    math::Rational** multiply (math::Rational** matrix1, math::Rational** matrix2,
    int dim1, int dim2, int dim3)
    {
        math::Rational** ans = new math::Rational*[dim1];
        for(int i = 0; i < dim1; i++)
        {
            ans[i] = new math::Rational[dim3]{};
        }
        for(int i = 0; i < dim1; i++)
        {
            for(int j = 0; j < dim3; j++)
            {
                for(int k = 0; k < dim2; k++)
                {
                    ans[i][j] += matrix1[i][k]*matrix2[k][j];
                }
            }
        }
        return ans;
    }

    void addRow(math::FastRational **matrix, int n, 
    int row1, int row2, const math::FastRational& num)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[row1][j] += num*matrix[row2][j];
        }
    }

    //Scales row by num/denom
    void scaleRow(math::FastRational **matrix, int n, int row,
    const math::FastRational& num)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[row][j] *= num;
        }
    }

    void swapRows(math::FastRational **matrix, int row1, int row2)
    {
        math::FastRational *temp = matrix[row1];
        matrix[row1] = matrix[row2];
        matrix[row2] = temp;
    }

    math::FastRational **matrixInverse (math::FastRational **matrix, int n)
    {
        math::FastRational **augmented = new math::FastRational*[n];
        for(int i = 0; i < n; i++)
        {
            augmented[i] = new math::FastRational[2*n];
            for(int j = 0; j < n; j++)
            {
                augmented[i][j] = matrix[i][j];
                if(i == j)
                {
                    augmented[i][j+n] = 1;
                }
                else
                {
                    augmented[i][j+n] = 0;
                }
            }
        }

        //Begin solving
        for(int i = 0; i < n; i++)
        {
            for(int a = 0; a < n; a++)
            {
                for(int b = 0; b < 2*n; b++)
                {
                    std::cout << augmented[a][b] << ' ';
                }
                std::cout << '\n';
            }
            std::cout << '\n';
            if(augmented[i][i] == 0)
            {
                for(int r = i+1; r < n; r++)
                {
                    if(augmented[r][i] != 0)
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
                    scaleRow(augmented, 2*n, r, 1/augmented[i][i]);
                }
                else
                {
                    addRow(augmented, 2*n, r, i, 
                    -augmented[r][i]/augmented[i][i]);
                }
            }
        }

        math::FastRational **ans = new math::FastRational*[n];
        for(int i = 0; i < n; i++)
        {
            ans[i] = new math::FastRational[n];
            for(int j = 0; j < n; j++)
            {
                ans[i][j] = augmented[i][j];
            }
            delete[] augmented[i];
        }
        delete[] augmented;
        return ans;
    }

    math::FastRational** multiply (math::FastRational** matrix1, math::FastRational** matrix2,
    int dim1, int dim2, int dim3)
    {
        math::FastRational** ans = new math::FastRational*[dim1];
        for(int i = 0; i < dim1; i++)
        {
            ans[i] = new math::FastRational[dim3]{};
        }
        for(int i = 0; i < dim1; i++)
        {
            for(int j = 0; j < dim3; j++)
            {
                for(int k = 0; k < dim2; k++)
                {
                    ans[i][j] += matrix1[i][k]*matrix2[k][j];
                }
            }
        }
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

    unsigned long long digitalRoot (unsigned long long num)
    {
        while(num >= 10)
        {
            unsigned long long next = 0;
            while(num > 0)
            {
                next += num % 10;
                num /= 10;
            }
            num = next;
        }
        return num;
    }

    math::Unsigned digitalRoot (math::Unsigned num)
    {
        while(num >= 10)
        {
            math::Unsigned next = 0;
            while(num > 0)
            {
                next += num % 10;
                num /= 10;
            }
            num = next;
        }
        return num;
    }

    std::string hexadecimal(math::Unsigned num)
    {
        std::string ans{};
        while(num > 0)
        {
            unsigned int remainder = (num % 16).to_uint();
            if(remainder < 10)
            {
                ans = static_cast<char>(remainder+48) + ans;
            }
            else
            {
                ans = static_cast<char>(remainder+55) + ans;
            }
            num /= 16;
        }
        return ans;
    }
}

#endif