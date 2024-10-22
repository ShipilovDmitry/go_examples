#pragma once

#include <string>
#include <vector>

namespace filter {

class TrackFilter
{
public:
    double getDistance() const;
    void printName() const;

private:
    std::string name;
};

}
