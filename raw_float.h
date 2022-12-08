#ifndef TOPIC1DEMO_RAW_FLOAT_H
#define TOPIC1DEMO_RAW_FLOAT_H
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#define cap_digits 8

class raw_float {
public:
    // Constructor
    explicit raw_float(const std::string& input);

    // Printing function
    std::string to_string() const;

    // Operators
    raw_float& operator+=(const raw_float& other);

    raw_float &operator-=(const raw_float &other);

    raw_float &operator*=(const raw_float &other);

    raw_float &operator/=(const raw_float &other);

    raw_float operator+(const raw_float &other) const;

    raw_float operator-(const raw_float &other) const;

    raw_float operator*(const raw_float &other) const;

    raw_float operator/(const raw_float &other) const;

    // Comparison operators
    bool operator<(const raw_float &other) const;

    bool operator<=(const raw_float &other) const;

    bool operator>(const raw_float &other) const;

    bool operator>=(const raw_float &other) const;

    bool operator==(const raw_float &other) const;

    bool operator!=(const raw_float &other) const;

    // Extra functions
    raw_float to_power(unsigned int power) const;

    // Get functions
    unsigned long long base() const;

    bool minus() const;

    friend size_t nr_of_bits(unsigned long long value);

private:
    unsigned long long base_;
    bool minus_;
};

size_t nr_of_bits(unsigned long long value);
#endif //TOPIC1DEMO_RAW_FLOAT_H
