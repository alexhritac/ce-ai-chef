#include "raw_float.h"

raw_float::raw_float(const std::string& input):
base_{0}{
    auto i{0}, counter{0};
    auto decimal = false;
    while (input[i] == 0)
        ++i;
    while (input[i] != '\0') {
        if (!isdigit(input[i]) && input[i] != '.')
            break;
        else if (input[i] != '.'){
            if (decimal)
                counter--;
            base_ = base_ * 10 + input[i]-48;
        }
        else
            decimal = true;
        ++i;
    }
    exp_ = counter;
    check();
}
std::string raw_float::to_string() const{
    std::ostringstream output{};
    output << std::to_string(base_);
    std::string my_output;
    if (exp() >= 0){
        for (auto i=0; i < exp(); i++)
            output << '0';
        my_output = output.str();
    }
    else {
        my_output = output.str();
        auto size = my_output.length();
        my_output.insert(size+exp(), ".");
    }
    return my_output;
}

long long raw_float::base() const {
    return base_;
}

long long raw_float::exp() const {
    return exp_;
}

raw_float& raw_float::operator+=(const raw_float& second) {
    if (this->exp() == second.exp())
        this->base_ += second.base();
    else if (exp_ > second.exp()) {
        auto multiplicator{1};
        for (auto i = 0; i < exp() - second.exp(); ++i)
            multiplicator *= 10;
        base_ *= multiplicator;
        exp_ = second.exp();
        base_ += second.base();
    }
    else {
        auto multiplicator{1};
        for (auto i = 0; i < second.exp() - exp(); ++i)
            multiplicator *= 10;
        base_ += second.base() * multiplicator;
    }
    return *this;
}

raw_float &raw_float::operator-=(const raw_float &second) {
    if (this->exp() == second.exp())
        this->base_ -= second.base();
    else if (exp_ > second.exp()) {
        auto multiplicator{1};
        for (auto i = 0; i < exp() - second.exp(); ++i)
            multiplicator *= 10;
        base_ *= multiplicator;
        exp_ = second.exp();
        base_ -= second.base();
    }
    else {
        auto multiplicator{1};
        for (auto i = 0; i < second.exp() - exp(); ++i)
            multiplicator *= 10;
        base_ -= second.base() * multiplicator;
    }
    return *this;
}

bool raw_float::operator==(const raw_float &other) const{
    if (this->base() == other.base() && this->exp() == other.exp())
        return true;
    return false;
}

bool raw_float::operator!=(const raw_float &other) const {
    return !(*this == other);
}

void raw_float::check() {
    while (base() % 10 == 0){
        base_/=10;
        exp_ ++;
    }
}
