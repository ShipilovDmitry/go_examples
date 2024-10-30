#include "../include/bridge.h"
#include "track_filter.hpp"
#include <iostream>
#include <memory>

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

    STDVectorInterop getRefsKinds()
    {
        std::vector<C_RefsKinds> refsKinds = {{1, 2}, {3, 4}, {5, 6}};
        return corendk::createVectorFromStdVector(std::move(refsKinds));
    }

    uint8_t *vector_data(STDVectorInterop vector)
    {
        return vector.dataGetter(vector.vector);
    }

    size_t vector_size(STDVectorInterop vector)
    {
        return vector.sizeInBytesGetter(vector.vector);
    }

    void vector_destructor(STDVectorInterop vector)
    {
        vector.destructor(vector.vector);
    }

    STDVectorInterop getIntsArray()
    {
        filter::TrackFilter filter;
        auto kinds = filter.getRefsKinds();
        return corendk::createVectorFromStdVector(std::move(kinds));
    }

    void ints_array(uint8_t *data, size_t size)
    {
        int32_t *ints = reinterpret_cast<int32_t *>(data);
        std::vector<int32_t> vec;
        vec.reserve(size);

        for (size_t i = 0; i < size; ++i)
        {
            vec.push_back(ints[i]);
        }

        for (auto i : vec)
        {
            std::cout << i << std::endl;
        }
    }

    void refs_kinds_array(uint8_t *data, size_t size)
    {
        C_RefsKinds *refsKinds = reinterpret_cast<C_RefsKinds *>(data);
        std::vector<C_RefsKinds> vec;
        vec.reserve(size);
        for (size_t i = 0; i < size; ++i)
        {
            vec.push_back(refsKinds[i]);
        }

        for (auto i : vec)
        {
            std::cout << i.refs << " " << i.kinds << std::endl;
        }
    }

    void get_go_callback(void (*callback)()) {
        callback();
    }
}