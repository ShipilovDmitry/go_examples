#include "../include/bridge.h"
#include "track_filter.hpp"

extern "C" {
int addNums(int a, int b) {
    return a + b;
}

double getDistance() {
    filter::TrackFilter filter;
    return filter.getDistance();
}

void printName() {
    filter::TrackFilter filter;
    filter.printName();
}

}
