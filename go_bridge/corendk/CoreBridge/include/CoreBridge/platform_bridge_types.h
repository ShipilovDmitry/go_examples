#pragma once

#if __APPLE__
#    include <CoreFoundation/CFAvailability.h>
// This macro generates native Swift enum with given RawValue type from C enum
#    define PLATFORM_ENUM_BEGIN typedef CF_CLOSED_ENUM
#    define PLATFORM_ENUM_END(_name)

#else
// On other platforms they leave it as integer constants
#    define PLATFORM_ENUM_BEGIN(_type, _name) enum _name
#    define PLATFORM_ENUM_END(_name) typedef enum _name _name
#endif

#define DEFINE_TYPE(TYPE_NAME)                                                                     \
    typedef struct TYPE_NAME {                                                                     \
        bool dummy__;                                                                              \
    } TYPE_NAME

#ifdef __cplusplus
#    include <cstdint>
#    include <cstdlib>
#    include <cstring>
#    define NOEXCEPT noexcept
extern "C" {
#else
#    include <stdbool.h>
#    include <stdint.h>
#    include <stdlib.h>
#    include <string.h>
#    define NOEXCEPT
#endif

// Convenient types
typedef char const * CStringCore;

typedef struct SizedString {
    CStringCore str;
    size_t size;
} SizedString;

typedef struct SizedU64Array {
    uint64_t const * pointer;
    size_t size;
} SizedU64Array;

typedef struct COptionalInt {
    int32_t value;
    bool hasValue;
} COptionalInt;

typedef struct COptionalSizeT {
    size_t value;
    bool hasValue;
} COptionalSizeT;

typedef struct COptionalDouble {
    double value;
    bool hasValue;
} COptionalDouble;

typedef struct COptionalBool {
    bool value;
    bool hasValue;
} COptionalBool;

PLATFORM_ENUM_BEGIN(int, CoreGPSInfoSource){
    kCoreGPSInfoSourceUndefined, kCoreGPSInfoSourceAppleNative, kCoreGPSInfoSourceAndroidNative};
PLATFORM_ENUM_END(CoreGPSInfoSource);

typedef struct CoreLatLonPoint {
    double lat;
    double lon;
} CoreLatLonPoint;

typedef struct CoreGPSInfo {
    CoreGPSInfoSource source;
    double timestamp;
    CoreLatLonPoint latLon;
    double horizontalAccuracyM;
    double altitudeM;
    double verticalAccuracyM;
    double bearingDeg;
    double speedMpS;
    double speedAccuracyM;
} CoreGPSInfo;

typedef struct COptionalGPSInfo {
    CoreGPSInfo value;
    bool hasValue;
} COptionalGPSInfo;

#ifdef __cplusplus
}
#endif
