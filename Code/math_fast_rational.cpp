#ifndef MATH_FAST_RATIONAL_H
#define MATH_FAST_RATIONAL_H

#include "algorithms.cpp"

namespace math
{
  class FastRational
  {
    private:
      long long numerator;
      long long denominator;
    public:
      FastRational(long long num = 0, long long denom = 1)
      : numerator{num}, denominator{denom}
      {

      }

      FastRational(const math::FastRational& copy) : 
      numerator{copy.numerator}, denominator{copy.denominator}
      {

      }

      FastRational& operator= (const math::FastRational& rhs)
      {
        numerator = rhs.numerator;
        denominator = rhs.denominator;
        return *this;
      }

      FastRational& operator= (const math::FastRational&& rhs)
      {
        numerator = rhs.numerator;
        denominator = rhs.denominator;
        return *this;
      }

      friend bool operator== (const math::FastRational& lhs, const math::FastRational& rhs)
      {
        return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
      }

      friend bool operator!= (const math::FastRational& lhs, const math::FastRational& rhs)
      {
        return lhs.numerator != rhs.numerator || lhs.denominator != rhs.denominator;
      }

      friend bool operator< (const math::FastRational& lhs, const math::FastRational& rhs)
      {
        return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) < 0;
      }

      friend bool operator> (const math::FastRational& lhs,const math::FastRational& rhs)
      {
        return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) > 0;
      }

      friend bool operator<= (const math::FastRational& lhs, const math::FastRational& rhs)
      {
        return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) <= 0;
      }
      
      friend bool operator>= (const math::FastRational& lhs, const math::FastRational& rhs)
      {
        return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) >= 0;
      }

      FastRational operator- () const 
      {
        FastRational ans (*this);
        ans.numerator = -numerator;
        return ans;
      }

      FastRational& operator /= (const FastRational& rhs)
      {
        numerator = numerator*rhs.denominator;
        denominator = denominator*rhs.numerator;

        unsigned long long gcd = algorithms::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if(denominator < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        return *this;
      }

      FastRational& operator *= (const FastRational& rhs)
      {
        numerator = numerator*rhs.numerator;
        denominator = denominator*rhs.denominator;

        unsigned long long gcd = algorithms::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if(denominator < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        return *this;
      }

      FastRational& operator += (const FastRational& rhs)
      {
        numerator = numerator*rhs.denominator + denominator*rhs.numerator;
        denominator = denominator*rhs.denominator;

        unsigned long long gcd = algorithms::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if(denominator < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        return *this;
      }
      
      FastRational& operator -= (const FastRational& rhs)
      {
        numerator = numerator*rhs.denominator - denominator*rhs.numerator;
        denominator = denominator*rhs.denominator;

        unsigned long long gcd = algorithms::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if(denominator < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        return *this;
      }

      friend FastRational operator* (const FastRational& lhs, const FastRational& rhs)
      {
        FastRational ans{lhs.numerator*rhs.numerator, lhs.denominator*rhs.denominator};

        unsigned long long gcd = algorithms::gcd(ans.numerator, ans.denominator);
        ans.numerator /= gcd;
        ans.denominator /= gcd;
        return ans;
      }
      friend FastRational operator/ (const FastRational& lhs, const FastRational& rhs)
      {
        FastRational ans{lhs.numerator*rhs.denominator, lhs.denominator*rhs.numerator};

        unsigned long long gcd = algorithms::gcd(ans.numerator, ans.denominator);
        ans.numerator /= gcd;
        ans.denominator /= gcd;
        return ans;
      }
      friend FastRational operator+ (const FastRational& lhs, const FastRational& rhs)
      {
        FastRational ans{lhs.numerator*rhs.denominator+rhs.numerator*lhs.denominator
        , lhs.denominator*rhs.denominator};

        unsigned long long gcd = algorithms::gcd(ans.numerator, ans.denominator);
        ans.numerator /= gcd;
        ans.denominator /= gcd;
        return ans;
      }
      friend FastRational operator- (const FastRational& lhs, const FastRational& rhs)
      {
        FastRational ans{lhs.numerator*rhs.denominator-rhs.numerator*lhs.denominator
        , lhs.denominator*rhs.denominator};
        unsigned long long gcd = algorithms::gcd(ans.numerator, ans.denominator);
        ans.numerator /= gcd;
        ans.denominator /= gcd;
        return ans;
      }

      friend std::ostream& operator<< (std::ostream& os, const FastRational& num)
      {
        os << num.numerator << '/' << num.denominator;
        return os;
      }

      unsigned long long get_numerator ()
      {
        return numerator;
      }

      unsigned long long get_denominator ()
      {
        return denominator;
      }
  };
}
#endif