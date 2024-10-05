#pragma once
#include <exception>
#include <algorithm>
#include <iostream>
#include "polynomial.h"

class Fraction {
public:
    Fraction() = default;
    Fraction(int64_t num, int64_t den);
    Fraction(int64_t num);
    Fraction(const Fraction& other);
    ~Fraction();
    friend Polynomial;

    int64_t num() const;
    int64_t den() const;
    void clear();
    void reduce();

    Fraction operator = (const Fraction& lhs);
    friend Fraction operator + (const Fraction& fruction);
    friend Fraction operator - (Fraction lhs);


    friend Fraction operator + (const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator + (const Fraction& lhs, const int64_t& rhs);
    friend Fraction operator + (const int64_t& lhs, const Fraction& rhs);
    friend Fraction operator - (const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator - (const Fraction& lhs, const int64_t& rhs);
    friend Fraction operator - (const int64_t& lhs, const Fraction& rhs);
    friend Fraction operator * (const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator * (const Fraction& lhs, const int64_t& rhs);
    friend Fraction operator * (const int64_t& lhs, const Fraction& rhs);
    friend Fraction operator / (const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator / (const Fraction& lhs, const int64_t& rhs);
    friend Fraction operator / (const int64_t& lhs, const Fraction& rhs);


    friend Fraction operator++ (Fraction& num);
    friend Fraction operator++ (Fraction& num, int d_);
    friend Fraction operator-- (Fraction& num);
    friend Fraction operator-- (Fraction& num, int d_);


    friend Fraction operator+= (Fraction& lhs, const Fraction& rhs);
    friend Fraction operator+= (Fraction& lhs, const int64_t& rhs);
    friend Fraction operator-= (Fraction& lhs, const Fraction& rhs);
    friend Fraction operator-= (Fraction& lhs, const int64_t& rhs);
    friend Fraction operator*= (Fraction& lhs, const Fraction& rhs);
    friend Fraction operator*= (Fraction& lhs, const int64_t& rhs);
    friend Fraction operator/= (Fraction& lhs, const Fraction& rhs);
    friend Fraction operator/= (Fraction& lhs, const int64_t& rhs);


    friend bool operator< (const Fraction& lhs, const Fraction& rhs);
    friend bool operator> (const Fraction& lhs, const Fraction& rhs);
    friend bool operator>= (const Fraction& lhs, const Fraction& rhs);
    friend bool operator<= (const Fraction& lhs, const Fraction& rhs);
    friend bool operator== (const Fraction& lhs, const Fraction& rhs);
    friend bool operator!= (const Fraction& lhs, const Fraction& rhs);

    friend bool operator< (const Fraction& lhs, const int64_t& rhs);
    friend bool operator> (const Fraction& lhs, const int64_t& rhs);
    friend bool operator>= (const Fraction& lhs, const int64_t& rhs);
    friend bool operator<= (const Fraction& lhs, const int64_t& rhs);
    friend bool operator== (const Fraction& lhs, const int64_t& rhs);
    friend bool operator!= (const Fraction& lhs, const int64_t& rhs);

    friend bool operator< (const int64_t& lhs, const Fraction& rhs);
    friend bool operator> (const int64_t& lhs, const Fraction& rhs);
    friend bool operator>= (const int64_t& lhs, const Fraction& rhs);
    friend bool operator<= (const int64_t& lhs, const Fraction& rhs);
    friend bool operator== (const int64_t& lhs, const Fraction& rhs);
    friend bool operator!= (const int64_t& lhs, const Fraction& rhs);

    std::string to_string();
    friend Fraction abs(Fraction);
    friend std::ostream& operator << (std::ostream& out, const Fraction& fract);

private:
    int64_t num_ = 0, den_ = 1;
};
