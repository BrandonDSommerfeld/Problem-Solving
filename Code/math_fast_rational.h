#ifndef MATH_FAST_RATIONAL_H
#define MATH_FAST_RATIONAL_H

#include<iostream>

namespace math
{
  class FastRational;

  bool operator== (const math::FastRational& lhs, const math::FastRational& rhs);
  bool operator!= (const math::FastRational& lhs, const math::FastRational& rhs);
  bool operator< (const math::FastRational& lhs, const math::FastRational& rhs);
  bool operator> (const math::FastRational& lhs,const math::FastRational& rhs);
  bool operator<= (const math::FastRational& lhs, const math::FastRational& rhs);
  bool operator>= (const math::FastRational& lhs, const math::FastRational& rhs);

  FastRational operator* (const FastRational& lhs, const FastRational& rhs);
  FastRational operator/ (const FastRational& lhs, const FastRational& rhs);
  FastRational operator+ (const FastRational& lhs, const FastRational& rhs);
  FastRational operator- (const FastRational& lhs, const FastRational& rhs);
  std::ostream& operator<< (std::ostream& os, const FastRational& num);
  
  class FastRational
  {
    private:
      long long numerator;
      long long denominator;
    public:
      FastRational(long long num = 0, long long denom = 1);
      FastRational(const math::FastRational& copy);
      FastRational& operator= (const math::FastRational& rhs);
      FastRational& operator= (const math::FastRational&& rhs);
      friend bool operator== (const math::FastRational& lhs, const math::FastRational& rhs);
      friend bool operator!= (const math::FastRational& lhs, const math::FastRational& rhs);
      friend bool operator< (const math::FastRational& lhs, const math::FastRational& rhs);
      friend bool operator> (const math::FastRational& lhs,const math::FastRational& rhs);
      friend bool operator<= (const math::FastRational& lhs, const math::FastRational& rhs);
      friend bool operator>= (const math::FastRational& lhs, const math::FastRational& rhs);
      FastRational operator- () const ;
      FastRational& operator /= (const FastRational& rhs);
      FastRational& operator *= (const FastRational& rhs);
      FastRational& operator += (const FastRational& rhs);
      FastRational& operator -= (const FastRational& rhs);
      friend FastRational operator* (const FastRational& lhs, const FastRational& rhs);
      friend FastRational operator/ (const FastRational& lhs, const FastRational& rhs);
      friend FastRational operator+ (const FastRational& lhs, const FastRational& rhs);
      friend FastRational operator- (const FastRational& lhs, const FastRational& rhs);
      friend std::ostream& operator<< (std::ostream& os, const FastRational& num);
      long long get_numerator () const;
      long long get_denominator () const;
  };
}
#endif