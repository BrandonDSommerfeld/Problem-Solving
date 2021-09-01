#include "math_unsigned.h"
#include <sstream>
#include <algorithm>
using std::size_t;


math::Unsigned::Unsigned(math::Unsigned::Digit u) :
    digits(1, u)
{
    // empty
}


math::Unsigned::Unsigned(int u) :
    digits(1, u)
{
    // empty
}

math::Unsigned::Unsigned(math::Unsigned::Wigit u) : digits{}
{
    digits.push_back(u & 0x0000000FFFFFFFFLL);
    digits.push_back((u >> 32) & 0x0000000FFFFFFFFLL);
    trim();
}

math::Unsigned::Unsigned(unsigned long long u) : 
math::Unsigned::Unsigned{static_cast<math::Unsigned::Wigit>(u)}
{

}

math::Unsigned::Unsigned(long long u) : digits{}
{
    digits.push_back(u & 0x0000000FFFFFFFFLL);
    digits.push_back((u >> 32) & 0x0000000FFFFFFFFLL);
    trim();
}

math::Unsigned::Unsigned(const std::string& s) :
    digits(1, 0)
{
    std::istringstream iss(s);
    iss >> *this;
    if (iss.fail() || !iss.eof())
    {
        throw std::runtime_error("Error: Unsigned::string");
    }
}

math::Unsigned::Unsigned(const math::Unsigned& copy) :
    digits(copy.digits)
{
    // empty
}

math::Unsigned& math::Unsigned::operator= (const math::Unsigned& rhs)
{
    digits = rhs.digits;
    return *this;
}

math::Unsigned& math::Unsigned::operator= (const math::Unsigned&& rhs)
{
    digits = rhs.digits;
    return *this;
}

math::Unsigned math::Unsigned::operator++ (int)
{
    math::Unsigned w(*this);
    ++(*this);
    return w;
}

math::Unsigned& math::Unsigned::operator++ ()
{
    for (size_t j = 0; j < digits.size() && ++digits[j] == 0; ++j);
    if (digits.back() == 0)
    {
        digits.push_back(1);
    }
    return *this;
}

math::Unsigned math::Unsigned::operator-- (int)
{
    math::Unsigned w(*this);
    --(*this);
    return w;
}

math::Unsigned& math::Unsigned::operator-- ()
{
    if (digits.back() == 0)
    {
        throw std::underflow_error("Error: Unsigned::underflow");
    }
    for (size_t j = 0; j < digits.size() && digits[j]-- == 0; ++j);
    trim();
    return *this;
}

math::Unsigned math::operator+ (const math::Unsigned& u, const math::Unsigned& v)
{
    math::Unsigned w(u);
    w += v;
    return w;
}

math::Unsigned& math::Unsigned::operator+= (const math::Unsigned& rhs)
{
    const size_t n = rhs.digits.size();
    if (digits.size() < n)
    {
        digits.resize(n, 0);
    }
    size_t j = 0;
    math::Unsigned::Wigit k = 0;
    for (; j < n; ++j)
    {
        k = k + digits[j] + rhs.digits[j];
        digits[j] = static_cast<Digit>(k);
        k >>= math::Unsigned::BITS;
    }
    for (; k != 0 && j < digits.size(); ++j)
    {
        k += digits[j];
        digits[j] = static_cast<Digit>(k);
        k >>= math::Unsigned::BITS;
    }
    if (k != 0)
    {
        digits.push_back(1);
    }
    return *this;
}

math::Unsigned math::operator- (const math::Unsigned& u, const math::Unsigned& v)
{
    math::Unsigned w(u);
    w -= v;
    return w;
}

math::Unsigned& math::Unsigned::operator-= (const math::Unsigned& rhs)
{
    if ((*this) < rhs)
    {
        throw std::underflow_error("Error: Unsigned::underflow");
    }
    size_t j = 0;
    math::Unsigned::Wigit k = 0;
    for (; j < rhs.digits.size(); ++j)
    {
        k = k + digits[j] - rhs.digits[j];
        digits[j] = static_cast<math::Unsigned::Digit>(k);
        k = ((k >> math::Unsigned::BITS) ? -1 : 0);
    }
    for (; k != 0 && j < digits.size(); ++j)
    {
        k += digits[j];
        digits[j] = static_cast<math::Unsigned::Digit>(k);
        k = ((k >> math::Unsigned::BITS) ? -1 : 0);
    }
    trim();
    return *this;
}

math::Unsigned math::operator* (const math::Unsigned& u, const math::Unsigned& v)
{
    const size_t m = u.digits.size();
    const size_t n = v.digits.size();
    math::Unsigned w;
    w.digits.resize(m + n, 0);
    for (size_t j = 0; j < n; ++j)
    {
        math::Unsigned::Wigit k = 0;
        for (size_t i = 0; i < m; ++i)
        {
            k += static_cast<math::Unsigned::Wigit>(u.digits[i]) * v.digits[j] +
                w.digits[i + j];
            w.digits[i + j] = static_cast<math::Unsigned::Digit>(k);
            k >>= math::Unsigned::BITS;
        }
        w.digits[j + m] = static_cast<math::Unsigned::Digit>(k);
    }
    w.trim();
    return w;
}
    
math::Unsigned& math::Unsigned::operator*= (const math::Unsigned& rhs)
{
    *this = (*this) * rhs;
    return *this;
}

math::Unsigned math::operator/ (const math::Unsigned& u, const math::Unsigned& v)
{
    math::Unsigned q, r;
    u.divide(v, q, r);
    return q;
}

math::Unsigned& math::Unsigned::operator/= (const math::Unsigned& rhs)
{
    math::Unsigned r;
    divide(rhs, *this, r);
    return *this;
}

math::Unsigned math::operator% (const math::Unsigned& u, const math::Unsigned& v)
{
    math::Unsigned q, r;
    u.divide(v, q, r);
    return r;
}

math::Unsigned& math::Unsigned::operator%= (const math::Unsigned& rhs)
{
    math::Unsigned q;
    divide(rhs, q, *this);
    return *this;
}

void math::Unsigned::divide(math::Unsigned v, math::Unsigned& q, math::Unsigned& r) const
{
    // Handle special cases (m < n).
    if (v.digits.back() == 0)
    {
        throw std::overflow_error("Error: Unsigned::overflow");
    }
    r.digits = digits;
    const size_t n = v.digits.size();
    if (digits.size() < n) { q.digits.assign(1, 0); return; } // Normalize divisor (v[n-1] >= BASE/2).
    unsigned d = math::Unsigned::BITS;
    for (math::Unsigned::Digit vn = v.digits.back(); vn != 0; vn >>= 1, --d);
    v <<= d;
    r <<= d;
    const math::Unsigned::Digit vn = v.digits.back();

    // Ensure first single-digit quotient (u[m-1] < v[n-1]).
    r.digits.push_back(0);
    const size_t m = r.digits.size();
    q.digits.resize(m - n);
    math::Unsigned w;
    w.digits.resize(n + 1);
    const math::Unsigned::Wigit MAX_DIGIT = (static_cast<math::Unsigned::Wigit>(1) << math::Unsigned::BITS) - 1;
    for (size_t j = m - n; j-- != 0;)
    {
        // Estimate quotient digit.
        math::Unsigned::Wigit qhat = std::min(MAX_DIGIT,
            (static_cast<math::Unsigned::Wigit>(r.digits[j + n]) << math::Unsigned::BITS |
                r.digits[j + n - 1]) / vn);

        // Compute partial product (w = qhat * v).
        math::Unsigned::Wigit k = 0;
        for (size_t i = 0; i < n; ++i)
        {
            k += qhat * v.digits[i];
            w.digits[i] = static_cast<math::Unsigned::Digit>(k);
            k >>= math::Unsigned::BITS;
        }
        w.digits[n] = static_cast<math::Unsigned::Digit>(k);

        // Check if qhat is too large (u - w < 0).
        bool is_trial = true;
        while (is_trial)
        {
            size_t i = n;
            for (; i != 0 && r.digits[j + i] == w.digits[i]; --i);
            if ((is_trial = (r.digits[j + i] < w.digits[i])))
            {
                // Adjust partial product (w -= v).
                --qhat;
                k = 0;
                for (size_t i = 0; i < n; ++i)
                {
                    k = k + w.digits[i] - v.digits[i];
                    w.digits[i] = static_cast<math::Unsigned::Digit>(k);
                    k = ((k >> math::Unsigned::BITS) ? -1 : 0);
                }
                w.digits[n] = static_cast<math::Unsigned::Digit>(k + w.digits[n]);
            }
        }
        q.digits[j] = static_cast<math::Unsigned::Digit>(qhat);

        // Compute partial remainder (u -= w).
        k = 0;
        for (size_t i = 0; i < n; ++i)
        {
            k = k + r.digits[j + i] - w.digits[i];
            r.digits[j + i] = static_cast<math::Unsigned::Digit>(k);
            k = ((k >> math::Unsigned::BITS) ? -1 : 0);
        }
    }

    // Denormalize remainder.
    q.trim();
    r.digits.resize(n);
    r >>= d;
}

math::Unsigned math::operator<< (const math::Unsigned& u, size_t v)
{
    math::Unsigned w(u);
    w <<= v;
    return w;
}

math::Unsigned& math::Unsigned::operator<<= (size_t rhs)
{
    if (digits.back() != 0 && rhs != 0)
    {
        const size_t n = rhs / math::Unsigned::BITS;
        digits.insert(digits.begin(), n, 0);
        rhs -= n * math::Unsigned::BITS;
        math::Unsigned::Wigit k = 0;
        for (size_t j = n; j < digits.size(); ++j)
        {
            k |= static_cast<math::Unsigned::Wigit>(digits[j]) << rhs;
            digits[j] = static_cast<math::Unsigned::Digit>(k);
            k >>= math::Unsigned::BITS;
        }
        if (k != 0)
        {
            digits.push_back(static_cast<math::Unsigned::Digit>(k));
        }
    }
    return *this;
}

math::Unsigned math::operator>> (const math::Unsigned& u, size_t v)
{
    math::Unsigned w(u);
    w >>= v;
    return w;
}

math::Unsigned& math::Unsigned::operator>>= (size_t rhs)
{
    const size_t n = rhs / math::Unsigned::BITS;
    if (n >= digits.size())
    {
        digits.assign(1, 0);
    }
    else
    {
        digits.erase(digits.begin(), digits.begin() + n);
        rhs -= n * math::Unsigned::BITS;
        math::Unsigned::Wigit k = 0;
        for (size_t j = digits.size(); j-- != 0;)
        {
            k = k << math::Unsigned::BITS | digits[j];
            digits[j] = static_cast<math::Unsigned::Digit>(k >> rhs);
            k = static_cast<math::Unsigned::Digit>(k);
        }
        trim();
    }
    return *this;
}

math::Unsigned math::operator& (const math::Unsigned& u, const math::Unsigned& v)
{
    math::Unsigned w(u);
    w &= v;
    return w;
}

math::Unsigned& math::Unsigned::operator&= (const math::Unsigned& rhs)
{
    const size_t n = rhs.digits.size();
    if (digits.size() > n)
    {
        digits.resize(n);
    }
    for (size_t j = 0; j < digits.size(); ++j)
    {
        digits[j] &= rhs.digits[j];
    }
    trim();
    return *this;
}

math::Unsigned math::operator^ (const math::Unsigned& u, const math::Unsigned& v)
{
    math::Unsigned w(u);
    w ^= v;
    return w;
}

math::Unsigned& math::Unsigned::operator^= (const math::Unsigned& rhs)
{
    const size_t n = rhs.digits.size();
    if (digits.size() < n)
    {
        digits.resize(n, 0);
    }
    for (size_t j = 0; j < n; ++j)
    {
        digits[j] ^= rhs.digits[j];
    }
    trim();
    return *this;
}

math::Unsigned math::operator| (const math::Unsigned& u, const math::Unsigned& v)
{
    math::Unsigned w(u);
    w |= v;
    return w;
}

math::Unsigned& math::Unsigned::operator|= (const math::Unsigned& rhs)
{
    const size_t n = rhs.digits.size();
    if (digits.size() < n)
    {
        digits.resize(n, 0);
    }
    for (size_t j = 0; j < n; ++j)
    {
        digits[j] |= rhs.digits[j];
    }
    return *this;
}

bool math::operator< (const math::Unsigned& u, const math::Unsigned& v)
{
    const size_t m = u.digits.size();
    size_t n = v.digits.size();
    if (m != n)
    {
        return (m < n);
    }
    for (--n; n != 0 && u.digits[n] == v.digits[n]; --n);
    return (u.digits[n] < v.digits[n]); 
} 
bool math::operator> (const math::Unsigned& u, const math::Unsigned& v)
{
    return (v < u);
}

bool math::operator<= (const math::Unsigned& u, const math::Unsigned& v)
{
    return !(v < u); } 
bool math::operator>= (const math::Unsigned& u, const math::Unsigned& v)
{
    return !(u < v);
}

bool math::operator== (const math::Unsigned& u, const math::Unsigned& v)
{
    return (u.digits == v.digits);
}

bool math::operator!= (const math::Unsigned& u, const math::Unsigned& v)
{
    return (u.digits != v.digits);
}

math::Unsigned::Digit math::Unsigned::to_uint() const
{
    return digits[0];
}

std::string math::Unsigned::to_string() const
{
    std::ostringstream oss;
    math::Unsigned q(*this), r;
    do
    {
        q.divide((math::Unsigned::Digit) 10, q, r);
        oss << r.digits[0];
    } while (q.digits.back() != 0);
    std::string s(oss.str());
    std::reverse(s.begin(), s.end());
    return s;
}

std::ostream& math::operator<< (std::ostream& os, const math::Unsigned& u)
{
    os << u.to_string(); return os; } 

std::istream& math::operator>> (std::istream& is, math::Unsigned& u)
{
    char digit = '\0';
    is >> digit;
    if (is.good() && std::isdigit(digit))
    {
        u = (math::Unsigned::Digit) digit - '0';
        while (std::isdigit(is.peek()))
        {
            is >> digit;
            u = (math::Unsigned::Digit) 10 * u + ((math::Unsigned::Digit) digit - '0');
        }
    }
    else
    {
        is.setstate(std::ios_base::failbit);
    }
    return is;
}

void math::Unsigned::trim()
{
    while (digits.back() == 0 && digits.size() > 1)
    {
        digits.pop_back();
    }
}
