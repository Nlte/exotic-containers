#ifndef SERIALIZER_H_
#define SERIALIZER_H_

#include "core/pointer.hpp"
#include <string>
#include <type_traits>

template <typename T, typename trivially_copyable = void> struct serializer {};

template <typename T>
struct serializer<
    T, typename std::enable_if<std::is_trivially_copyable<T>::value>::type> {
    T serialize(const T &value) { return value; }

    T deserialize(const T &value) { return value; }
};

template <> struct serializer<std::string> {
    serial_core_pointer<char> serialize(const std::string &str) {
        serial_core_pointer<char> ptr(str.length());
        for (std::size_t i = 0; i < str.length(); i++) {
            ptr[i] = str[i];
        }
        return ptr;
    }

    std::string deserialize(const serial_core_pointer<char> &ptr) {
        return std::string(ptr.data(), ptr.size());
    }
};

#endif // SERIALIZER_H_
