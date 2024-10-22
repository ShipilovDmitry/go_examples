#include "include/track_filter.hpp"

#include <iostream>

using namespace filter;

double TrackFilter::getDistance() const
{
    return 42;
}

void TrackFilter::printName() const
{
    std::cout << "TrackFilter" << std::endl;
}
