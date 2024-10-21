#include "../include/add.h"
#include "track_filter.hpp"

#include <string>
#include <iostream>

extern "C" {
int add_nums(int a, int b) {
    filter::TrackFilter filter;
    std::cout << filter.getDistance() << std::endl;
    return a + b;
}
}
