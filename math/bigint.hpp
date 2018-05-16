#pragma once

#include<vector>
#include<iostream>
#include<iomanip>

/**
 * An signed big integer
 **/
const uint32_t BASE = 1000000000;
const size_t BASE_DIGITS = 9;

class bigint_t {
private:
    bool sign;
    std::vector<int32_t> a;
public:
    bigint_t(int64_t value)
    {
        sign = value >= 0;
        for (int64_t v = std::abs(value); v > 0; v /= BASE)
            a.push_back(v % BASE);
    }
    bigint_t& operator = (const bigint_t& rhs)
    {
        if (this != &rhs) 
        {
            sign = rhs.sign;
            a = rhs.a;
        }
        return *this;
    }
    const bigint_t operator -() const 
    {
        bigint_t ret = *this;
        ret.sign = !ret.sign;
        return ret;
    }

    // Addition
    bigint_t& operator += (const bigint_t& rhs)
    {
        if (sign != rhs.sign)
        {
            *this -= (-rhs);
            return *this;
        }
        a.resize(std::max(a.size(), rhs.a.size()), 0);
        int32_t carry = 0;
        for (size_t i=0; i<a.size(); ++i)
        {
            a[i] += (carry + (i < rhs.a.size() ? rhs.a[i] : 0));
            carry = a[i] > BASE;
            a[i] %= BASE;
        }
        if (carry > 0)
        {
            a.push_back(carry);
        }
        return *this;
    }
    const bigint_t operator + (const bigint_t& rhs) const 
    {
        bigint_t result = *this;
        result += rhs;
        return result;
    }

    // Substraction
    bigint_t& operator -= (const bigint_t& rhs)
    {
        if (sign != rhs.sign)
        {
            *this += (-rhs);
            return *this;
        }
        a.resize(std::max(a.size(), rhs.a.size()), 0);
        int32_t carry = 0;
        for (size_t i=0; i<a.size(); ++i)
        {
            a[i] -= (carry + (i < rhs.a.size() ? rhs.a[i] : 0));
            carry = a[i] < 0;
            a[i] = (a[i] + BASE) % BASE;
        }
        if (carry)
        {
            sign = !sign;
            for (int i=0; i<a.size(); ++i)
                a[i] = BASE - a[i];
        }
        while (a.size() > 0 && a.back() == 0)
            a.pop_back();
        return *this;
    }
    const bigint_t operator - (const bigint_t& rhs) const {
        bigint_t result = *this;
        result += rhs;
        return result;
    }

    // Multiplication
    bigint_t& operator *= (const bigint_t& rhs)
    {
        sign &= rhs.sign;

        std::vector<int64_t> temp(a.size() + rhs.a.size() - 1, 0);
        for (size_t i=0; i<a.size(); ++i)
            for (size_t j=0; j<rhs.a.size(); ++j)
                temp[i + j] += ((int64_t) a[i]) * rhs.a[j];

        a.resize(temp.size(), 0);
        int64_t carry = 0;
        for (size_t i=0; i<temp.size(); ++i) 
        {
            carry += temp[i];
            a[i] = carry % BASE;
            carry /= BASE;
        }
        for (; carry > 0; carry /= BASE)
            a.push_back(carry % BASE);
        return *this;
    }
    const bigint_t operator * (const bigint_t& rhs) const {
        bigint_t result = *this;
        result *= rhs;
        return result;
    }

    // Division 
    bigint_t& operator /= (const uint32_t rhs)
    {
        uint32_t carry = 0;
        for (int32_t i=a.size() - 1; i>=0; --i)
        {
            uint64_t value = ((uint64_t)carry) * BASE + a[i];
            a[i] = value / rhs;
            carry = value % rhs;
        }
        while (a.size() > 0 && a.back() == 0)
            a.pop_back();
        return *this;
    }

    friend std::ostream& operator<< (std::ostream& stream, const bigint_t& n) 
    {
        stream << (n.sign ? "" : "-");
        stream << (n.a.empty() ? 0 : n.a.back());
        for (int32_t i = n.a.size() - 2; i >= 0; --i)
            stream << std::setw(BASE_DIGITS) << std::setfill('0') << n.a[i];
        return stream;
    }
};
