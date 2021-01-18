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
    static std::vector<int> primes;

    void generatePrimes(int limit)
    {
        composite = new bool[limit];
        for(int i{2}; i*i < limit; i++)
        {
            if(!composite[i])
            {
                for(int j{2}; i*j < limit; j++)
                {
                    composite[i*j] = true;
                }
            }
        }

        for(int i = 2; i < limit; i++)
        {
            if(!composite[i])
            {
                primes.push_back(i);
            }
        }
    }

    int totient (int num)
    {
        int ans = num;
        for(int i = 0; i < primes.size () && primes[i] * primes[i] <= num; i++)
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
        for(int i = 0; i < primes.size () && primes[i] * primes[i] <= num; i++)
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
        for(int i = 0; i < primes.size() && primes[i] * primes[i] <= num; i++)
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
        for(int i = 0; i < primes.size() && primes[i] * primes[i] <= num; i++)
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

    int exp(long long base, int exponent, int mod)
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

    math::Unsigned exp(math::Unsigned base, math::Unsigned exponent, math::Unsigned mod)
    {
        math::Unsigned ans = 1;
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

    int gcd(int num1, int num2)
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

    math::Signed gcd(math::Signed num1, math::Signed num2)
    {
        if(num1 < 0)
        {
            num1 *= -1;
        }
        if(num2 < 0)
        {
            num2 *= -1;
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
        for(int i = 0; i < primes.size() && primes[i]*primes[i] <= num; i++)
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
        if(mid*mid < num)
        {
            return recursive_square(num, mid+1, high);
        }
        if(mid*mid > num)
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

    std::vector<int> extendedEuclidean(int num1, int num2)
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
            std::vector<int> ans{};
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
            std::vector<int> ans{};
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
            std::vector<int> prev = extendedEuclidean(num1%num2, num2);
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
        std::vector<int> prev= extendedEuclidean(num2%num1, num1);
        prev[1] -= prev[0]*(num2/num1);
        int temp = prev[0];
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

    int modularInverse(int a, int mod)
    {
        if(gcd(a, mod) != 1)
        {
            return 0;
        }
        std::vector<int> temp = extendedEuclidean(a, mod);
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
                ans[1] *= -1;
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
                ans[0] *= -1;
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
                prev[0] *= -1;
            }
            if(!positive2)
            {
                prev[1] *= -1;
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
            prev[0] *= -1;
        }
        if(!positive2)
        {
            prev[1] *= -1;
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
};

#endif