#pragma once

#include <string>
#include <vector>

namespace filter {

class TrackFilter
{
public:
    double getDistance() const;

private:
    std::string name;
};

}
