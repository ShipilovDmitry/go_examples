#include "include/add.h"

#include <string>
#include <iostream>

extern "C" {
int add_nums(int a, int b) {
    std::string s = "Hello, world";
    std::cout << s << std::endl;
    return a + b;
}
}
