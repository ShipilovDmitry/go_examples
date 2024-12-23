#pragma once

#include <string>
#include <vector>

namespace filter
{

    class TrackFilter
    {
    public:
        TrackFilter();
        ~TrackFilter();
        double getDistance() const;
        void printName() const;
        std::string getName() const;

        std::vector<int> getRefsKinds() const;

    private:
        std::string m_name = "TrackFilter";
    };

}
