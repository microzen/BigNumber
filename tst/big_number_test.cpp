//
// Created by Microzenas on 3/9/23.
//
#include <gtest/gtest.h>
#include <big_number.h>

TEST(BGT, Init) {
    string num = "100000";
    BigNumber::BigInt bignum("100000");
    EXPECT_EQ(num, "100000");
}