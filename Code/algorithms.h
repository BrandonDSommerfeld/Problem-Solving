#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <string>
#include <cmath>
#include <vector>
#include "math_unsigned.h"
#include "math_signed.h"
#include "math_rational.h"

namespace algorithms
{
    extern std::vector<unsigned long long> primes;
    void generatePrimes(unsigned long long limit);
    unsigned long long totient (unsigned long long num);
    math::Unsigned totient (math::Unsigned num);
    std::vector<unsigned long long>* factors (unsigned long long num);
    std::vector<math::Unsigned>* factors (math::Unsigned num);
    long long exp(long long base, int exponent, int mod);
    long long exp(long long base, int exponent);
    unsigned long long exp(unsigned long long base, unsigned long long exponent);
    unsigned long long exp(unsigned long long base, unsigned long long exponent, unsigned long long mod);
    math::Unsigned exp(math::Unsigned base, math::Unsigned exponent, math::Unsigned mod);
    math::Signed exp(math::Signed base, math::Signed exponent);
    math::Unsigned exp(math::Unsigned base, math::Unsigned exponent);
    math::Unsigned sqrt(math::Unsigned num);
    bool isNthPower(unsigned long long num, unsigned long long n);
    bool isNthPower(math::Unsigned num, int n);
    math::Unsigned nthRoot(math::Unsigned num, int n);
    unsigned long long nthRoot(unsigned long long num, unsigned long long n);
    long long gcd(long long num1, long long num2);
    unsigned long long gcd(unsigned long long num1, unsigned long long num2);
    math::Signed gcd(math::Signed num1, math::Signed num2);
    bool palindrome (std::string num);
    math::Unsigned choose (unsigned long long n, unsigned long long k);
    bool isPrime(math::Unsigned num);
    bool isPrime(unsigned long long num);
    math::Unsigned numFactors(math::Unsigned num);
    unsigned long long numFactors(unsigned long long num);
    void addRow(math::Rational **matrix, int n, 
    int row1, int row2, const math::Rational& num);
    void scaleRow(math::Rational **matrix, int n, int row,
    const math::Rational& num);
    void swapRows(math::Rational **matrix, int row1, int row2);
    math::Rational **matrixInverse (math::Rational **matrix, int n);
    math::Rational** multiply (math::Rational** matrix1, math::Rational** matrix2,
    int dim1, int dim2, int dim3);
    void scaleRow(math::FastRational **matrix, int n, int row,
    const math::FastRational& num);
    void swapRows(math::FastRational **matrix, int row1, int row2);
    math::FastRational **matrixInverse (math::FastRational **matrix, int n);
    math::FastRational** multiply (math::FastRational** matrix1, math::FastRational** matrix2,
    int dim1, int dim2, int dim3);
    bool isSquare(math::Unsigned num);
    bool fastIsSquare(unsigned long long num);
    bool fastSqrt(unsigned long long num);
    bool isSquare(unsigned long long num);
    bool isCube(math::Unsigned num);
    std::vector<long long> extendedEuclidean(long long num1, long long num2);
    long long modularInverse(long long a, long long mod);
    std::vector<math::Signed> extendedEuclidean(math::Signed num1, math::Signed num2);
    math::Signed modularInverse(math::Signed a, math::Signed mod);
    int numDigits(math::Signed num);
    unsigned long long digitalRoot (unsigned long long num);
    math::Unsigned digitalRoot (math::Unsigned num);
    std::string hexadecimal(math::Unsigned num);
    std::string hexToBinary(const std::string& s);
    std::string binary(math::Unsigned num);
}

#endif