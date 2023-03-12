#pragma once

#include <vector>
#include <bitset>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

namespace BB
{
    class BigBits
    {
        public:
            // Constructors
            BigBits();
            BigBits(uint64_t);
            BigBits(const BigBits &);
            BigBits(const string &);
            BigBits(const char *);

            // Getters
            const uint64_t at(unsigned int) const;
            vector<uint64_t> getVect() const;
            unsigned int getNumBits() const;
            uint64_t truncate(BigBits &) const;
            unsigned int size() const;
            vector<unsigned int> toBin() const;

            // Setters
            uint64_t & at(unsigned int);
            BigBits & randomize(unsigned int, unsigned int);
            BigBits & fromBin(vector<unsigned int>);
            
            // Mutators
            void expand();
            void resize(unsigned int);

            // Other
            BigBits &findMinSize();

            /// Operator Overloading ///

            // Direct Assignment
            BigBits & operator =(const BigBits &);
            BigBits & operator =(const uint64_t &);
            BigBits & operator =(const string &);
            BigBits & operator =(const char *);

            // Comparison operators
            bool operator ==(const BigBits &);
            bool operator !=(const BigBits &);
            bool operator >(const BigBits &);
            bool operator >=(const BigBits &);
            bool operator <(const BigBits &);
            bool operator <=(const BigBits &);

            bool operator ==(const uint64_t &);
            bool operator !=(const uint64_t &);
            bool operator >(const uint64_t &);
            bool operator >=(const uint64_t &);
            bool operator <(const uint64_t &);
            bool operator <=(const uint64_t &);

            bool operator ==(const string &);
            bool operator !=(const string &);
            bool operator >(const string &);
            bool operator >=(const string &);
            bool operator <(const string &);
            bool operator <=(const string &);

            bool operator ==(const char *);
            bool operator !=(const char *);
            bool operator >(const char *);
            bool operator >=(const char *);
            bool operator <(const char *);
            bool operator <=(const char *);

            // Incrementation/decrementation
            BigBits & operator ++();
            BigBits operator ++(int temp);
            /*
            BigBits &operator --();
            BigBits operator --(int temp);
            */

            // Addition and Subtraction
            BigBits & operator +=(const BigBits &);
            BigBits operator +(BigBits &);
            /*
            BigBits &operator -=(BigBits &, const BigBits &);
            BigBits operator -(const BigBits &, const BigBits &);
            */

            BigBits & operator +=(const uint64_t &);
            BigBits operator +(const uint64_t &);
            /*
            BigBits &operator -=(BigBits &, const BigBits &);
            BigBits operator -(const BigBits &, const BigBits &);

            // Multiplication and Division
            BigBits &operator *=(BigBits &, const BigBits &);
            BigBits operator *(const BigBits &, const BigBits &);
            BigBits &operator /=(BigBits &, const BigBits &);
            BigBits operator /(const BigBits &, const BigBits &);

            // Modulo
            BigBits &operator %=(BigBits &, const BigBits &);
            BigBits operator %(const BigBits &, const BigBits &);

            // Power Function
            BigBits &operator ^=(BigBits &,const BigBits &);
            BigBits operator ^^(BigBits &, const BigBits &);

            // Square Root
            BigBits & sqrt(BigBits &a);
            */

            // Stream operators
            friend ostream & operator <<(ostream &, const BigBits &a);
            
        private:
            // Private Data Members
            vector<uint64_t> number;

            // Private Helper Functions
            unsigned int ceilPowTwo(unsigned int) const;
            string toString() const;
            bool leftShiftOut(unsigned int) const;
    };


    class Nibble
    {
        public:
            Nibble();
            Nibble(uint8_t);

            bool shift(const bool);
            char toChar() const;

            Nibble & operator =(const uint8_t);
            Nibble & operator +=(const uint8_t);
            bool operator >(const uint8_t);

        private:
            uint8_t low : 4;
            uint8_t high : 4;
    };

} // End of namespace BB