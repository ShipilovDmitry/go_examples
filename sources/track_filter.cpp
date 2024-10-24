#include "include/track_filter.hpp"

#include <iostream>

using namespace filter;

TrackFilter::TrackFilter()
{
    std::cout << "TrackFilter::Ctor" << std::endl;
}

double TrackFilter::getDistance() const
{
    return 42;
}

void TrackFilter::printName() const
{
    std::cout << "TrackFilter: printName" << std::endl;
}

std::string TrackFilter::getName() const
{
    return m_name;
}

TrackFilter::~TrackFilter()
{
    std::cout << "TrackFilter destructor" << std::endl;
}