#include <gtest/gtest.h>
#include <string>

#include "core/pointer.hpp"
#include "core/serializer.hpp"

TEST(TestSerializer, TrivialTypes) {
    int i = 3;
    int ser = serializer<int>{}.serialize(i);
    int deser = serializer<int>{}.deserialize(ser);
    EXPECT_EQ(deser, i);
}

TEST(TestSerializer, String) {
    std::string s = "abcd";
    serial_core_pointer<char> ptr = serializer<std::string>{}.serialize(s);
    std::string deser = serializer<std::string>{}.deserialize(ptr);
    EXPECT_EQ(deser, "abcd");
}
