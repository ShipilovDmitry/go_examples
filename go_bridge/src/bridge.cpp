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

    CStringCore getInfo(TrackFilterRef *filter)
    {
        auto &trackFilter = *reinterpret_cast<filter::TrackFilter *>(filter);
        auto name = trackFilter.getName();
        auto copy = CStringCopy(name.c_str());
        return copy;
    }

    TrackFilterRef *createTrackFilter()
    {
        auto filter = std::make_unique<filter::TrackFilter>();
        return reinterpret_cast<TrackFilterRef *>(filter.release());
    }

    void destroyTrackFilter(TrackFilterRef *filter)
    {
        delete reinterpret_cast<filter::TrackFilter *>(filter);
    }
}
