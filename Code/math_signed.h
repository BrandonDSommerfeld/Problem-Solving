#ifndef MATH_SIGNED_H
#define MATH_SIGNED_H

#include <iostream>
#include "math_unsigned.h"
using std::size_t;

namespace math
{
    class Signed;

    bool operator== (const Signed& lhs, const Signed& rhs);
    bool operator != (const Signed& lhs, const Signed& rhs);
    bool operator< (const Signed& lhs, const Signed& rhs);
    bool operator> (const Signed& lhs, const Signed& rhs);
    bool operator<= (const Signed& lhs, const Signed& rhs);
    bool operator>= (const Signed& lhs, const Signed& rhs);

    Signed operator% (const Signed& lhs, const Signed& rhs);
    Signed operator/ (const Signed& lhs, const Signed& rhs);
    Signed operator* (const Signed& lhs, const Signed& rhs);
    Signed operator+ (const Signed& lhs, const Signed& rhs);
    Signed operator- (const Signed& lhs, const Signed& rhs);

    std::ostream& operator<< (std::ostream& os, const Signed& u);
    std::istream& operator>> (std::istream& is, Signed& u);

    class Signed
    {
    private:
        math::Unsigned num;
        bool positive;
    public:
        Signed(int n = 0);
        Signed(unsigned int n);
        Signed (long long n);
        Signed (unsigned long long n);
        Signed (const Signed& copy);
        Signed (const math::Unsigned& copy);
        Signed& operator= (const Signed& rhs);
        Signed& operator= (const Signed&& rhs);
        friend bool operator== (const Signed& lhs, const Signed& rhs);
        friend bool operator != (const Signed& lhs, const Signed& rhs);
        friend bool operator< (const Signed& lhs, const Signed& rhs);
        friend bool operator> (const Signed& lhs, const Signed& rhs);
        friend bool operator<= (const Signed& lhs, const Signed& rhs);
        friend bool operator>= (const Signed& lhs, const Signed& rhs);
        Signed operator-() const;
        Signed& operator %= (const Signed& rhs);
        Signed& operator /= (const Signed& rhs);
        Signed& operator *= (const Signed& rhs);
        Signed& operator += (const Signed& rhs);
        Signed& operator -= (const Signed& rhs);
        friend Signed operator% (const Signed& lhs, const Signed& rhs);
        friend Signed operator/ (const Signed& lhs, const Signed& rhs);
        friend Signed operator* (const Signed& lhs, const Signed& rhs);
        friend Signed operator+ (const Signed& lhs, const Signed& rhs);
        friend Signed operator- (const Signed& lhs, const Signed& rhs);
        Signed& operator++();
        Signed operator++(int);
        Signed& operator--();
        Signed operator--(int);
        std::string to_string() const;
        int to_int ();
        friend std::ostream& operator<< (std::ostream& os, const Signed& u);
        friend std::istream& operator>> (std::istream& is, Signed& u);
        math::Unsigned to_unsigned();
    };
    
} // namespace math

#endif