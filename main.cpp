#include "raw_float.h"

int main() {
    raw_float rawFloat{"1234.5678"};
    raw_float rawFloat1{"1234.5678324123213"};
    raw_float rawFloat2{"1234.5678134"};
    raw_float rawFloat3{"1234.5678534"};
    raw_float rawFloat4{"1234.56781431"};
    std::cout << rawFloat.to_string() << '\n';
    std::cout << rawFloat1.to_string() << '\n';
    std::cout << rawFloat2.to_string() << '\n';
    std::cout << rawFloat3.to_string() << '\n';
    std::cout << rawFloat4.to_string() << '\n';
}