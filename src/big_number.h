//
// Created by Microzenas on 3/9/23.
//

#ifndef BIGNUMBER_BIG_NUMBER_H
#define BIGNUMBER_BIG_NUMBER_H
#include <string>
using namespace std;
namespace BigNumber {

    class BigInt {
    public:
        BigInt(const string);

        BigInt(const long long);

        BigInt(const BigInt &);

        void add(const BigInt &);

        void multiply(const BigInt &);

        void divide(const BigInt &);

        void subtract(const BigInt&);

        bool is_equal(const BigInt&);

        bool is_greater(const BigInt &);

        bool is_lesser(const BigInt &);

        bool is_prime();

        string get_number() const;

        string to_string() const;

    private:
        string _num;
    };

    BigInt operator+(const BigInt&,const BigInt&);
    BigInt operator-(const BigInt&,const BigInt&);
    BigInt operator*(const BigInt&,const BigInt&);
    BigInt operator/(const BigInt&,const BigInt&);

    bool operator==(const BigInt&,const BigInt&);
    bool operator>(const BigInt&,const BigInt&);
    bool operator<(const BigInt&,const BigInt&);


    BigInt operator+=(const BigInt&,const BigInt&);
    BigInt operator-=(const BigInt&,const BigInt&);
    BigInt operator*=(const BigInt&,const BigInt&);
    BigInt operator/=(const BigInt&,const BigInt&);

    bool operator!=(const BigInt&,const BigInt&);
    bool operator<=(const BigInt&,const BigInt&);
    bool operator>=(const BigInt&,const BigInt&);


}
#endif //BIGNUMBER_BIG_NUMBER_H
