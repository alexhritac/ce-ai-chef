#include <iostream>
#include "raw_float.h"

int main() {

    raw_float rawFloat{"1234.5678"};
    raw_float rawFloat1{"1234.5678000000"};
    raw_float rawFloat2{"0.123"};
    std::cout << rawFloat.to_string() << '\n';
    std::cout << rawFloat1.to_string() << '\n';
}