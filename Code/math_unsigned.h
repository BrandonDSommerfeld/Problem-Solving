#ifndef MATH_UNSIGNED_H
#define MATH_UNSIGNED_H

#include <cstdint>
#include <iostream>
#include <vector>

using std::size_t;

namespace math
{
    class Unsigned;

    Unsigned operator+ (const Unsigned& u, const Unsigned& v);  
    Unsigned operator- (const Unsigned& u, const Unsigned& v);
    Unsigned operator* (const Unsigned& u, const Unsigned& v);
    Unsigned operator/ (const Unsigned& u, const Unsigned& v);
    Unsigned operator% (const Unsigned& u, const Unsigned& v);
    Unsigned operator<< (const Unsigned& u, size_t v);
    Unsigned operator>> (const Unsigned& u, size_t v);
    Unsigned operator& (const Unsigned& u, const Unsigned& v);
    Unsigned operator^ (const Unsigned& u, const Unsigned& v);
    Unsigned operator| (const Unsigned& u, const Unsigned& v);
    bool operator< (const Unsigned& u, const Unsigned& v);
    bool operator<= (const Unsigned& u, const Unsigned& v);
    bool operator> (const Unsigned& u, const Unsigned& v);
    bool operator>= (const Unsigned& u, const Unsigned& v);
    bool operator== (const Unsigned& u, const Unsigned& v);
    bool operator!= (const Unsigned& u, const Unsigned& v);
    std::ostream& operator<< (std::ostream& os, const Unsigned& u);
    std::istream& operator>> (std::istream& is, Unsigned& u);

    class Unsigned
    {
    public:
        typedef std::uint32_t Digit;
        typedef std::uint64_t Wigit;
        static const unsigned BITS = 32;
        Unsigned(Digit u = 0);
        Unsigned(int u);
        Unsigned(Wigit u);
        Unsigned(unsigned long long u);
        Unsigned(long long u);
        Unsigned(const std::string& s);
        Unsigned(const Unsigned& copy);
        Unsigned& operator= (const Unsigned& rhs);
        Unsigned& operator= (const Unsigned&& rhs);
        Unsigned operator++ (int);
        Unsigned& operator++ ();
        Unsigned operator-- (int);
        Unsigned& operator-- ();
        friend Unsigned operator+ (const Unsigned& u, const Unsigned& v);
        Unsigned& operator+= (const Unsigned& rhs);
        friend Unsigned operator- (const Unsigned& u, const Unsigned& v);
        Unsigned& operator-= (const Unsigned& rhs);
        friend Unsigned operator* (const Unsigned& u, const Unsigned& v);
        Unsigned& operator*= (const Unsigned& rhs);
        friend Unsigned operator/ (const Unsigned& u, const Unsigned& v);
        Unsigned& operator/= (const Unsigned& rhs);
        friend Unsigned operator% (const Unsigned& u, const Unsigned& v);
        Unsigned& operator%= (const Unsigned& rhs);
 
        void divide(Unsigned v, Unsigned& q, Unsigned& r) const;
        friend Unsigned operator<< (const Unsigned& u, size_t v);
        Unsigned& operator<<= (size_t rhs);
        friend Unsigned operator>> (const Unsigned& u, size_t v);
        Unsigned& operator>>= (size_t rhs);
        friend Unsigned operator& (const Unsigned& u, const Unsigned& v);
        Unsigned& operator&= (const Unsigned& rhs);
        friend Unsigned operator^ (const Unsigned& u, const Unsigned& v);
        Unsigned& operator^= (const Unsigned& rhs);
        friend Unsigned operator| (const Unsigned& u, const Unsigned& v);
 
        Unsigned& operator|= (const Unsigned& rhs);
 
        friend bool operator< (const Unsigned& u, const Unsigned& v);
 
        friend bool operator<= (const Unsigned& u, const Unsigned& v);
        friend bool operator> (const Unsigned& u, const Unsigned& v);
        friend bool operator>= (const Unsigned& u, const Unsigned& v);
 
        friend bool operator== (const Unsigned& u, const Unsigned& v);
 
        friend bool operator!= (const Unsigned& u, const Unsigned& v);
 
        Digit to_uint() const;
 
        std::string to_string() const;
 
        friend std::ostream& operator<< (std::ostream& os, const Unsigned& u);
        
        friend std::istream& operator>> (std::istream& is, Unsigned& u);
 
    private:
        std::vector<Digit> digits;
 
        void trim();
    };
} // namespace math
#endif
