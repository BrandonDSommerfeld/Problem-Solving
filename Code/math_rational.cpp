#ifndef MATH_RATIONAL_H
#define MATH_RATIONAL_H

#include "math_signed.cpp"
#include "algorithms.cpp"

namespace math
{
  class Rational
  {
    private:
      math::Signed numerator;
      math::Signed denominator;
    public:
      Rational(long long num = 0, long long denom = 1)
      : numerator{num}, denominator{denom}
      {
        if(denom < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        math::Signed d = algorithms::gcd(numerator, denominator);
        numerator /= d;
        denominator /= d;
      }

      Rational (const math::Signed& num, const math::Signed& denom)
      : numerator{num}, denominator{denom}
      {
        if(denom < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        math::Signed d = algorithms::gcd(numerator, denominator);
        numerator /= d;
        denominator /= d;
      }

      Rational (const math::Rational& copy)
      : numerator{copy.numerator}, denominator{copy.denominator}
      {

      }

      Rational& operator= (const math::Rational& rhs)
      {
        numerator = rhs.numerator;
        denominator = rhs.denominator;
        return *this;
      }

      Rational& operator= (const math::Rational&& rhs)
      {
        numerator = rhs.numerator;
        denominator = rhs.denominator;
        return *this;
      }

      friend bool operator== (const math::Rational& lhs, const math::Rational& rhs)
      {
        return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
      }

      friend bool operator!= (const math::Rational& lhs, const math::Rational& rhs)
      {
        return lhs.numerator != rhs.numerator || lhs.denominator != rhs.denominator;
      }

      friend bool operator< (const math::Rational& lhs, const math::Rational& rhs)
      {
        return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) < 0;
      }

      friend bool operator> (const math::Rational& lhs,const math::Rational& rhs)
      {
        return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) > 0;
      }

      friend bool operator<= (const math::Rational& lhs, const math::Rational& rhs)
      {
        return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) <= 0;
      }
      
      friend bool operator>= (const math::Rational& lhs, const math::Rational& rhs)
      {
        return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) >= 0;
      }

      Rational operator- () const 
      {
        Rational ans (*this);
        ans.numerator = -numerator;
        return ans;
      }

      Rational& operator /= (const Rational& rhs)
      {
        numerator = numerator*rhs.denominator;
        denominator = denominator*rhs.numerator;

        math::Signed gcd = algorithms::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if(denominator < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        return *this;
      }

      Rational& operator *= (const Rational& rhs)
      {
        numerator = numerator*rhs.numerator;
        denominator = denominator*rhs.denominator;

        math::Signed gcd = algorithms::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if(denominator < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        return *this;
      }

      Rational& operator += (const Rational& rhs)
      {
        numerator = numerator*rhs.denominator + denominator*rhs.numerator;
        denominator = denominator*rhs.denominator;

        math::Signed gcd = algorithms::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if(denominator < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        return *this;
      }
      
      Rational& operator -= (const Rational& rhs)
      {
        numerator = numerator*rhs.denominator - denominator*rhs.numerator;
        denominator = denominator*rhs.denominator;

        math::Signed gcd = algorithms::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if(denominator < 0)
        {
          numerator = -numerator;
          denominator = -denominator;
        }
        return *this;
      }

      friend Rational operator* (const Rational& lhs, const Rational& rhs)
      {
        Rational ans{lhs.numerator*rhs.numerator, lhs.denominator*rhs.denominator};

        math::Signed gcd = algorithms::gcd(ans.numerator, ans.denominator);
        ans.numerator /= gcd;
        ans.denominator /= gcd;
        return ans;
      }
      friend Rational operator/ (const Rational& lhs, const Rational& rhs)
      {
        Rational ans{lhs.numerator*rhs.denominator, lhs.denominator*rhs.numerator};

        math::Signed gcd = algorithms::gcd(ans.numerator, ans.denominator);
        ans.numerator /= gcd;
        ans.denominator /= gcd;
        return ans;
      }
      friend Rational operator+ (const Rational& lhs, const Rational& rhs)
      {
        Rational ans{lhs.numerator*rhs.denominator+rhs.numerator*lhs.denominator
        , lhs.denominator*rhs.denominator};

        math::Signed gcd = algorithms::gcd(ans.numerator, ans.denominator);
        ans.numerator /= gcd;
        ans.denominator /= gcd;
        return ans;
      }
      friend Rational operator- (const Rational& lhs, const Rational& rhs)
      {
        Rational ans{lhs.numerator*rhs.denominator-rhs.numerator*lhs.denominator
        , lhs.denominator*rhs.denominator};
        math::Signed gcd = algorithms::gcd(ans.numerator, ans.denominator);
        ans.numerator /= gcd;
        ans.denominator /= gcd;
        return ans;
      }
      
      std::string to_string () const 
      {
        return numerator.to_string() + '/' + denominator.to_string();
      }

      friend std::ostream& operator<< (std::ostream& os, const Rational& num)
      {
        os << num.to_string();
        return os;
      }

      math::Signed get_numerator ()
      {
        return numerator;
      }

      math::Signed get_denominator ()
      {
        return denominator;
      }
  };
}
#endif