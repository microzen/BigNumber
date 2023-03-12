//
// Created by Microzenas on 3/11/23.
//
#include <gtest/gtest.h>
#include <BigBits.h>
#include <stdint.h>

TEST(BBITS,Init){
    // uint64_t
    EXPECT_NO_THROW(BB::BigBits());
    EXPECT_NO_THROW(BB::BigBits(ULLONG_MAX));
    EXPECT_NO_THROW(BB::BigBits("123456987123786783654378264587234657823465782346578236457823645"));
    EXPECT_NO_THROW(BB::BigBits("7823645"));
    EXPECT_ANY_THROW(BB::BigBits("-7823645"));
    EXPECT_ANY_THROW(BB::BigBits("a7823645"));
    EXPECT_NO_THROW(BB::BigBits('1'));
    EXPECT_NO_THROW(BB::BigBits('-1'));
    EXPECT_NO_THROW(BB::BigBits('a'));
}

TEST(BBITS, AdditionWithULLong) {
    BB::BigBits ullbig(ULLONG_MAX);
    ullbig = ullbig + 1;
    EXPECT_EQ(ullbig.at(0), 0);
    EXPECT_EQ(ullbig.at(1), 1);

    ullbig = ullbig + ULLONG_MAX;
    ullbig = ullbig + 1;

    EXPECT_EQ(ullbig.at(0), 0);
    EXPECT_EQ(ullbig.at(1), 2);

}

TEST(BBITS, AdditionWithBigBits) {
    BB::BigBits bigulli(ULLONG_MAX);
    BB::BigBits num1(1);

    BB::BigBits result = bigulli + num1;
    bigulli + num1;
    bigulli + num1;
    bigulli + num1;

}

TEST(BBITS, Greater) {
    BB::BigBits a(ULLONG_MAX);
    BB::BigBits b(ULLONG_MAX);

    a = a + 1 + ULLONG_MAX;
    a = a + 1 + ULLONG_MAX;
    a = a + 10;

    b = b + 1 + ULLONG_MAX;
    b = b + 1 + ULLONG_MAX;
    b = b + 1 + ULLONG_MAX;
    b = b + 1 + ULLONG_MAX;
    b = b + 1 ;

    EXPECT_TRUE(b > a) << "b > a should be true.";
}

TEST(BBITS, FromBin) {
    BB::BigBits num;

    // BigBits are "little endian", meaning the least significant bit is stored at the smallest address
    // Keep that in mind when using toBin() and fromBin()
    //
    //                        least significant -> most significant
    vector<unsigned int> bin = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    num.fromBin(bin);
    EXPECT_EQ(num.at(0),131071);

    srand(0);
    bin.resize(0);
    for (unsigned int i=0; i<80; i++)
    {
        bin.push_back(rand()%2);
    }
    num.fromBin(bin);

    EXPECT_EQ(num.size(), 2);
    EXPECT_EQ(num.at(0), 8341798683095734119);
    EXPECT_EQ(num.at(1), 58618);
}