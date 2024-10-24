#include "../include/bridge.h"
#include "track_filter.hpp"
#include <memory>

using CStringCore = const char *;

extern "C"
{
    int addNums(int a, int b)
    {
        return a + b;
    }

    double getDistance()
    {
        filter::TrackFilter filter;
        return filter.getDistance();
    }

    void printName()
    {
        filter::TrackFilter filter;
        filter.printName();
    }

    char const *getInfo()
    {
        filter::TrackFilter filter;
        auto name = filter.getName();
        auto copy = CStringCopy(name.c_str());
        return copy;
    }
}
