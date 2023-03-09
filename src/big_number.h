//
// Created by Microzenas on 3/9/23.
//

#ifndef BIGNUMBER_BIG_NUMBER_H
#define BIGNUMBER_BIG_NUMBER_H
#include <string>
using namespace std;
class BigInt {
public:
    BigInt(const string);
    BigInt(const long long);

    BigInt(const BigInt&);

    void add(const BigInt&);
    void multiply(const BigInt&);
    void divide(const BigInt&);
    void subtract(const BigInt&);
    bool is_equal(const BigInt&);
    bool is_greater(const BigInt&);
    bool is_lesser(const BigInt&);
    bool is_prime();
private:
    string _num;
};

#endif //BIGNUMBER_BIG_NUMBER_H
