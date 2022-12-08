#include "raw_float.h"

raw_float::raw_float(const std::string &input) :
        base_{0},
        minus_{false} {

    // Checking if the number is negative or positive
    auto i{0};
    if (input[i] == '-') {
        minus_ = true;
        ++i;
    }

    // Decomposing the string into an actual number
    auto pos{0};
    auto counter{-1};
    while (isdigit(input[i]) || input[i] == '.') {
        if (input[i] == '.') {
            counter = 0;
            pos = i;
        } else {
            base_ = base_ * 10 + input[i] - 48;
            if (counter != -1)
                counter++;
            if (counter == cap_digits)
                break;
        }
        ++i;
    }

    // Multiplicating the base with the amount of digits needed to create the full number
    auto multiplication_factor{1};
    for (unsigned int j = 0; counter != cap_digits && j < cap_digits + 1 - (input.size() - pos); ++j)
        multiplication_factor *= 10;
    base_ *= multiplication_factor;
}

std::string raw_float::to_string() const {
    std::string result;

    if (minus()) result += '-';                         // Adding the minus if negative
    result += std::to_string(base_);                    // Adding the raw number

    //TODO: if you have a number like 0.[digits] the to_string() method will print only [digits] and not 0.[digits]

    // Inserting the dot at a specific position if needed
    if (result.size() > cap_digits) result.insert(result.size() - cap_digits, ".");

    // Enable to make it look nicer (without 0's at the end)
    while (result.at(result.length() - 1) == '0') result.erase(result.end() - 1);
    return result;
}

raw_float &raw_float::operator+=(const raw_float &other) {
    // Performing either addition or subtraction depending on the signs
    if (minus() == other.minus()) {
        // Checking if the there is space for this operation
        if (nr_of_bits(this->base()) == sizeof(unsigned long long) * 8 ||
            nr_of_bits(other.base()) == sizeof(unsigned long long) * 8)
            throw std::logic_error("The result of the addition will most probably be out of bounds");
        base_ += other.base();
    } else if (base() > other.base())
        base_ -= other.base();
    else {
        base_ = other.base() - base_;
        minus_ = !minus_;
    }
    return *this;
}

raw_float &raw_float::operator-=(const raw_float &other) {
    // Performing either addition or subtraction depending on the signs
    if (minus() != other.minus()) {
        // Checking if the there is space for this operation
        if (nr_of_bits(this->base()) == sizeof(unsigned long long) * 8 ||
            nr_of_bits(other.base()) == sizeof(unsigned long long) * 8)
            throw std::logic_error("The result of the addition will most probably be out of bounds");
        base_ += other.base();
    } else if (base() > other.base()) {
        base_ -= other.base();
    } else {
        base_ = other.base() - base_;
        minus_ = !minus_;
    }
    return *this;
}

raw_float &raw_float::operator*=(const raw_float &other) {
    // Determining the sign
    minus_ = minus() != other.minus();

    auto aux1 = base();
    auto aux2 = other.base();
    auto multiplicator{1};

    // Checking if the result will be out of bounds
    if (nr_of_bits(aux1) + (nr_of_bits(aux2)) > sizeof(unsigned long long) * 8)
        throw std::logic_error("The result of the multiplication will be out of bounds");

    // Setting the multiplication factor
    for (auto i = 0; i < cap_digits; ++i)
        multiplicator *= 10;
    this->base_ = aux1 * aux2 / multiplicator;

    return *this;
}

raw_float &raw_float::operator/=(const raw_float &other) {
    // Checking the sign of the result
    minus_ = minus() != other.minus();
    auto multiplicator{1};

    // Setting the multiplication factor
    for (auto i = 0; i < cap_digits; ++i)
        multiplicator *= 10;
    base_ = (base_ * multiplicator) / other.base();

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

raw_float raw_float::to_power(unsigned int power) const {
    raw_float result{this->to_string()};
    // Calculating base to the given power
    for (unsigned int i = 0; i < power - 1; i++)
        result *= *this;
    return result;
}

unsigned long long raw_float::base() const {
    return base_;
}

bool raw_float::minus() const {
    return minus_;
}

size_t nr_of_bits(unsigned long long value) {
    size_t size{0};
    // Detecting the most left bit that is stored for 'value'
    while (value > 0) {
        value >>= 1;
        size++;
    }
    return size;
}
