#pragma once

#include <CoreBridge/platform_bridge_common.h>

#ifdef __cplusplus
#    include <cassert>
#    include <memory>
#    include <utility>
#    include <vector>

extern "C" {
#endif

typedef void Object_Destructor(void const * objRef) NOEXCEPT;
typedef void Object_Copy(void const * objRef) NOEXCEPT;
typedef struct SwiftObjectOwner {
    void const * ref;
    Object_Destructor * destructor;
    Object_Copy * retainer;
} SwiftObjectOwner;

void core_TestSwiftObjectOwner(SwiftObjectOwner objectOwner) NOEXCEPT;

typedef uint8_t * STDVectorInterop_DataGetter(void * vector) NOEXCEPT;
typedef size_t STDVectorInterop_SizeInBytesGetter(void const * vector) NOEXCEPT;

typedef struct STDVectorInterop {
    void * vector;
    STDVectorInterop_DataGetter * dataGetter;
    STDVectorInterop_SizeInBytesGetter * sizeInBytesGetter;
    Object_Destructor * destructor;
} STDVectorInterop;

typedef struct STDVectorViewInterop {
    void const * data;
    size_t size;
} STDVectorViewInterop;

STDVectorInterop core_CreateNilVector() NOEXCEPT;
STDVectorInterop core_CreateVectorOfBytes(size_t size) NOEXCEPT;
STDVectorInterop core_CreateVectorOfDoubles(size_t size) NOEXCEPT;

// Test functions
STDVectorInterop core_CreateTestVector() NOEXCEPT;
STDVectorInterop core_CreateTestVectorFromView(STDVectorViewInterop view) NOEXCEPT;

void platform_interopExample(STDVectorInterop vector) NOEXCEPT;
STDVectorInterop platform_fillNewVector() NOEXCEPT;
// Test functions end
#ifdef __cplusplus
}  // extern "C"

namespace corendk {
class SwiftObjectRef {
public:
    SwiftObjectRef()
        : m_owner{nullptr, nullptr, nullptr} {}
    SwiftObjectRef(SwiftObjectOwner const & cOwner)
        : m_owner(cOwner) {}
    SwiftObjectRef(SwiftObjectRef const & other)
        : m_owner(other.m_owner) {
        m_owner.retainer(m_owner.ref);
    }
    SwiftObjectRef & operator=(SwiftObjectRef const & other) {
        SwiftObjectRef temp = other;
        std::swap(*this, temp);
        return *this;
    }
    SwiftObjectRef(SwiftObjectRef && other) noexcept
        : m_owner{std::exchange(other.m_owner.ref, nullptr),
                  std::exchange(other.m_owner.destructor, nullptr),
                  std::exchange(other.m_owner.retainer, nullptr)} {}
    SwiftObjectRef & operator=(SwiftObjectRef && other) noexcept {
        assert(this != &other);
        std::swap(m_owner, other.m_owner);
        return *this;
    }
    ~SwiftObjectRef() {
        if (m_owner.destructor == nullptr)
            return;
        m_owner.destructor(m_owner.ref);
    }

    void const * get() const { return m_owner.ref; }

private:
    SwiftObjectOwner m_owner;
};

STDVectorInterop createVectorFromString(std::string && str);

template<typename T>
std::vector<T> createVectorFromView(STDVectorViewInterop view) {
    auto data = static_cast<T const *>(view.data);
    std::vector<T> vector(data, data + view.size);
    return vector;
}

template<typename T>
STDVectorInterop createVectorFromStdVector(std::vector<T> vector) {
    std::unique_ptr typedVector = std::make_unique<std::vector<T>>(std::move(vector));
    return {typedVector.release(),
            [](void * vector) noexcept -> uint8_t * {
                auto & typedVector = *static_cast<std::vector<T> *>(vector);
                return reinterpret_cast<uint8_t *>(typedVector.data());
            },
            [](void const * vector) noexcept -> size_t {
                auto const & typedVector = *static_cast<std::vector<T> const *>(vector);
                static constexpr auto tSize = sizeof(T);
                return typedVector.size() * tSize;
            },
            [](void const * vector) noexcept {
                auto const * typedVector = static_cast<std::vector<T> const *>(vector);
                std::unique_ptr<std::vector<T> const> deleter{typedVector};
                deleter.reset();
            }};
}
}  // namespace corendk

#endif
