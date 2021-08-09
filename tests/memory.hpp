#ifndef MEMORY_H_
#define MEMORY_H_

#include "core/pointer.hpp"
#include <vector>

std::vector<int> int_memory(20, 0);

template <> void memread(int *dst, int offset, int size) {
    if ((offset >= int_memory.size()) || (offset < 0)) {
        throw std::runtime_error("out of bound int_memory");
    }
    *dst = int_memory[offset];
}

template <> void memwrite(const int *src, int offset, int size) {
    if ((offset >= int_memory.size()) || (offset < 0)) {
        throw std::runtime_error("out of bound int_memory");
    }
    int_memory[offset] = *src;
}

template <> void delete_(core_pointer<int> p) { return; }

template <> core_pointer<int> allocate(std::size_t n) {
    core_pointer<int> ret(int_memory.size());
    int_memory.resize(int_memory.size() + n);
    return ret;
}

template <> std::size_t memsizeof<int>() { return 1; }

std::vector<char> char_memory;

template <> void memread(char *dst, int offset, int size) {
    if ((offset >= char_memory.size()) || (offset < 0)) {
        throw std::runtime_error("out of bound memory");
    }
    for (int i = 0; i < size; i++) {
        dst[i] = char_memory[offset + i];
    }
}

template <> void memwrite(const char *src, int offset, int size) {
    if ((offset >= char_memory.size()) || (offset < 0)) {
        throw std::runtime_error("out of bound memory");
    }
    for (int i = 0; i < size; i++) {
        char_memory[offset + i] = src[i];
    }
}

template <> void delete_(core_pointer<char> p) { return; }

template <> core_pointer<char> allocate(std::size_t n) {
    core_pointer<char> ret(char_memory.size());
    char_memory.resize(char_memory.size() + n);
    return ret;
}

template <> std::size_t memsizeof<char>() { return 1; }


#endif // MEMORY_H_
