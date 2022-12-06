#include "raw_float.h"

raw_float::raw_float(const std::string &input):     // The constructor is ready
base_{0},
minus_{false}{
    auto i{0};
    if (input[i] == '-'){
        minus_ = true;
        ++i;
    }
    auto pos{0};
    auto counter{-1};
    while (isdigit(input[i]) || input[i] == '.'){
        if (input[i] == '.'){
            counter = 0;
            pos = i;
        }
        else{
            base_ = base_ * 10 + input[i] - 48;
            if (counter != -1)
                counter ++;
            if (counter == cap_digits)
                break;
        }
        ++i;
    }
    auto multiplication{1};
    for (unsigned int j = 0; counter != cap_digits && j < cap_digits +1-(input.size() - pos); ++j)
        multiplication *= 10;
    base_ *= multiplication;
}

std::string raw_float::to_string() const {
    std::string result;
    if (minus()) result += '-';
    result += std::to_string(base_);
    if (result.size() > cap_digits) result.insert(result.size() - cap_digits, ".");
    return result;
}      // The printing function is ready

raw_float &raw_float::operator+=(const raw_float &other) {
    if (minus() == other.minus())
        base_ += other.base();
    else if (base() > other.base())
        base_ -= other.base();
    else {
        base_ = other.base() - base_;
        minus_ = !minus_;
    }
    return *this;
}

raw_float &raw_float::operator-=(const raw_float &other) {
    if (minus() != other.minus())
        base_ += other.base();
    else if (base() > other.base()){
        base_ -= other.base();
    }
    else{
        base_ = other.base() - base_;
        minus_ = !minus_;
    }
    return *this;
}

raw_float &raw_float::operator*=(const raw_float &other) {
    minus_ = minus() != other.minus();
    auto aux1 = base();
    auto aux2 = other.base();
    auto multiplicator{1};
    for (auto i = 0; i < cap_digits; ++i)
        multiplicator *= 10;
    this->base_ = aux1 * aux2 / multiplicator;
    return *this;
}

raw_float &raw_float::operator/=(const raw_float &other) {
    minus_ = minus() != other.minus();
    auto multiplicator{1};
    for (auto i = 0; i < cap_digits; ++i)
        multiplicator *= 10;
    base_ = (base_ * multiplicator)/other.base();
    return *this;
}

raw_float raw_float::operator+(const raw_float &other) const {
    raw_float result{"0.0"};
    result += *this;
    result += other;
    return result;
}

raw_float raw_float::operator-(const raw_float &other) const {
    raw_float result{"0.0"};
    result += *this;
    result -= other;
    return result;
}

raw_float raw_float::operator*(const raw_float &other) const {
    raw_float result{"1.0"};
    result *= *this;
    result *= other;
    return result;
}

raw_float raw_float::operator/(const raw_float &other) const {
    raw_float result{"1.0"};
    result *= *this;
    result /= other;
    return result;
}

bool raw_float::operator<(const raw_float &other) const {
    return (base() < other.base());
}

bool raw_float::operator<=(const raw_float &other) const {
    return (base() <= other.base());
}

bool raw_float::operator>(const raw_float &other) const {
    return (base() > other.base());
}

bool raw_float::operator>=(const raw_float &other) const {
    return (base() >= other.base());
}

bool raw_float::operator==(const raw_float &other) const {
    return (base() == other.base());
}

bool raw_float::operator!=(const raw_float &other) const {
    return (base() != other.base());
}

raw_float raw_float::sqrt() const {
    return *this;
}

raw_float raw_float::to_power(int power) const {
    raw_float result{this->to_string()};
    for (auto i = 0; i < power -1; i++)
        result *= *this;
    return result;
}

unsigned long long raw_float::base() const {
    return base_;
}

bool raw_float::minus() const {
    return minus_;
}
