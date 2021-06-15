#include "algorithms.h"
#include "math_fast_rational.h"


math::FastRational::FastRational(long long num, long long denom)
: numerator{num}, denominator{denom}
{
  if(denom < 0)
  {
    numerator *= -1;
    denominator *= -1;
  }
  else if (denom == 0)
  {
    std::cout << "Constructor\n";
    std::cout << num << ' ' << denom << '\n';
    throw std::bad_alloc();
  }
  long long d = algorithms::gcd(numerator, denominator);
  numerator /= d;
  denominator /= d;
}

math::FastRational::FastRational(const math::FastRational& copy) : 
numerator{copy.numerator}, denominator{copy.denominator}
{

}

math::FastRational& math::FastRational::operator= (const math::FastRational& rhs)
{
  numerator = rhs.numerator;
  denominator = rhs.denominator;
  return *this;
}

math::FastRational& math::FastRational::operator= (const math::FastRational&& rhs)
{
  numerator = rhs.numerator;
  denominator = rhs.denominator;
  return *this;
}

bool math::operator== (const math::FastRational& lhs, const math::FastRational& rhs)
{
  return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool math::operator!= (const math::FastRational& lhs, const math::FastRational& rhs)
{
  return lhs.numerator != rhs.numerator || lhs.denominator != rhs.denominator;
}
bool math::operator< (const math::FastRational& lhs, const math::FastRational& rhs)
{
  return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) < 0;
}

bool math::operator> (const math::FastRational& lhs,const math::FastRational& rhs)
{
  return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) > 0;
}

bool math::operator<= (const math::FastRational& lhs, const math::FastRational& rhs)
{
  return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) <= 0;
}

bool math::operator>= (const math::FastRational& lhs, const math::FastRational& rhs)
{
  return (lhs.numerator*rhs.denominator - rhs.numerator*lhs.denominator) >= 0;
}

math::FastRational math::FastRational::operator- () const 
{
  math::FastRational ans (*this);
  ans.numerator = -numerator;
  return ans;
}

math::FastRational& math::FastRational::operator /= (const math::FastRational& rhs)
{
  if(rhs.numerator == 0)
  {
    std::cout << "Assignment\n";
    std::cout << rhs.numerator << ' ' << rhs.denominator << '\n';
    throw std::bad_alloc();
  }
  numerator = numerator*rhs.denominator;
  denominator = denominator*rhs.numerator;

  long long gcd = algorithms::gcd(numerator, denominator);
  numerator /= gcd;
  denominator /= gcd;

  if(denominator < 0)
  {
    numerator = -numerator;
    denominator = -denominator;
  }
  return *this;
}

math::FastRational& math::FastRational::operator *= (const math::FastRational& rhs)
{
  numerator = numerator*rhs.numerator;
  denominator = denominator*rhs.denominator;

  long long gcd = algorithms::gcd(numerator, denominator);
  numerator /= gcd;
  denominator /= gcd;

  if(denominator < 0)
  {
    numerator = -numerator;
    denominator = -denominator;
  }
  return *this;
}

math::FastRational& math::FastRational::operator += (const math::FastRational& rhs)
{
  numerator = numerator*rhs.denominator + denominator*rhs.numerator;
  denominator = denominator*rhs.denominator;

  long long gcd = algorithms::gcd(numerator, denominator);
  numerator /= gcd;
  denominator /= gcd;

  if(denominator < 0)
  {
    numerator = -numerator;
    denominator = -denominator;
  }
  return *this;
}

math::FastRational& math::FastRational::operator -= (const math::FastRational& rhs)
{
  numerator = numerator*rhs.denominator - denominator*rhs.numerator;
  denominator = denominator*rhs.denominator;

  long long gcd = algorithms::gcd(numerator, denominator);
  numerator /= gcd;
  denominator /= gcd;

  if(denominator < 0)
  {
    numerator = -numerator;
    denominator = -denominator;
  }
  return *this;
}

math::FastRational math::operator* (const math::FastRational& lhs, const math::FastRational& rhs)
{
  math::FastRational ans{lhs.numerator*rhs.numerator, lhs.denominator*rhs.denominator};

  long long gcd = algorithms::gcd(ans.numerator, ans.denominator);
  ans.numerator /= gcd;
  ans.denominator /= gcd;
  return ans;
}
math::FastRational math::operator/ (const math::FastRational& lhs, const math::FastRational& rhs)
{
  if(rhs.numerator == 0)
  {
    std::cout << "Division\n";
    std::cout << rhs.numerator << ' ' << rhs.denominator << '\n';
    throw std::bad_alloc();
  }
  FastRational ans{lhs.numerator*rhs.denominator, lhs.denominator*rhs.numerator};

  long long gcd = algorithms::gcd(ans.numerator, ans.denominator);
  ans.numerator /= gcd;
  ans.denominator /= gcd;
  return ans;
}
math::FastRational math::operator+ (const math::FastRational& lhs, const math::FastRational& rhs)
{
  FastRational ans{lhs.numerator*rhs.denominator+rhs.numerator*lhs.denominator
  , lhs.denominator*rhs.denominator};

  long long gcd = algorithms::gcd(ans.numerator, ans.denominator);
  ans.numerator /= gcd;
  ans.denominator /= gcd;
  return ans;
}
math::FastRational math::operator- (const math::FastRational& lhs, const math::FastRational& rhs)
{
  FastRational ans{lhs.numerator*rhs.denominator-rhs.numerator*lhs.denominator
  , lhs.denominator*rhs.denominator};
  long long gcd = algorithms::gcd(ans.numerator, ans.denominator);
  ans.numerator /= gcd;
  ans.denominator /= gcd;
  return ans;
}

std::ostream& math::operator<< (std::ostream& os, const math::FastRational& num)
{
  os << num.numerator << '/' << num.denominator;
  return os;
}

long long math::FastRational::get_numerator () const
{
  return numerator;
}

long long math::FastRational::get_denominator () const
{
  return denominator;
}
