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

    struct C_RefsKinds {
        int refs;
        int kinds;
    };

    int addNums(int a, int b);

    double getDistance();

    void get_go_callback(void (*callback)());

    TrackFilterRef *createTrackFilter();
    CStringCore getInfo(TrackFilterRef *filter);
    void destroyTrackFilter(TrackFilterRef *filter);


    STDVectorInterop getIntsArray();
    STDVectorInterop getRefsKinds();

    uint8_t * vector_data(STDVectorInterop vector);
    size_t vector_size(STDVectorInterop vector);
    void vector_destructor(STDVectorInterop vector);

    void ints_array(uint8_t *data, size_t size);
    void refs_kinds_array(uint8_t * data, size_t size);

#ifdef __cplusplus
}
#endif

#endif
