#include "math_rational.h"
#include "math_signed.h"
#include "math_fast_rational.h"
#include "algorithms.h"

math::Rational::Rational(long long num, long long denom)
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

math::Rational::Rational (const math::Signed& num, const math::Signed& denom)
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

math::Rational::Rational (const math::Rational& copy)
: numerator{copy.numerator}, denominator{copy.denominator}
{

}

math::Rational::Rational (const math::FastRational& copy)
:numerator{copy.get_numerator()}, denominator{copy.get_denominator()}
{
  
}

math::Rational& math::Rational::operator= (const math::Rational& rhs)
{
  numerator = rhs.numerator;
  denominator = rhs.denominator;
  return *this;
}

math::Rational& math::Rational::operator= (const math::Rational&& rhs)
{
  numerator = rhs.numerator;
  denominator = rhs.denominator;
  return *this;
}

bool math::operator== (const math::Rational& lhs, const math::Rational& rhs)
{
  return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool math::operator!= (const math::Rational& lhs, const math::Rational& rhs)
{
  return lhs.numerator != rhs.numerator || lhs.denominator != rhs.denominator;
}

bool math::operator< (const math::Rational& lhs, const math::Rational& rhs)
{
  return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) < 0;
}

bool math::operator> (const math::Rational& lhs,const math::Rational& rhs)
{
  return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) > 0;
}

bool math::operator<= (const math::Rational& lhs, const math::Rational& rhs)
{
  return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) <= 0;
}

bool math::operator>= (const math::Rational& lhs, const math::Rational& rhs)
{
  return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) >= 0;
}

math::Rational math::Rational::operator- () const 
{
  math::Rational ans (*this);
  ans.numerator = -numerator;
  return ans;
}

math::Rational& math::Rational::operator /= (const Rational& rhs)
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

math::Rational& math::Rational::operator *= (const math::Rational& rhs)
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

math::Rational& math::Rational::operator += (const math::Rational& rhs)
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

math::Rational& math::Rational::operator -= (const math::Rational& rhs)
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

math::Rational math::operator* (const math::Rational& lhs, const math::Rational& rhs)
{
  math::Rational ans{lhs.numerator*rhs.numerator, lhs.denominator*rhs.denominator};

  math::Signed gcd = algorithms::gcd(ans.numerator, ans.denominator);
  ans.numerator /= gcd;
  ans.denominator /= gcd;
  return ans;
}
math::Rational math::operator/ (const math::Rational& lhs, const math::Rational& rhs)
{
  math::Rational ans{lhs.numerator*rhs.denominator, lhs.denominator*rhs.numerator};

  math::Signed gcd = algorithms::gcd(ans.numerator, ans.denominator);
  ans.numerator /= gcd;
  ans.denominator /= gcd;
  return ans;
}
math::Rational math::operator+ (const math::Rational& lhs, const math::Rational& rhs)
{
  math::Rational ans{lhs.numerator*rhs.denominator+rhs.numerator*lhs.denominator
  , lhs.denominator*rhs.denominator};

  math::Signed gcd = algorithms::gcd(ans.numerator, ans.denominator);
  ans.numerator /= gcd;
  ans.denominator /= gcd;
  return ans;
}
math::Rational math::operator- (const math::Rational& lhs, const math::Rational& rhs)
{
  math::Rational ans{lhs.numerator*rhs.denominator-rhs.numerator*lhs.denominator
  , lhs.denominator*rhs.denominator};
  math::Signed gcd = algorithms::gcd(ans.numerator, ans.denominator);
  ans.numerator /= gcd;
  ans.denominator /= gcd;
  return ans;
}

std::string math::Rational::to_string () const 
{
  return numerator.to_string() + '/' + denominator.to_string();
}

std::ostream& math::operator<< (std::ostream& os, const math::Rational& num)
{
  os << num.to_string();
  return os;
}

math::Signed math::Rational::get_numerator ()
{
  return numerator;
}

math::Signed math::Rational::get_denominator ()
{
  return denominator;
}

