
#include <cstdint>
#include <vector>
#include "math_unsigned.h"
#include "math_signed.h"
using std::size_t;


math::Signed::Signed(int n)
: num{n < 0 ? math::Unsigned(-n) : math::Unsigned(n)}, 
positive{n >= 0}
{
}

math::Signed::Signed(unsigned int n) :
num{math::Unsigned(n)},
positive{true}
{
}

math::Signed::Signed (long long n) :
num{n < 0 ? math::Unsigned(-n) : math::Unsigned(n)}, 
positive{n >= 0}
{
}

math::Signed::Signed (unsigned long long n) :
num{math::Unsigned(n)},
positive{true}
{
}

math::Signed::Signed (const math::Signed& copy) :
num{copy.num},
positive{copy.positive}
{
}

math::Signed::Signed (const math::Unsigned& copy) :
num{copy},
positive{true}
{
}

math::Signed& math::Signed::operator= (const math::Signed& rhs)
{
    num = rhs.num;
    positive = rhs.positive;
    return *this;
}

math::Signed& math::Signed::operator= (const math::Signed&& rhs)
{
    num = rhs.num;
    positive = rhs.positive;
    return *this;
}

bool math::operator== (const math::Signed& lhs, const math::Signed& rhs)
{
    return lhs.positive == rhs.positive && lhs.num == rhs.num;
}

bool math::operator != (const math::Signed& lhs, const math::Signed& rhs)
{
    return lhs.positive == rhs.positive && lhs.num != rhs.num;
}

bool math::operator< (const math::Signed& lhs, const math::Signed& rhs)
{
    if(lhs.positive)
    {
        if(!rhs.positive)
        {
            return false;
        }
        return lhs.num < rhs.num;
    }
    if(rhs.positive)
    {
        return true;
    }
    return rhs.num < lhs.num;
}

bool math::operator> (const math::Signed& lhs, const math::Signed& rhs)
{
    if(lhs.positive)
    {
        if(!rhs.positive)
        {
            return true;
        }
        return lhs.num > rhs.num;
    }
    if(rhs.positive)
    {
        return false;
    }
    return rhs.num > lhs.num;
}

bool math::operator<= (const math::Signed& lhs, const math::Signed& rhs)
{
    return !(lhs > rhs);
}

bool math::operator>= (const math::Signed& lhs, const math::Signed& rhs)
{
    return !(lhs < rhs);
}

math::Signed math::Signed::operator-() const
{
    math::Signed ans(*this);
    if(ans == 0)
    {
        return ans;
    }
    ans.positive = !ans.positive;
    return ans;
}


math::Signed& math::Signed::operator %= (const math::Signed& rhs)
{
    num %= rhs.num;
    positive = (positive && rhs.positive) ||
                (!positive && !rhs.positive);
    return *this;
}

math::Signed& math::Signed::operator /= (const math::Signed& rhs)
{
    num /= rhs.num;
    positive = (positive && rhs.positive) ||
                (!positive && !rhs.positive);
    return *this;
}

math::Signed& math::Signed::operator *= (const math::Signed& rhs)
{
    num *= rhs.num;
    positive = (positive && rhs.positive) ||
                (!positive && !rhs.positive);
    return *this;
}

math::Signed& math::Signed::operator += (const math::Signed& rhs)
{
    if((positive && rhs.positive) || (!positive && !rhs.positive))
    {
        num += rhs.num;
        return *this;
    }

    if(positive)
    {
        if(num >= rhs.num)
        {
            num -= rhs.num;
            return *this;
        }
        num = rhs.num - num;
        positive = false;
        return *this;
    }

    if(num >= rhs.num)
    {
        num -= rhs.num;
        return *this;
    }
    num = rhs.num - num;
    positive = true;
    return *this;
}

math::Signed& math::Signed::operator -= (const math::Signed& rhs)
{
    *this += -rhs;
    return *this;
}

math::Signed math::operator% (const math::Signed& lhs, const math::Signed& rhs)
{
    math::Signed ans{lhs};
    ans %= rhs;
    return ans;
}

math::Signed math::operator/ (const math::Signed& lhs, const math::Signed& rhs)
{
    math::Signed ans{lhs};
    ans /= rhs;
    return ans;
}

math::Signed math::operator* (const math::Signed& lhs, const math::Signed& rhs)
{
    math::Signed ans{lhs};
    ans *= rhs;
    return ans;
}

math::Signed math::operator+ (const math::Signed& lhs, const math::Signed& rhs)
{
    math::Signed ans{lhs};
    ans += rhs;
    return ans;
}

math::Signed math::operator- (const math::Signed& lhs, const math::Signed& rhs)
{
    math::Signed ans{lhs};
    ans -= rhs;
    return ans;
}

math::Signed& math::Signed::operator++()
{
    *this += 1;
    return *this;
}

math::Signed math::Signed::operator++(int)
{
    math::Signed ans{*this};
    ++(*this);
    return ans;
}

math::Signed& math::Signed::operator--()
{
    *this -= 1;
    return *this;
}

math::Signed math::Signed::operator--(int)
{
    math::Signed ans{*this};
    --(*this);
    return ans;
}

std::string math::Signed::to_string() const
{
    std::string ans = positive ? "" : "-";
    ans += num.to_string();
    return ans;
}

int math::Signed::to_int ()
{
    return (int) num.to_uint();
}

std::ostream& math::operator<< (std::ostream& os, const math::Signed& u)
{
    os << u.to_string(); return os; }

std::istream& math::operator>> (std::istream& is, math::Signed& u)
{
    if(is.peek() == '-')
    {
        u.positive = false;
        is.get();
        is >> u.num;
    }
    else
    {
        u.positive = true;
        is >> u.num;
    }
    return is;
}
