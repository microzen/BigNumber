//
// Created by Microzenas on 3/11/23.
//
#include <gtest/gtest.h>
#include <BigBits.h>
#include <bitset>
#include <cstdint>

TEST(BBITS, Constructors){
    // Default
    EXPECT_NO_THROW(BB::BigBits());

    // BigBits
    BB::BigBits bb = 12;
    EXPECT_NO_THROW(BB::BigBits num(bb));
    BB::BigBits num(bb);
    EXPECT_EQ(num.at(0), 12);

    // uint64_t
    EXPECT_NO_THROW(BB::BigBits(ULLONG_MAX));
    EXPECT_NO_THROW(BB::BigBits(1234567));
    EXPECT_NO_THROW(BB::BigBits(323));
    EXPECT_EQ(BB::BigBits(323).at(0), 323);

    // string
    EXPECT_NO_THROW(BB::BigBits(string("123")));
    EXPECT_ANY_THROW(BB::BigBits(string("-12")));
    EXPECT_ANY_THROW(BB::BigBits(string("64abc")));
    EXPECT_NO_THROW(BB::BigBits(string("123456987123786783654378264587234657823465782346578236457823645")));
    EXPECT_EQ(BB::BigBits(string("323")).at(0), 323);

    /*
    BB::BigBits bigNum = string("90445398191276609683561357299864965001643765149");
    EXPECT_EQ(bigNum.size(), 3);
    EXPECT_EQ(bigNum.at(0),11072005533870792623);
    EXPECT_EQ(bigNum.at(1),7818575067201490371);
    EXPECT_EQ(bigNum.at(2),12047803422806778902);
    */
}


TEST(BBITS, FromBin) {
    BB::BigBits num;

    // BigBits are "little endian", meaning the least significant bit is stored at the smallest address
    // Keep that in mind when using toBin() and fromBin()
    //
    //                        least significant -> most significant

    vector<unsigned int> bin1 = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    num.fromBin(bin1);
    EXPECT_EQ(num.at(0),131071);

    vector<unsigned int> bin2 = {0,0,0,0,0,0,0,1};
    num.fromBin(bin2);
    EXPECT_EQ(num.at(0),128);

    //                          0|    4|      8|     12|     16|     20|     24|     28|     32|     36|     40|     44|     48|     52|     56|     60|     64|     68|
    vector<unsigned int> bin3 = {1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1};
    num.fromBin(bin3);
    EXPECT_EQ(num.size(), 2);
    EXPECT_EQ(num.at(0),18446744073709551607);
    EXPECT_EQ(num.at(1),11);
}


TEST(BBITS, leftShiftOut) {
    BB::BigBits num = 17646744053709551612;
    string binaryNum = "1111010011100101110101000011100001101011100110000011011111111100";

    for (unsigned int i=0; i<64; i++)
    {
        bool thisBit = binaryNum.at(i) == '1';
        EXPECT_EQ(num.leftShiftOut(63 - i), thisBit);
    }
}


TEST(BBITS, Equal) {
    BB::BigBits a(ULLONG_MAX);
    BB::BigBits b(ULLONG_MAX);
    EXPECT_TRUE(a == b);
    a++;
    EXPECT_FALSE(a == b);
}


TEST(BBITS, NotEqual) {
    BB::BigBits a(ULLONG_MAX);
    BB::BigBits b(ULLONG_MAX);
    EXPECT_FALSE(a != b);
    a++;
    EXPECT_TRUE(a != b);
}


TEST(BBITS, GreaterThan) {
    BB::BigBits a(ULLONG_MAX - 2);
    BB::BigBits b(ULLONG_MAX - 1);

    EXPECT_FALSE(a > b);
    a++;
    EXPECT_FALSE(a > b);
    a++;
    EXPECT_TRUE(a > b);
    a++; b++;
    EXPECT_TRUE(a > b);
}


TEST(BBITS, GreaterThanOrEqual) {
    BB::BigBits a(ULLONG_MAX - 2);
    BB::BigBits b(ULLONG_MAX - 1);

    EXPECT_FALSE(a >= b);
    a++;
    EXPECT_TRUE(a >= b);
    a++;
    EXPECT_TRUE(a >= b);
    a++; b++;
    EXPECT_TRUE(a >= b);
}


TEST(BBITS, LessThan) {
    BB::BigBits a(ULLONG_MAX - 2);
    BB::BigBits b(ULLONG_MAX - 1);

    EXPECT_TRUE(a < b);
    a++;
    EXPECT_FALSE(a < b);
    b++;
    EXPECT_TRUE(a < b);
    a++; b++;
    EXPECT_TRUE(a < b);
}


TEST(BBITS, LessThanOrEqual) {
    BB::BigBits a(ULLONG_MAX - 2);
    BB::BigBits b(ULLONG_MAX - 1);

    EXPECT_TRUE(a <= b);
    a++;
    EXPECT_TRUE(a <= b);
    b++;
    EXPECT_TRUE(a <= b);
    a++; b++;
    EXPECT_TRUE(a <= b);
}


TEST(BBITS, PreIncrement) {
    BB::BigBits num = 123;
    ++num;
    EXPECT_EQ(num.at(0), 124);
    num = ULLONG_MAX;
    ++num;
    EXPECT_EQ(num.at(0), 0);
    EXPECT_EQ(num.at(1), 1);
}


TEST(BBITS, PostIncrement) {
    BB::BigBits num = 123;
    num++;
    EXPECT_EQ(num.at(0), 124);
    num = ULLONG_MAX;
    num++;
    EXPECT_EQ(num.at(0), 0);
    EXPECT_EQ(num.at(1), 1);
}


TEST(BBITS, Addition) {
    // BigBits + int
    BB::BigBits ullMax(ULLONG_MAX);
    ullMax = ullMax + 1;
    EXPECT_EQ(ullMax.at(0), 0);
    EXPECT_EQ(ullMax.at(1), 1);

    ullMax = ullMax + ULLONG_MAX;
    ullMax = ullMax + 1;

    EXPECT_EQ(ullMax.at(0), 0);
    EXPECT_EQ(ullMax.at(1), 2);

    // BigBits + BigBits
    ullMax = ULLONG_MAX;
    BB::BigBits num1(1);
    BB::BigBits result = ullMax + num1;
    ullMax + num1;
    ullMax + num1;
    ullMax + num1;
    BB::BigBits num2 = 9007199254740983;
    BB::BigBits num3 = 9007199254740992;
    num2 += num3;
    EXPECT_EQ(num2.at(0), 18014398509481975);
}


TEST(BBITS, Multiplication) {
    BB::BigBits num1 = 12;
    BB::BigBits num2 = 10;
    num1 *= num2;
    EXPECT_EQ(num1.at(0), 120);

    num1 = 2;
    num2 = 18446744073709551615;
    BB::BigBits num3 = num2 + num2;
    EXPECT_EQ(num3.at(0), 18446744073709551614);
    EXPECT_EQ(num3.at(1), 1);
    num1 *= num2;
    EXPECT_EQ(num1.at(0), 18446744073709551614);
    EXPECT_EQ(num1.at(1), 1);
}


TEST(BBITS, Power) {
    BB::BigBits num1 = 4; // base
    BB::BigBits num2 = 0; // power
    num1 ^= num2;
    EXPECT_EQ(num1.at(0), 1);

    num1 = 3;
    num2 = 9;
    num1 = num1 ^ num2;
    EXPECT_EQ(num1.at(0), 19683);

    num1 = 2;
    num2 = 64;
    num1 = num1 ^ num2;
    EXPECT_EQ(num1.at(0), 0);
    EXPECT_EQ(num1.at(1), 1);
}


// Nibble -----------------------------------


TEST(NIBBLE, Constructors) {
    EXPECT_NO_THROW(BB::Nibble());
    EXPECT_NO_THROW(BB::Nibble(0));
    EXPECT_NO_THROW(BB::Nibble(3));
    EXPECT_NO_THROW(BB::Nibble(12));
    EXPECT_ANY_THROW(BB::Nibble(-4));
    EXPECT_ANY_THROW(BB::Nibble(19));
}


TEST(NIBBLE, Shift) {
    BB::Nibble nibble(0); // 0000
    bool shiftOut;

    shiftOut = nibble.shift(true); // 1000

    for (unsigned int k=0; k<4; k++)
    {
        shiftOut = nibble.shift(false); // 0100 -> 0010 -> 0001 -> 0000

        // Convert nibble to string of binary
        char nibbleChar = nibble.toChar();
        string bin;
        for (unsigned int i = 0; i < 4; i++) {
            bin += to_string(nibbleChar % 2);
            nibbleChar /= 2;
        }

        // Test binary and shift out values
        if (k==0)
        {
            EXPECT_EQ(bin, "0100");
            EXPECT_EQ(shiftOut, false);
        }
        else if (k==1)
        {
            EXPECT_EQ(bin, "0010");
            EXPECT_EQ(shiftOut, false);
        }
        else if (k==2)
        {
            EXPECT_EQ(bin, "0001");
            EXPECT_EQ(shiftOut, false);
        }
        else if (k==3)
        {
            EXPECT_EQ(bin, "0000");
            EXPECT_EQ(shiftOut, true);
        }
    }
}


TEST(NIBBLE, ToChar) {
    EXPECT_EQ(BB::Nibble().toChar(), '0');
    EXPECT_EQ(BB::Nibble(1).toChar(), '1');
    EXPECT_EQ(BB::Nibble(2).toChar(), '2');
    EXPECT_EQ(BB::Nibble(3).toChar(), '3');
    EXPECT_EQ(BB::Nibble(4).toChar(), '4');
    EXPECT_EQ(BB::Nibble(5).toChar(), '5');
    EXPECT_EQ(BB::Nibble(6).toChar(), '6');
    EXPECT_EQ(BB::Nibble(7).toChar(), '7');
    EXPECT_EQ(BB::Nibble(8).toChar(), '8');
    EXPECT_EQ(BB::Nibble(9).toChar(), '9');
}


TEST(NIBBLE, DirectAssignment) {
    EXPECT_NO_THROW(BB::Nibble num = 0);
    EXPECT_NO_THROW(BB::Nibble num = 3);
    EXPECT_NO_THROW(BB::Nibble num = 15);
    EXPECT_ANY_THROW(BB::Nibble num = -43);
    EXPECT_ANY_THROW(BB::Nibble num = 43);

    BB::Nibble num;
    num = 1;
    EXPECT_EQ(num.toChar(), '1');
    num = 7;
    EXPECT_EQ(num.toChar(), '7');
}


TEST(NIBBLE, Addition) {
    BB::Nibble num = 3;
    num += 1;
    EXPECT_EQ(num.toChar(), '4');
    num += 2;
    EXPECT_EQ(num.toChar(), '6');
    num += -3;
    EXPECT_EQ(num.toChar(), '3');
}


TEST(NIBBLE, GreaterThan) {
    BB::Nibble num1 = 3;
    int n = 4;
    EXPECT_EQ(num1 > n, false);
    n--;
    EXPECT_EQ(num1 > n, false);
    n--;
    EXPECT_EQ(num1 > n, true);
}
