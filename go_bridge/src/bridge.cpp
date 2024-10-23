#include "../include/bridge.h"
#include "track_filter.hpp"
#include <memory>

using CString = const char *;

CString CStringCopy(CString value)
{
    if (value == nullptr)
    {
        return nullptr;
    }

    try
    {
        std::unique_ptr<char[]> owner(new char[std::strlen(value) + 1]); // +1 because of \0
        std::strcpy(owner.get(), value);
        return owner.release();
    }
    catch (std::exception const &exception)
    {
        return nullptr;
    }
}

void CStringRelease(const char * ptr) { std::unique_ptr<char const[]> const deleter(ptr); }

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
