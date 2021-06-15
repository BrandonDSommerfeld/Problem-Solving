#ifndef MATH_RATIONAL_H
#define MATH_RATIONAL_H

#include "math_signed.h"
#include "math_fast_rational.h"

namespace math
{
  class Rational;

  bool operator== (const math::Rational& lhs, const math::Rational& rhs);
  bool operator!= (const math::Rational& lhs, const math::Rational& rhs);
  bool operator< (const math::Rational& lhs, const math::Rational& rhs);
  bool operator> (const math::Rational& lhs,const math::Rational& rhs);
  bool operator<= (const math::Rational& lhs, const math::Rational& rhs);   
  bool operator>= (const math::Rational& lhs, const math::Rational& rhs);

  Rational operator* (const Rational& lhs, const Rational& rhs);
  Rational operator/ (const Rational& lhs, const Rational& rhs);
  Rational operator+ (const Rational& lhs, const Rational& rhs);
  Rational operator- (const Rational& lhs, const Rational& rhs);
  std::ostream& operator<< (std::ostream& os, const Rational& num);

  class Rational
  {
    private:
        math::Signed numerator;
        math::Signed denominator;
    public:
      Rational(long long num = 0, long long denom = 1);

      Rational (const math::Signed& num, const math::Signed& denom);

      Rational (const math::Rational& copy);

      Rational (const math::FastRational& copy);

      Rational& operator= (const math::Rational& rhs);

      Rational& operator= (const math::Rational&& rhs);

      friend bool operator== (const math::Rational& lhs, const math::Rational& rhs);

      friend bool operator!= (const math::Rational& lhs, const math::Rational& rhs);

      friend bool operator< (const math::Rational& lhs, const math::Rational& rhs);

      friend bool operator> (const math::Rational& lhs,const math::Rational& rhs);

      friend bool operator<= (const math::Rational& lhs, const math::Rational& rhs);
      
      friend bool operator>= (const math::Rational& lhs, const math::Rational& rhs);

      Rational operator- () const ;

      Rational& operator /= (const Rational& rhs);

      Rational& operator *= (const Rational& rhs);

      Rational& operator += (const Rational& rhs);
      
      Rational& operator -= (const Rational& rhs);

      friend Rational operator* (const Rational& lhs, const Rational& rhs);
      friend Rational operator/ (const Rational& lhs, const Rational& rhs);
      friend Rational operator+ (const Rational& lhs, const Rational& rhs);
      friend Rational operator- (const Rational& lhs, const Rational& rhs);
      
      std::string to_string () const;

      friend std::ostream& operator<< (std::ostream& os, const Rational& num);

      math::Signed get_numerator ();

      math::Signed get_denominator ();
  };
}
#endif