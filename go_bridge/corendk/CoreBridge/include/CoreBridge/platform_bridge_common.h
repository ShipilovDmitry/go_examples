#pragma once

#include <CoreBridge/platform_bridge_types.h>

#ifdef __cplusplus

#    include <string>

extern "C" {
#endif

// string functions

CStringCore CStringCopy(CStringCore value) NOEXCEPT;

void CStringRelease(CStringCore ptr) NOEXCEPT;

typedef struct STDStringRef STDStringRef;

STDStringRef * std_stringCreateEmpty() NOEXCEPT;

STDStringRef * std_stringCreate(CStringCore cString) NOEXCEPT;

void std_stringDestroy(STDStringRef const * string) NOEXCEPT;

CStringCore std_stringData(STDStringRef * string) NOEXCEPT;

size_t std_stringSize(STDStringRef const * string) NOEXCEPT;
#ifdef __cplusplus
}  // extern "C"

// string functions
STDStringRef * std_stringCreate(std::string const & source);

void std_stringCopy(std::string const & source, STDStringRef * destination);

std::string const & std_stringGet(STDStringRef const * string);
#endif
