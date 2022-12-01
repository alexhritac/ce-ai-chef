#ifndef TOPIC1DEMO_RAW_FLOAT_H
#define TOPIC1DEMO_RAW_FLOAT_H
#include <iostream>
#include <string>
#include <thread>
#include <sstream>

#define cap_digits 6

class raw_float {
public:
    // Constructor
    explicit raw_float(const std::string& input);

    // Printing function
    [[nodiscard]] std::string to_string() const;

    // Operators
    raw_float& operator+=(const raw_float& other);
    raw_float& operator-=(const raw_float& other);
    raw_float& operator*=(const raw_float& other);
    raw_float& operator/=(const raw_float& other);
    raw_float operator+(const raw_float& other) const;
    raw_float operator-(const raw_float& other) const;
    raw_float operator*(const raw_float& other) const;
    raw_float operator/(const raw_float& other) const;

    // Comparison operators
    bool operator< (const raw_float& other) const;
    bool operator<=(const raw_float& other) const;
    bool operator> (const raw_float& other) const;
    bool operator>=(const raw_float& other) const;
    bool operator==(const raw_float& other) const;
    bool operator!=(const raw_float& other) const;

    // Extra functions
    raw_float sqrt() const;
    raw_float to_power(int power) const;
    // Get functions
    [[nodiscard]] unsigned long long base() const;
    [[nodiscard]] bool minus() const;
private:
    unsigned long long base_;
    bool minus_;
};


#endif //TOPIC1DEMO_RAW_FLOAT_H
