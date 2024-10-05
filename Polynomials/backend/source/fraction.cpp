#include "../includes/fraction.h"

int64_t Gcd(int64_t first_number, int64_t second_number) {
    if (second_number == 0) {
        throw std::logic_error("Not implemented");
    }
    if (first_number != 0) {
        while (second_number) {
            first_number %= second_number;
            std::swap(first_number, second_number);
        }
        return first_number;
    }
    return 1;
}

Fraction::Fraction(int64_t num, int64_t den) {
    num_ = num;
    den_ = den;
    if (den == 0) {
        throw std::logic_error("Not implemented");
    }
    int64_t gcd = Gcd(num_, den_);
    num_ /= gcd;
    den_ /= gcd;
    if (num_ == 0) {
        den_ = 1;
    }
}

Fraction::Fraction(int64_t num) {
    num_ = num;
    if (den_ == 0) {
        throw std::logic_error("Not implemented");
    }
}

Fraction::Fraction(const Fraction& other) {
    num_ = other.num();
    den_ = other.den();
}

Fraction::~Fraction() {
    clear();
}

int64_t Fraction::num() const {
    return num_;
}

int64_t Fraction::den() const {
    return den_;
}

void Fraction::clear() {
    num_ = 0;
    den_ = 1;
}

void Fraction::reduce() {
    int64_t gcd = Gcd(std::abs(num_), std::abs(den_));
    num_ /= gcd;
    den_ /= gcd;
    if (num_ == 0) {
        den_ = 1;
    }
}

Fraction Fraction::operator=(const Fraction& lhs) {
    num_ = lhs.num_;
    den_ = lhs.den_;
    return *this;
}

std::string Fraction::to_string() {
    std::string ans;
    if (den_ == 1) {
        ans += std::to_string(num_);
    } else {
        ans += "(";
        ans += std::to_string(num_);
        ans += "/";
        ans += std::to_string(den_);
        ans += ")";
    }
    return ans;
}

Fraction abs(Fraction fract) {
    fract.num_ = std::abs(fract.num_);
    fract.den_ = std::abs(fract.den_);
    return fract;
}

Fraction operator+ (const Fraction& fraction) {
    return fraction;
}

Fraction operator- (Fraction fraction) {
    fraction.num_ = -fraction.num_;
    return fraction;
}


Fraction operator+ (const Fraction& lhs, const Fraction& rhs) {
    Fraction current;
    current.num_ = lhs.num() * rhs.den() + lhs.den() * rhs.num();
    current.den_ = lhs.den() * rhs.den();
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator+ (const Fraction& lhs, const int64_t& rhs) {
    Fraction current;
    current.num_ = lhs.num() + lhs.den() * rhs;
    current.den_ = lhs.den();
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator+ (const int64_t& lhs, const Fraction& rhs) {
    Fraction current;
    current.num_ = lhs * rhs.den() + rhs.num();
    current.den_ = rhs.den();
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator- (const Fraction& lhs, const Fraction& rhs) {
    Fraction current;
    current.num_ = lhs.num() * rhs.den() - lhs.den() * rhs.num();
    current.den_ = lhs.den() * rhs.den();
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator- (const Fraction& lhs, const int64_t& rhs) {
    Fraction current;
    current.num_ = lhs.num() - lhs.den() * rhs;
    current.den_ = lhs.den();
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator- (const int64_t& lhs, const Fraction& rhs) {
    Fraction current;
    current.num_ = lhs * rhs.den() - rhs.num();
    current.den_ = rhs.den();
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator* (const Fraction& lhs, const Fraction& rhs) {
    Fraction current;
    current.num_ = lhs.num_ * rhs.num_;
    current.den_ = lhs.den() * rhs.den();
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator* (const Fraction& lhs, const int64_t& rhs) {
    Fraction current;
    current.num_ = lhs.num_ * rhs;
    current.den_ = lhs.den();
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator* (const int64_t& lhs, const Fraction& rhs) {
    Fraction current;
    current.num_ = lhs * rhs.num_;
    current.den_ = rhs.den();
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator/ (const Fraction& lhs, const Fraction& rhs) {
    Fraction current;
    current.num_ = lhs.num_ * rhs.den_;
    current.den_ = lhs.den() * rhs.num_;
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator/ (const Fraction& lhs, const int64_t& rhs) {
    Fraction current;
    current.num_ = lhs.num_;
    current.den_ = lhs.den() * rhs;
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}

Fraction operator/ (const int64_t& lhs, const Fraction& rhs) {
    Fraction current;
    current.num_ = rhs.den_;
    current.den_ = lhs * rhs.num_;
    int64_t gcd = Gcd(std::abs(current.num_), std::abs(current.den_));
    current.num_ /= gcd;
    current.den_ /= gcd;
    if (current.num_ == 0) {
        current.den_ = 1;
    }
    return current;
}


Fraction operator++ (Fraction& fraction) {
    fraction.num_ += fraction.den_;
    if (fraction.num_ == 0) {
        fraction.den_ = 1;
    }
    return fraction;
}

Fraction operator++ (Fraction& fraction, int d_) {
    Fraction current = fraction;
    fraction.num_ += fraction.den_;
    if (fraction.num_ == 0) {
        fraction.den_ = 1;
    }
    return current;
}

Fraction operator-- (Fraction& fraction) {
    fraction.num_ -= fraction.den_;
    if (fraction.num_ == 0) {
        fraction.den_ = 1;
    }
    return fraction;
}

Fraction operator-- (Fraction& fraction, int d_) {
    Fraction current = fraction;
    fraction.num_ -= fraction.den_;
    if (fraction.num_ == 0) {
        fraction.den_ = 1;
    }
    return current;
}


Fraction operator+= (Fraction& lhs, const Fraction& rhs) {
    lhs.num_ = lhs.num_ * rhs.den_ + lhs.den_ * rhs.num_;
    lhs.den_ = lhs.den_ * rhs.den_;
    int64_t gcd = Gcd(std::abs(lhs.num_), std::abs(lhs.den_));
    lhs.den_ /= gcd;
    lhs.num_ /= gcd;
    if (lhs.num_ == 0) {
        lhs.den_ = 1;
    }
    return lhs;
}

Fraction operator+= (Fraction& lhs, const int64_t& rhs) {
    lhs.num_ = lhs.num_ + rhs * lhs.den_;
    lhs.den_ = lhs.den_;
    int64_t gcd = Gcd(std::abs(lhs.num_), std::abs(lhs.den_));
    lhs.den_ /= gcd;
    lhs.num_ /= gcd;
    if (lhs.num_ == 0) {
        lhs.den_ = 1;
    }
    return lhs;
}

Fraction operator-= (Fraction& lhs, const Fraction& rhs) {
    lhs.num_ = lhs.num_ * rhs.den_ - lhs.den_ * rhs.num_;
    lhs.den_ = lhs.den_ * rhs.den_;
    int64_t gcd = Gcd(std::abs(lhs.num_), std::abs(lhs.den_));
    lhs.den_ /= gcd;
    lhs.num_ /= gcd;
    if (lhs.num_ == 0) {
        lhs.den_ = 1;
    }
    return lhs;
}

Fraction operator-= (Fraction& lhs, const int64_t& rhs) {
    lhs.num_ = lhs.num_ - rhs * lhs.den_;
    lhs.den_ = lhs.den_;
    int64_t gcd = Gcd(std::abs(lhs.num_), std::abs(lhs.den_));
    lhs.den_ /= gcd;
    lhs.num_ /= gcd;
    if (lhs.num_ == 0) {
        lhs.den_ = 1;
    }
    return lhs;
}

Fraction operator*= (Fraction& lhs, const Fraction& rhs) {
    lhs.num_ = lhs.num_ * rhs.num_;
    lhs.den_ = lhs.den_ * rhs.den_;
    int64_t gcd = Gcd(std::abs(lhs.num_), std::abs(lhs.den_));
    lhs.den_ /= gcd;
    lhs.num_ /= gcd;
    if (lhs.num_ == 0) {
        lhs.den_ = 1;
    }
    return lhs;
}

Fraction operator*= (Fraction& lhs, const int64_t& rhs) {
    lhs.num_ = lhs.num_ * rhs;
    lhs.den_ = lhs.den_;
    int64_t gcd = Gcd(std::abs(lhs.num_), std::abs(lhs.den_));
    lhs.den_ /= gcd;
    lhs.num_ /= gcd;
    if (lhs.num_ == 0) {
        lhs.den_ = 1;
    }
    return lhs;
}

Fraction operator/= (Fraction& lhs, const Fraction& rhs) {
    lhs.num_ = lhs.num_ * rhs.den_;
    lhs.den_ = lhs.den_ * rhs.num_;
    int64_t gcd = Gcd(std::abs(lhs.num_), std::abs(lhs.den_));
    lhs.den_ /= gcd;
    lhs.num_ /= gcd;
    if (lhs.num_ == 0) {
        lhs.den_ = 1;
    }
    return lhs;
}

Fraction operator/= (Fraction& lhs, const int64_t& rhs) {
    lhs.num_ = lhs.num_;
    lhs.den_ = lhs.den_ * rhs;
    int64_t gcd = Gcd(std::abs(lhs.num_), std::abs(lhs.den_));
    lhs.den_ /= gcd;
    lhs.num_ /= gcd;
    if (lhs.num_ == 0) {
        lhs.den_ = 1;
    }
    return lhs;
}



bool operator< (const Fraction& lhs, const Fraction& rhs) {
    return lhs.num_ * rhs.den_ < lhs.den_ * rhs.num_;
}

bool operator> (const Fraction& lhs, const Fraction& rhs) {
    return !(lhs <= rhs);
}

bool operator>= (const Fraction& lhs, const Fraction& rhs) {
    return !(lhs < rhs);
}

bool operator<= (const Fraction& lhs, const Fraction& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator== (const Fraction& lhs, const Fraction& rhs) {
    return lhs.num_ * rhs.den_ == lhs.den_ * rhs.num_;
}

bool operator!= (const Fraction& lhs, const Fraction& rhs) {
    return !(lhs == rhs);
}

bool operator< (const Fraction& lhs, const int64_t& rhs) {
    return lhs.num_ < lhs.den_ * rhs;
}

bool operator> (const Fraction& lhs, const int64_t& rhs) {
    return !(lhs <= rhs);
}

bool operator>= (const Fraction& lhs, const int64_t& rhs) {
    return !(lhs < rhs);
}

bool operator<= (const Fraction& lhs, const int64_t& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator== (const Fraction& lhs, const int64_t& rhs) {
    return lhs.num_ == lhs.den_ * rhs;
}

bool operator!= (const Fraction& lhs, const int64_t& rhs) {
    return !(lhs == rhs);
}

bool operator< (const int64_t& lhs, const Fraction& rhs) {
    return lhs * rhs.den_ < rhs.num_;
}

bool operator> (const int64_t& lhs, const Fraction& rhs) {
    return !(lhs <= rhs);
}

bool operator>= (const int64_t& lhs, const Fraction& rhs) {
    return !(lhs < rhs);
}

bool operator<= (const int64_t& lhs, const Fraction& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator== (const int64_t& lhs, const Fraction& rhs) {
    return lhs * rhs.den_ == rhs.num_;
}

bool operator!= (const int64_t& lhs, const Fraction& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& out, const Fraction& fract) {
    if (fract.den_ == 1) {
        out << fract.num_;
    } else {
        out << "(" << fract.num_ << "/" << fract.den_ << ")";
    }
    return out;
}
