//
// Created by Microzenas on 3/9/23.
//
#include <gtest/gtest.h>
#include <big_number.h>

TEST(BGT, ThrowErrorInInvalidNumber) {

    EXPECT_THROW(BigNumber::BigInt("-00001"),invalid_argument);
    EXPECT_THROW(BigNumber::BigInt("0000"),invalid_argument);
    EXPECT_THROW(BigNumber::BigInt("-"),invalid_argument);
    EXPECT_THROW(BigNumber::BigInt("adf"),invalid_argument);

    EXPECT_NO_THROW(BigNumber::BigInt("-1"));
    EXPECT_NO_THROW(BigNumber::BigInt("-100"));
}

TEST(BGT,InitIntNumber){
    string num = "100000";
    BigNumber::BigInt bignum("100000");
    EXPECT_EQ(num, "100000");
}