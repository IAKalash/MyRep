#include <gtest/gtest.h>
#include <cstring>  // для strcmp в тестах
#include "string.hpp"

class StringTest : public ::testing::Test {
protected:
    // Setup if needed
};

TEST_F(StringTest, DefaultConstructor_Success) {
    String s;
    EXPECT_EQ(s.size(), 0);
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(strcmp(s.data(), ""), 0);
    EXPECT_EQ(s.countRef(), 1);
}

TEST_F(StringTest, DefaultConstructor_Empty) {
    String s;
    EXPECT_TRUE(s.empty());
}

TEST_F(StringTest, CStrConstructor_Success) {
    String s("hello");
    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(strcmp(s.data(), "hello"), 0);
    EXPECT_EQ(s.countRef(), 1);
}

TEST_F(StringTest, CStrConstructor_Nullptr) {
    String s(nullptr);
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(strcmp(s.data(), ""), 0);
}

TEST_F(StringTest, CStrNConstructor_Success) {
    String s("hello", 3);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(strcmp(s.data(), "hel"), 0);
}

TEST_F(StringTest, CStrNConstructor_ShortSrc) {
    String s("hi", 5);
    EXPECT_EQ(s.size(), 2);
}

TEST_F(StringTest, FillConstructor_Success) {
    String s(4, 'a');
    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(strcmp(s.data(), "aaaa"), 0);
}

TEST_F(StringTest, FillConstructor_Zero) {
    String s(0, 'a');
    EXPECT_EQ(s.size(), 0);
    EXPECT_EQ(strcmp(s.data(), ""), 0);
}

TEST_F(StringTest, CopyConstructor_Success) {
    String s1("hello");
    String s2(s1);
    EXPECT_EQ(s1.countRef(), 2);
    EXPECT_EQ(s2.size(), 5);
    EXPECT_EQ(strcmp(s2.data(), "hello"), 0);
}

TEST_F(StringTest, CopyConstructor_Empty) {
    String s1;
    String s2(s1);
    EXPECT_EQ(s2.size(), 0);
    EXPECT_EQ(s1.countRef(), 2);
}

TEST_F(StringTest, SubstrConstructor_Success) {
    String s1("helloworld");
    String s2(s1, 5, 5);
    EXPECT_EQ(s2.size(), 5);
    EXPECT_EQ(strcmp(s2.data(), "world"), 0);
    EXPECT_EQ(s2.countRef(), 1);
}

TEST_F(StringTest, SubstrConstructor_Throw) {
    String s1("hello");
    EXPECT_THROW(String(s1, 10), std::out_of_range);
}

TEST_F(StringTest, Size_Success) {
    String s("hello");
    EXPECT_EQ(s.size(), 5);
}

TEST_F(StringTest, Size_Empty) {
    String s;
    EXPECT_EQ(s.size(), 0);
}

TEST_F(StringTest, Capacity_Success) {
    String s("hello");
    EXPECT_EQ(s.capacity(), 5);
}

TEST_F(StringTest, Capacity_Reserved) {
    String s;
    s.reserve(10);
    EXPECT_GE(s.capacity(), 10);
}

TEST_F(StringTest, Empty_Success) {
    String s;
    EXPECT_TRUE(s.empty());
}

TEST_F(StringTest, Empty_False) {
    String s("a");
    EXPECT_FALSE(s.empty());
}

TEST_F(StringTest, Data_Success) {
    String s("hello");
    EXPECT_EQ(strcmp(s.data(), "hello"), 0);
}

TEST_F(StringTest, Data_Empty) {
    String s;
    EXPECT_EQ(strcmp(s.data(), ""), 0);
}

TEST_F(StringTest, CountRef_Success) {
    String s("hello");
    EXPECT_EQ(s.countRef(), 1);
}

TEST_F(StringTest, CountRef_Shared) {
    String s1("hello");
    String s2 = s1;
    EXPECT_EQ(s1.countRef(), 2);
}

TEST_F(StringTest, At_Success) {
    String s("hello");
    EXPECT_EQ(s.at(0), 'h');
    s.at(0) = 'H';
    EXPECT_EQ(s.at(0), 'H');
}

TEST_F(StringTest, At_Throw) {
    String s("hello");
    EXPECT_THROW(s.at(5), std::out_of_range);
    const String cs("hello");
    EXPECT_THROW(cs.at(6), std::out_of_range);
    EXPECT_EQ(cs.at(5), '\0');
}

TEST_F(StringTest, OperatorBracket_Success) {
    String s("hello");
    EXPECT_EQ(s[0], 'h');
    s[0] = 'H';
    EXPECT_EQ(s[0], 'H');
}

TEST_F(StringTest, OperatorBracket_End) {
    const String s("hello");
    EXPECT_EQ(s[5], '\0');
}

TEST_F(StringTest, Back_Success) {
    String s("hello");
    EXPECT_EQ(s.back(), 'o');
    s.back() = 'O';
    EXPECT_EQ(s.back(), 'O');
}

TEST_F(StringTest, Back_Const) {
    const String s("hello");
    EXPECT_EQ(s.back(), 'o');
}

TEST_F(StringTest, Front_Success) {
    String s("hello");
    EXPECT_EQ(s.front(), 'h');
    s.front() = 'H';
    EXPECT_EQ(s.front(), 'H');
}

TEST_F(StringTest, Front_Const) {
    const String s("hello");
    EXPECT_EQ(s.front(), 'h');
}

TEST_F(StringTest, Reserve_Success) {
    String s("hello");
    size_t old_cap = s.capacity();
    s.reserve(10);
    EXPECT_GE(s.capacity(), 10);
    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(strcmp(s.data(), "hello"), 0);
}

TEST_F(StringTest, Reserve_NoChange) {
    String s("hello");
    size_t old_cap = s.capacity();
    s.reserve(3);
    EXPECT_EQ(s.capacity(), old_cap);
}

TEST_F(StringTest, Clear_Success) {
    String s("hello");
    s.clear();
    EXPECT_EQ(s.size(), 0);
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(strcmp(s.data(), ""), 0);
}

TEST_F(StringTest, Clear_Empty) {
    String s;
    s.clear();
    EXPECT_EQ(s.size(), 0);
}

TEST_F(StringTest, OperatorPlusEqual_String_Success) {
    String s("hello");
    String add(" world");
    s += add;
    EXPECT_EQ(strcmp(s.data(), "hello world"), 0);
    EXPECT_EQ(s.size(), 11);
}

TEST_F(StringTest, OperatorPlusEqual_String_CopyOnWrite) {
    String s1("hello");
    String s2 = s1;
    s2 += " world";
    EXPECT_EQ(strcmp(s2.data(), "hello world"), 0);
    EXPECT_EQ(strcmp(s1.data(), "hello"), 0);
    EXPECT_EQ(s1.countRef(), 1);
    EXPECT_EQ(s2.countRef(), 1);
}

TEST_F(StringTest, OperatorPlusEqual_CStr_Success) {
    String s("hello");
    s += " world";
    EXPECT_EQ(strcmp(s.data(), "hello world"), 0);
}

TEST_F(StringTest, OperatorPlusEqual_Char_Success) {
    String s("hello");
    s += '!';
    EXPECT_EQ(strcmp(s.data(), "hello!"), 0);
}

TEST_F(StringTest, OperatorAssign_String_Success) {
    String s1("hello");
    String s2;
    s2 = s1;
    EXPECT_EQ(s2.size(), 5);
    EXPECT_EQ(strcmp(s2.data(), "hello"), 0);
    EXPECT_EQ(s1.countRef(), 2);
}

TEST_F(StringTest, OperatorAssign_Self) {
    String s("hello");
    s = s;
    EXPECT_EQ(strcmp(s.data(), "hello"), 0);
}

TEST_F(StringTest, OperatorAssign_CStr_Success) {
    String s;
    s = "hello";
    EXPECT_EQ(strcmp(s.data(), "hello"), 0);
    EXPECT_EQ(s.countRef(), 1);
}

TEST_F(StringTest, Insert_String_Success) {
    String s("hello");
    s.insert(5, String(" world"));
    EXPECT_EQ(strcmp(s.data(), "hello world"), 0);
}

TEST_F(StringTest, Insert_String_Throw) {
    String s("hello");
    EXPECT_THROW(s.insert(6, String("a")), std::out_of_range);
}

TEST_F(StringTest, Insert_CStr_Success) {
    String s("hello");
    s.insert(5, " world");
    EXPECT_EQ(strcmp(s.data(), "hello world"), 0);
}

TEST_F(StringTest, Insert_Fill_Success) {
    String s("hello");
    s.insert(0, 3, 'a');
    EXPECT_EQ(strcmp(s.data(), "aaahello"), 0);
}

TEST_F(StringTest, Erase_Success) {
    String s("hello world");
    s.erase(5, 6);
    EXPECT_EQ(strcmp(s.data(), "hello"), 0);
}

TEST_F(StringTest, Erase_Throw) {
    String s("hello");
    EXPECT_THROW(s.erase(6), std::out_of_range);
}

TEST_F(StringTest, Replace_String_Success) {
    String s("hello world");
    s.replace(6, 5, String("everyone"));
    EXPECT_EQ(strcmp(s.data(), "hello everyone"), 0);
}

TEST_F(StringTest, Replace_Throw) {
    String s("hello");
    EXPECT_THROW(s.replace(6, 1, "a"), std::out_of_range);
}

TEST_F(StringTest, Replace_CStr_Success) {
    String s("hello");
    s.replace(0, 5, "hi");
    EXPECT_EQ(strcmp(s.data(), "hi"), 0);
}

TEST_F(StringTest, Replace_Fill_Success) {
    String s("hello");
    s.replace(1, 3, 2, 'x');
    EXPECT_EQ(strcmp(s.data(), "hxxo"), 0);
}

TEST_F(StringTest, Swap_Success) {
    String s1("hello");
    String s2("world");
    s1.swap(s2);
    EXPECT_EQ(strcmp(s1.data(), "world"), 0);
    EXPECT_EQ(strcmp(s2.data(), "hello"), 0);
}

TEST_F(StringTest, Swap_Self) {
    String s("hello");
    s.swap(s);
    EXPECT_EQ(strcmp(s.data(), "hello"), 0);
}

TEST_F(StringTest, Find_String_Success) {
    String s("hello world");
    EXPECT_EQ(s.find(String("world")), 6);
}

TEST_F(StringTest, Find_String_NotFound) {
    String s("hello");
    EXPECT_EQ(s.find(String("world")), String::npos);
}

TEST_F(StringTest, Find_CStr_Success) {
    String s("hello world");
    EXPECT_EQ(s.find("world"), 6);
}

TEST_F(StringTest, Find_Char_Success) {
    String s("hello");
    EXPECT_EQ(s.find('l', 2), 2);
}

TEST_F(StringTest, Substr_Success) {
    String s("hello world");
    String sub = s.substr(6, 5);
    EXPECT_EQ(strcmp(sub.data(), "world"), 0);
}

TEST_F(StringTest, Substr_Throw) {
    String s("hello");
    EXPECT_THROW(s.substr(6), std::out_of_range);
}

TEST_F(StringTest, Compare_String_Success) {
    String s1("hello");
    String s2("hello");
    EXPECT_EQ(s1.compare(s2), 0);
    String s3("hellp");
    EXPECT_LT(s1.compare(s3), 0);
}

TEST_F(StringTest, Compare_CStr_Success) {
    String s("hello");
    EXPECT_EQ(s.compare("hello"), 0);
    EXPECT_GT(s.compare("hell"), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}