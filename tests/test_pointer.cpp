#include <array>
#include <gtest/gtest.h>

#include "core/pointer.hpp"
#include "memory.hpp"

TEST(TestCore_Pointer, WriteInt_Memory) {
    core_pointer<int> ptr(0);
    ptr[5] = 10;
    int buff;
    memread(&buff, 5, 0);
    EXPECT_EQ(buff, 10);
}

TEST(TestCore_Pointer, ReadInt_Memory) {
    int_memory[1] = 123;
    core_pointer<int> ptr(1);
    EXPECT_EQ(*ptr, 123);
}

TEST(TestCore_Pointer, Addition) {
    int_memory[0] = 123;
    int_memory[1] = 456;
    core_pointer<int> ptr(0);
    EXPECT_EQ(*ptr, 123);
    ptr = ptr + 1;
    EXPECT_EQ(*ptr, 456);
}

TEST(TestCore_Pointer, AdditionSelf) {
    int_memory[0] = 123;
    int_memory[1] = 456;
    core_pointer<int> ptr(0);
    EXPECT_EQ(*ptr, 123);
    ptr += 1;
    EXPECT_EQ(*ptr, 456);
}

TEST(TestCore_Pointer, PrefixIncrement) {
    int_memory[0] = 123;
    int_memory[1] = 456;
    core_pointer<int> ptr(0);
    EXPECT_EQ(*ptr, 123);
    core_pointer<int> newptr = ++ptr;
    EXPECT_EQ(*ptr, 456);
    EXPECT_EQ(*newptr, 456);
}

TEST(TestCore_Pointer, PostfixIncrement) {
    int_memory[0] = 123;
    int_memory[1] = 456;
    core_pointer<int> ptr(0);
    EXPECT_EQ(*ptr, 123);
    core_pointer<int> newptr = ptr++;
    EXPECT_EQ(*ptr, 456);
    EXPECT_EQ(*newptr, 123);
}

TEST(TestCore_Pointer, Subtraction) {
    int_memory[0] = 123;
    int_memory[1] = 456;
    core_pointer<int> ptr(1);
    EXPECT_EQ(*ptr, 456);
    ptr = ptr - 1;
    EXPECT_EQ(*ptr, 123);
}

TEST(TestCore_Pointer, SubtractionSelf) {
    int_memory[0] = 123;
    int_memory[1] = 456;
    core_pointer<int> ptr(1);
    EXPECT_EQ(*ptr, 456);
    ptr -= 1;
    EXPECT_EQ(*ptr, 123);
}

TEST(TestCore_Pointer, PrefixDecrement) {
    int_memory[0] = 123;
    int_memory[1] = 456;
    core_pointer<int> ptr(1);
    EXPECT_EQ(*ptr, 456);
    core_pointer<int> newptr = --ptr;
    EXPECT_EQ(*newptr, 123);
    EXPECT_EQ(*ptr, 123);
}

TEST(TestCore_Pointer, PostfixDecrement) {
    int_memory[0] = 123;
    int_memory[1] = 456;
    core_pointer<int> ptr(1);
    EXPECT_EQ(*ptr, 456);
    core_pointer<int> newptr = ptr--;
    EXPECT_EQ(*ptr, 123);
    EXPECT_EQ(*newptr, 456);
}

TEST(TestCore_Pointer, Equal) {
    core_pointer<int> ptr(1);
    core_pointer<int> ptr2(1);
    EXPECT_EQ(ptr == ptr2, true);
}

TEST(TestCore_Pointer, Inequal) {
    core_pointer<int> ptr1(1);
    core_pointer<int> ptr2(2);
    EXPECT_EQ(ptr1 != ptr2, true);
}

TEST(TestCore_Pointer, Superior) {
    core_pointer<int> ptr1(1);
    core_pointer<int> ptr2(2);
    EXPECT_EQ(ptr2 > ptr1, true);
    EXPECT_EQ(ptr2 < ptr1, false);
}

TEST(TestCore_Pointer, SuperiorOrEqual) {
    core_pointer<int> ptr(0);
    core_pointer<int> ptr_copy(0);
    core_pointer<int> ptr1(1);
    EXPECT_EQ(ptr >= ptr_copy, true);
    EXPECT_EQ(ptr1 >= ptr, true);
    EXPECT_EQ(ptr >= ptr1, false);
}

TEST(TestCore_Pointer, Inferior) {
    core_pointer<int> ptr(0);
    core_pointer<int> ptr1(1);
    EXPECT_EQ(ptr < ptr1, true);
    EXPECT_EQ(ptr > ptr1, false);
}

TEST(TestCore_Pointer, InferiorOrEqual) {
    core_pointer<int> ptr(0);
    core_pointer<int> ptr_copy(0);
    core_pointer<int> ptr1(1);
    EXPECT_EQ(ptr <= ptr_copy, true);
    EXPECT_EQ(ptr <= ptr1, true);
    EXPECT_EQ(ptr >= ptr1, false);
}

TEST(TestSerialCore_Pointer, Instantiation) {
    serial_core_pointer<int> ptr(5);
    EXPECT_EQ(ptr.size(), 5);
}

TEST(TestSerialCore_Pointer, RandomAccessOperator) {
    serial_core_pointer<int> ptr(5);
    ptr[0] = 0;
    ptr[1] = 1;
    ptr[2] = 2;
    EXPECT_EQ(ptr.data()[0], 0);
    EXPECT_EQ(ptr.data()[1], 1);
    EXPECT_EQ(ptr.data()[2], 2);
}
