#include <CoreBridge/platform_bridge_common.h>

#include <cstring>
#include <exception>
#include <memory>

extern "C" {

CString CStringCopy(CString value) NOEXCEPT {
    if (value == nullptr) {
        return nullptr;
    }

    try {
        std::unique_ptr<char[]> owner(new char[std::strlen(value) + 1]);  // +1 because of \0
        std::strcpy(owner.get(), value);
        return owner.release();
    } catch (std::exception const & exception) {
        return nullptr;
    }
}

void CStringRelease(CString ptr) NOEXCEPT { std::unique_ptr<char const[]> const deleter(ptr); }

STDStringRef * std_stringCreateEmpty() NOEXCEPT {
    auto string = std::make_unique<std::string>();
    return reinterpret_cast<STDStringRef *>(string.release());
}

STDStringRef * std_stringCreate(CString cString) NOEXCEPT {
    auto string = std::make_unique<std::string>(cString);
    return reinterpret_cast<STDStringRef *>(string.release());
}

void std_stringDestroy(STDStringRef const * string) NOEXCEPT {
    std::unique_ptr<std::string const> const pString(reinterpret_cast<std::string const *>(string));
}

CString std_stringData(STDStringRef * string) NOEXCEPT {
    return reinterpret_cast<std::string *>(string)->data();
}

size_t std_stringSize(STDStringRef const * string) NOEXCEPT {
    return reinterpret_cast<std::string const *>(string)->size();
}

}  // extern "C"

STDStringRef * std_stringCreate(std::string const & source) {
    auto string = std::make_unique<std::string>(source);
    return reinterpret_cast<STDStringRef *>(string.release());
}

void std_stringCopy(std::string const & source, STDStringRef * destination) {
    *reinterpret_cast<std::string *>(destination) = source;
}

std::string const & std_stringGet(STDStringRef const * string) {
    return *reinterpret_cast<std::string const *>(string);
}
