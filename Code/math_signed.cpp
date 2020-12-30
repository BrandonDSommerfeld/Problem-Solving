#ifndef MATH_SIGNED_H
#define MATH_SIGNED_H

#include <cstdint>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <cctype>
#include "math_unsigned.cpp"
using std::size_t;

namespace math
{
    class Signed
    {
    private:
        math::Unsigned num;
        bool positive;
    public:
        Signed(int n = 0)
        {
            num = n < 0 ? math::Unsigned(-n) : math::Unsigned(n);
            positive = n < 0 ? false : true;
        }

        Signed (const Signed& copy)
        {
            num = math::Unsigned(copy.num);
            positive = copy.positive;
        }

        Signed (const Unsigned& copy)
        {
            num = math::Unsigned(copy);
            positive = true;
        }

        Signed& operator= (const Signed& rhs)
        {
            num = rhs.num;
            positive = rhs.positive;
            return *this;
        }

        bool operator== (const Signed& rhs)
        {
            return num == rhs.num;
        }

        bool operator != (const Signed& rhs)
        {
            return num != rhs.num;
        }

        bool operator< (const Signed& rhs)
        {
            if(positive)
            {
                if(!rhs.positive)
                {
                    return false;
                }
                return num < rhs.num;
            }
            if(rhs.positive)
            {
                return true;
            }
            return rhs.num < num;
        }

        bool operator> (const Signed& rhs)
        {
            return !(*this < rhs || *this == rhs);
        }

        bool operator<= (const Signed& rhs)
        {
            return !(*this > rhs);
        }

        bool operator>= (const Signed& rhs)
        {
            return !(*this < rhs);
        }

        Signed operator-() const
        {
            Signed ans(*this);
            if(ans == 0)
            {
                return ans;
            }
            ans.positive = !ans.positive;
            return ans;
        }

        
        Signed& operator %= (const Signed& rhs)
        {
            num %= rhs.num;
            positive = (positive && rhs.positive) ||
                        (!positive && !rhs.positive);
            return *this;
        }

        Signed& operator /= (const Signed& rhs)
        {
            num /= rhs.num;
            positive = (positive && rhs.positive) ||
                        (!positive && !rhs.positive);
            return *this;
        }

        Signed& operator *= (const Signed& rhs)
        {
            num *= rhs.num;
            positive = (positive && rhs.positive) ||
                        (!positive && !rhs.positive);
            return *this;
        }

        Signed& operator += (const Signed& rhs)
        {
            if(positive && rhs.positive || !positive && !rhs.positive)
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

        Signed& operator -= (const Signed& rhs)
        {
            *this += -rhs;
            return *this;
        }

        Signed operator% (const Signed& rhs)
        {
            Signed ans{*this};
            ans %= rhs;
            return ans;
        }

        Signed operator/ (const Signed& rhs)
        {
            Signed ans{*this};
            ans /= rhs;
            return ans;
        }

        Signed operator* (const Signed& rhs)
        {
            Signed ans{*this};
            ans *= rhs;
            return ans;
        }

        Signed operator+ (const Signed& rhs)
        {
            Signed ans{*this};
            ans += rhs;
            return ans;
        }

        Signed operator- (const Signed& rhs)
        {
            Signed ans{*this};
            ans -= rhs;
            return ans;
        }

        Signed& operator++()
        {
            *this += 1;
            return *this;
        }

        Signed operator++(int)
        {
            Signed ans{*this};
            ++(*this);
            return ans;
        }

        Signed& operator--()
        {
            *this -= 1;
            return *this;
        }

        Signed operator--(int)
        {
            Signed ans{*this};
            --(*this);
            return ans;
        }

        std::string to_string() const
        {
            std::string ans = positive ? "" : "-";
            ans += num.to_string();
            return ans;
        }

        friend std::ostream& operator<< (std::ostream& os, const Signed& u)
        {
            os << u.to_string(); return os; }
    };
    
} // namespace math

#endif