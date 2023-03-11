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
            BigBits(unsigned long long);
            BigBits(const BigBits &);
            //BigBits(string); // I need operator+= for this I think

            // Getters
            const uint64_t & at(unsigned int) const;
            vector<uint64_t> getVect() const;
            unsigned int getNumBits() const;
            uint64_t truncate(BigBits &) const;
            unsigned int size() const;
            vector<unsigned int> toBin();

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
            BigBits &operator =(const BigBits &);
            BigBits &operator =(const uint64_t &);
            //BigBits &operator =(const string &);

            //Comparison operators
            bool operator ==(const BigBits &);
            bool operator !=(const BigBits &);
            bool operator >(const BigBits &);
            bool operator >=(const BigBits &);
            bool operator <(const BigBits &);
            bool operator <=(const BigBits &);

            /*
            //Incrementation/decrementation
            BigBits &operator ++();
            BigBits &operator --();
            */

            //Addition and Subtraction
            BigBits &operator +=(const BigBits &);
            friend BigBits operator +(BigBits &, BigBits &);
            /*
            BigBits &operator -=(BigBits &, const BigBits &);
            BigBits operator -(const BigBits &, const BigBits &);

            //Multiplication and Division
            BigBits &operator *=(BigBits &, const BigBits &);
            BigBits operator *(const BigBits &, const BigBits &);
            BigBits &operator /=(BigBits &, const BigBits &);
            BigBits operator /(const BigBits &, const BigBits &);

            //Modulo
            BigBits &operator %=(BigBits &, const BigBits &);
            BigBits operator %(const BigBits &, const BigBits &);

            //Power Function
            BigBits &operator ^=(BigBits &,const BigBits &);
            BigBits operator ^^(BigBits &, const BigBits &);

            // Square Root
            BigBits & sqrt(BigBits &a);
            */

            //Stream operators
            friend ostream & operator <<(ostream &, const BigBits &a);
            
        private:
            // Private Data Members
            vector<uint64_t> number;

            // Private Helper Functions
            unsigned int ceilPowTwo(unsigned int);
    };

} // End of namespace BB