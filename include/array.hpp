#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdexcept>
#include "core/pointer.hpp"
#include "core/log.hpp"

template <typename T, std::size_t N> struct array {
    typedef T value_type;
    typedef core_pointer<T> pointer;
    typedef const core_pointer<T> const_pointer;
    typedef core_reference<T> reference;
    typedef const core_reference<T> const_reference;
    typedef core_pointer<T> iterator;
    typedef const core_pointer<T> const_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    pointer start_;
    size_type size_ = N;

    array() { start_ = allocate<value_type>(size_); }

    /* Iterators */
    iterator begin(){ return iterator(start_); }

    const_iterator begin() const { return const_iterator(start_); }

    iterator end() { return iterator(start_ + size_); }

    const_iterator end() const { return const_iterator(start_ + size_); }

    /* Capacity */
    constexpr size_type size() const { return size_; }

    constexpr size_type max_size() const { return size_; }

    constexpr bool empty() const { return size() == 0; }

    /* Element access */
    reference operator[](size_type idx) {
        if (start_ == nullptr) {
            throw std::runtime_error("start_ is nullptr");
        }
        return reference(pointer(start_ + idx));
    }

    const_reference operator[](size_type idx) const {
        if (start_ == nullptr) {
            throw std::runtime_error("start_ is nullptr");
        }
        return reference(pointer(start_ + idx));
    }

    reference at(size_type idx) {
        if (idx >= size_)
            std::out_of_range("array::at");
        return reference(pointer(start_ + idx));
    }

    const_reference at(size_type idx) const {
        if (idx >= size_)
            std::out_of_range("array::at");
        return const_reference(pointer(start_ + idx));
    }

    reference front() { return reference(pointer(start_)); }

    const_reference front() const { return const_reference(pointer(start_)); }

    reference back() { return size_ ? reference(end() - 1) : reference(end()); }

    const_reference back() const { return size_ ? reference(end() - 1) : reference(end()); }

};

#endif // ARRAY_H_
