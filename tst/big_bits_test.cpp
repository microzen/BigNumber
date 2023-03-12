//
// Created by Microzenas on 3/11/23.
//
#include <gtest/gtest.h>
#include <BigBits.h>
#include <stdint.h>

TEST(BBITS,Init){
    EXPECT_NO_THROW(BB::BigBits());
//    unit64_t
    EXPECT_NO_THROW(BB::BigBits(ULLONG_MAX));
    EXPECT_THROW(BB::BigBits("123456987123786783654378264587234657823465782346578236457823645"), out_of_range);
    EXPECT_NO_THROW(BB::BigBits("7823645"));
    EXPECT_NO_THROW(BB::BigBits("-7823645"));
    EXPECT_ANY_THROW(BB::BigBits("a7823645"));
    EXPECT_NO_THROW(BB::BigBits('1'));
    EXPECT_NO_THROW(BB::BigBits('-1'));
    EXPECT_ANY_THROW(BB::BigBits('a'));
}

TEST(BBITS, AdditionWithULLong) {
    BB::BigBits ullbig(ULLONG_MAX);
    ullbig = ullbig + 1;
    EXPECT_EQ(ullbig.at(0),ULLONG_MAX);
    EXPECT_EQ(ullbig.at(1),1);

    ullbig = ullbig + 1;
    EXPECT_EQ(ullbig.at(0),ULLONG_MAX);
    EXPECT_EQ(ullbig.at(1),2);

    vector<::uint64_t> s = ullbig.getVect();

}

TEST(BBITS,AdditionWithBigBits){
    BB::BigBits bigulli(ULLONG_MAX);
    BB::BigBits num1(1);

    BB::BigBits result = bigulli + num1;


}