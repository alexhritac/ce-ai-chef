#ifndef TOPIC1DEMO_RAW_FLOAT_H
#define TOPIC1DEMO_RAW_FLOAT_H
#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <cmath>

class raw_float {
public:
    explicit raw_float(const std::string& input);

    [[nodiscard]] std::string to_string() const;

    raw_float& operator+=(const raw_float& second);
    raw_float& operator-=(const raw_float& second);
    bool operator==(const raw_float& other)const;
    bool operator!=(const raw_float& other) const;

    [[nodiscard]] long long base() const;
    [[nodiscard]] long long exp() const;
private:
    void check();
    long long base_;
    long long exp_;
};


#endif //TOPIC1DEMO_RAW_FLOAT_H
