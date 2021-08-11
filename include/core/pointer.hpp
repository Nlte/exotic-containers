#ifndef CORE_POINTER_H_
#define CORE_POINTER_H_

/*
 * Adapted from original blog post:
 * https://people.eecs.berkeley.edu/~brock/blog/remote_pointers.php
 * */

#include <cstddef>
#include <type_traits>

#include "core/log.hpp"


template <typename T> struct core_pointer;

template <typename T> struct core_reference;

template <typename T> void memread(T *dst, int offset, int size);
template <typename T> void memwrite(const T *src, int offset, int size);

template <typename T> extern void delete_(core_pointer<T>);
template <typename T> extern core_pointer<T> allocate(std::size_t n);

template <typename T> std::size_t memsizeof() { return sizeof(T); }

template <typename T> struct core_pointer {

    std::size_t offset_;

    core_pointer() { offset_ = -1; }

    core_pointer(std::size_t offset) : offset_(offset) { }

    core_pointer<T> operator+(std::ptrdiff_t diff) {
        std::size_t new_offset = offset_ + memsizeof<T>() * diff;
        return core_pointer<T>{new_offset};
    }

    core_pointer<T> operator+=(std::ptrdiff_t diff) {
        offset_ = offset_ + memsizeof<T>() * diff;
        return *this;
    }

    core_pointer<T> operator++() {
        offset_ = offset_ + memsizeof<T>() * 1;
        return *this;
    }

    core_pointer<T> operator++(int) {
        core_pointer<T> old = *this;
        offset_ = offset_ + memsizeof<T>() * 1;
        return old;
    }

    core_pointer<T> operator-(std::ptrdiff_t diff) {
        std::size_t new_offset = offset_ - memsizeof<T>() * diff;
        return core_pointer<T>{new_offset};
    }

    core_pointer<T> operator-=(std::ptrdiff_t diff) {
        offset_ = offset_ - memsizeof<T>() * diff;
        return *this;
    }

    core_pointer<T> operator--() {
        offset_ = offset_ - memsizeof<T>() * 1;
        return *this;
    }

    core_pointer<T> operator--(int) {
        core_pointer<T> old = *this;
        offset_ = offset_ - memsizeof<T>() * 1;
        return old;
    }

    bool operator==(std::nullptr_t) const { return offset_ == -1; }

    bool operator!=(std::nullptr_t) const { return offset_ != -1; }

    bool operator==(const core_pointer &other) const {
        return offset_ == other.offset_;
    }

    bool operator!=(const core_pointer &other) const {
        return !(*this == other);
    }

    bool operator>(const core_pointer<T> other) {
        return offset_ > other.offset_;
    }

    bool operator>=(const core_pointer<T> other) {
        return offset_ >= other.offset_;
    }

    bool operator<(const core_pointer<T> other) {
        return offset_ < other.offset_;
    }

    bool operator<=(const core_pointer<T> other) {
        return offset_ <= other.offset_;
    }

    core_reference<T> operator*() {
        if (*this == nullptr) {
            throw std::runtime_error("nullptr derefence");
        }
        return core_reference<T>{*this};
    }

    core_reference<T> operator[](std::ptrdiff_t idx) {
        if (*this == nullptr) {
            throw std::runtime_error("nullptr derefence");
        }
        return core_reference<T>{*this + idx};
    }
};

template <typename T> struct core_reference {

    core_pointer<T> ptr_;

    core_reference(core_pointer<T> ptr): ptr_(ptr) { }

    operator T() const { return rget(ptr_); }

    core_reference &operator=(const T &value) {
        rput(ptr_, value);
        return *this;
    }
};

template <typename T> T rget(const core_pointer<T> src) {
    T rv;
    memread(&rv, src.offset_, memsizeof<T>());
    return rv;
}

template <typename T>
void rget(const core_pointer<T> src, T *dst, std::size_t len) {
    memread(dst, src.offset_, memsizeof<T>() * len);
}

template <typename T> void rput(const core_pointer<T> dst, const T &src) {
    memwrite(&src, dst.offset_, memsizeof<T>());
}

template <typename T>
void rput(const core_pointer<T> dst, const T *src, std::size_t len) {
    memwrite(src, dst.offset_, memsizeof<T>() * len);
}

template <typename T> class serial_core_pointer {

  public:
    using type = T;

    serial_core_pointer(std::size_t size) : len_(size), data_(new T[size]) {}
    serial_core_pointer(const serial_core_pointer &) = delete;
    serial_core_pointer(serial_core_pointer &&) = default;

    ~serial_core_pointer() { delete[] data_; }

    T &operator[](std::size_t idx) { return data_[idx]; }

    T *data() const { return data_; }

    std::size_t size() const { return len_; }

  private:
    T *data_;
    std::size_t len_;
};

template <typename T> struct is_serial_core_pointer : std::false_type {};

template <typename T>
struct is_serial_core_pointer<serial_core_pointer<T>> : std::true_type {};

#endif // CORE_POINTER_H_
