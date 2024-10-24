#include <CoreBridge/platform_bridge_interop.h>

namespace corendk {
template<typename T>
STDVectorInterop createVectorOfT(size_t size) {
    std::unique_ptr typedVector = std::make_unique<std::vector<T>>(size);
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

STDVectorInterop createVectorFromString(std::string && str) {
    std::unique_ptr typedVector = std::make_unique<std::string>(std::move(str));
    return {typedVector.release(),
            [](void * strData) noexcept -> uint8_t * {
                auto & str = *static_cast<std::string *>(strData);
                return reinterpret_cast<uint8_t *>(str.data());
            },
            [](void const * strData) noexcept -> size_t {
                auto const & str = *static_cast<std::string const *>(strData);
                return str.length();
            },
            [](void const * strData) noexcept {
                auto const * str = static_cast<std::string const *>(strData);
                std::unique_ptr<std::string const> deleter{str};
                deleter.reset();
            }};
}
}  // namespace corendk

extern "C" {
void core_TestSwiftObjectOwner(SwiftObjectOwner objectOwner) noexcept {
    corendk::SwiftObjectRef owner{objectOwner};
    auto moved = std::move(owner);
    corendk::SwiftObjectRef empty;
    corendk::SwiftObjectRef moveAssign;
    moveAssign = std::move(moved);
}

STDVectorInterop core_CreateVectorOfDoubles(size_t size) noexcept {
    return corendk::createVectorOfT<double>(size);
}

STDVectorInterop core_CreateVectorOfBytes(size_t size) noexcept {
    return corendk::createVectorOfT<std::byte>(size);
}
STDVectorInterop core_CreateNilVector() noexcept { return {nullptr, nullptr, nullptr, nullptr}; }

STDVectorInterop core_CreateTestVectorFromView(STDVectorViewInterop view) noexcept {
    auto vector = corendk::createVectorFromView<double>(view);
    return corendk::createVectorFromStdVector<double>(vector);
}

STDVectorInterop core_CreateTestVector() noexcept {
    return corendk::createVectorFromStdVector(std::vector<double>{10.0, 20.1, 30.2});
}
}
