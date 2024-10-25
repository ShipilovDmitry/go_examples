#ifndef ADD_H
#define ADD_H

#include <CoreBridge/platform_bridge_interop.h>
#include <stdint.h>

// Pointers
struct TrackFilterRef;
typedef struct TrackFilterRef TrackFilterRef;

#ifdef __cplusplus
extern "C"
{
#endif

    int addNums(int a, int b);

    double getDistance();

    void printName();

    TrackFilterRef *createTrackFilter();
    CStringCore getInfo(TrackFilterRef *filter);
    void destroyTrackFilter(TrackFilterRef *filter);

    STDVectorInterop getRefsKinds();

    uint8_t * vector_data(STDVectorInterop vector);
    size_t vector_size(STDVectorInterop vector);
    void vector_destructor(STDVectorInterop vector);


#ifdef __cplusplus
}
#endif

#endif
