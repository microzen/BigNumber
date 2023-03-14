//
// Created by Microzenas on 3/11/23.
//
#include <gtest/gtest.h>
#include <BigBits.h>
#include <bitset>
#include <cstdint>

TEST(BBITS,Init){
    // Default
    EXPECT_NO_THROW(BB::BigBits());

    // uint64_t
    EXPECT_NO_THROW(BB::BigBits(ULLONG_MAX));
    EXPECT_NO_THROW(BB::BigBits(1234567));
    EXPECT_NO_THROW(BB::BigBits(323));

    // string
    EXPECT_NO_THROW(BB::BigBits(string("123")));
    EXPECT_ANY_THROW(BB::BigBits(string("-12")));
    EXPECT_ANY_THROW(BB::BigBits(string("64abc")));
    EXPECT_NO_THROW(BB::BigBits(string("123456987123786783654378264587234657823465782346578236457823645")));

    BB::BigBits bigNum = string("90445398191276609683561357299864965001643765149");
    EXPECT_EQ(bigNum.size(), 3);
    EXPECT_EQ(bigNum.at(0),11072005533870792623);
    EXPECT_EQ(bigNum.at(1),7818575067201490371);
    EXPECT_EQ(bigNum.at(2),12047803422806778902);


    /*
    EXPECT_NO_THROW(BB::BigBits("7823645"));
    EXPECT_ANY_THROW(BB::BigBits("-7823645"));
    EXPECT_ANY_THROW(BB::BigBits("a7823645"));
    EXPECT_NO_THROW(BB::BigBits('1'));
    EXPECT_NO_THROW(BB::BigBits('-1'));
    EXPECT_NO_THROW(BB::BigBits('a'));
     */
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

    BB::BigBits num2 = 9007199254740983;
    BB::BigBits num3 = 9007199254740992;
    num2 += num3;
    EXPECT_EQ(num2.at(0), 18014398509481975);
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

TEST(BBITS, LessThan) {
    BB::BigBits a(ULLONG_MAX);
    BB::BigBits b(ULLONG_MAX - 2);
    bool test = false;

    EXPECT_FALSE(a < b);
    test = a < b;
    b++;
    EXPECT_FALSE(a < b);
    test = a < b;
    b++;
    EXPECT_FALSE(a < b);
    test = a < b;
    b++;
    EXPECT_TRUE(a < b);
    test = a < b;
    b++;
    EXPECT_TRUE(a < b);
    test = a < b;
    b++;
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



    /*
    srand(0);
    bin1.resize(0);
    for (unsigned int i=0; i<80; i++)
    {
        bin1.push_back(rand()%2);
    }
    num.fromBin(bin1);

    EXPECT_EQ(num.size(), 2);
    EXPECT_EQ(num.at(0), 8341798683095734119);
    EXPECT_EQ(num.at(1), 58618);
    */

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
    num2 = 0;
    num1 = num1 ^ num2;
    EXPECT_EQ(num1.at(0), 1);

    num1 = 2;
    num2 = 64;
    num1 = num1 ^ num2;
    EXPECT_EQ(num1.at(0), 0);
    EXPECT_EQ(num1.at(1), 1);
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
