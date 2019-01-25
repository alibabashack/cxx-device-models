#pragma once
#include <cstdint>

namespace hwmodel {

template <class T> class Dev_ptr {
    const intptr_t baseAddress;
public:

    constexpr Dev_ptr(intptr_t baseAddress) :
    baseAddress(baseAddress) {
    }

    operator T*() const {
        return reinterpret_cast<T*> (baseAddress);
    }

    T* operator->() const {
        return operator T * ();
    }
};

template <class T> class Reg_ptr {
    const intptr_t baseAddress;
public:

    constexpr Reg_ptr(intptr_t baseAddress) :
    baseAddress(baseAddress) {
    }

    operator volatile T*() const {
        return reinterpret_cast<volatile T*> (baseAddress);
    }

    volatile T* operator->() const {
        return operator volatile T * ();
    }
};

}
