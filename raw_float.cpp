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
    result.insert(result.size() - cap_digits, ".");
    return result;
}      // The printing function is ready

raw_float &raw_float::operator+=(const raw_float &other) {
    return *this;
}

raw_float &raw_float::operator-=(const raw_float &other) {
    return *this;
}

raw_float &raw_float::operator*=(const raw_float &other) {
    return *this;
}

raw_float &raw_float::operator/=(const raw_float &other) {
    return *this;
}

raw_float raw_float::operator+(const raw_float &other) const {
    return *this;
}

raw_float raw_float::operator-(const raw_float &other) const {
    return *this;
}

raw_float raw_float::operator*(const raw_float &other) const {
    return *this;
}

raw_float raw_float::operator/(const raw_float &other) const {
    return *this;
}

bool raw_float::operator<(const raw_float &other) const {
    return false;
}

bool raw_float::operator<=(const raw_float &other) const {
    return false;
}

bool raw_float::operator>(const raw_float &other) const {
    return false;
}

bool raw_float::operator>=(const raw_float &other) const {
    return false;
}

bool raw_float::operator==(const raw_float &other) const {
    return false;
}

bool raw_float::operator!=(const raw_float &other) const {
    return false;
}

raw_float raw_float::sqrt() const {
    return *this;
}

raw_float raw_float::to_power(int power) const {
    return *this;
}

unsigned long long raw_float::base() const {
    return base_;
}

bool raw_float::minus() const {
    return minus_;
}
