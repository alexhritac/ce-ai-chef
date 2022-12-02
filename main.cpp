#include "raw_float.h"

int main() {
    raw_float rawFloat {"4.56"};
    raw_float rawFloat1{"12.56"};
    raw_float rawFloat2{"1.423"};
    raw_float rawFloat3{"4.6"};
    raw_float rawFloat4{"1.56"};

    rawFloat += rawFloat1;
    rawFloat1 -= rawFloat2;
    rawFloat2 *= rawFloat3;
    rawFloat3 /= rawFloat4;

    std::cout << rawFloat.to_string() << '\n';
    std::cout << rawFloat1.to_string() << '\n';
    std::cout << rawFloat2.to_string() << '\n';
    std::cout << rawFloat3.to_string() << '\n';
    std::cout << rawFloat4.to_string() << '\n';
    std::cout << std::endl;

    raw_float rf1 = rawFloat4 + rawFloat4;
    raw_float rf2 = rawFloat3 - rawFloat4;
    raw_float rf3 = rawFloat4 * rawFloat4;
    raw_float rf4 = rawFloat2 / rawFloat4;
    raw_float rf5 = rawFloat4 * rawFloat4;

    std::cout << rf1.to_string() << '\n';
    std::cout << rf2.to_string() << '\n';
    std::cout << rf3.to_string() << '\n';
    std::cout << rf4.to_string() << '\n';
    std::cout << rf5.to_string() << '\n';
    std::cout << std::endl;
}