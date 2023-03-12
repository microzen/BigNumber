#include "BigBits.h"
using namespace std;


namespace BB
{
    // **********************************************************************************************
    // BigBits:
    // **********************************************************************************************
    // Constructors:

    BigBits::BigBits()
    {
        number.resize(1,0);
    }

    BigBits::BigBits(uint64_t n)
    {
        number.resize(1);
        *this = n;
    }

    BigBits::BigBits(const BigBits &other)
    {
        *this = other;
    }

    // Work in progress
    BigBits::BigBits(const string &s)
    {
        *this = s;
    }

    BigBits::BigBits(const char *s)
    {
        *this = s;
    }


    // **********************************************************************************************
    // Getters:

    const uint64_t BigBits::at(unsigned int i) const
    {
        return number.at(i);
    }

    vector<uint64_t> BigBits::getVect() const
    {
        return number;
    }

    unsigned int BigBits::getNumBits() const
    {
        return number.size() * 64;
    }

    uint64_t BigBits::truncate(BigBits &n) const
    {
        return n.at(0);
    }

    unsigned int BigBits::size() const
    {
        return number.size();
    }

    vector<unsigned int> BigBits::toBin() const
    {
        vector<unsigned int> bin;
        
        for (unsigned int i=0; i<this->size(); i++)
        {
            uint64_t currentNum = this->at(i);
            do
            {
                bin.push_back(currentNum % 2);
                currentNum /= 2;
            } while (currentNum > 0);
        }

        unsigned int new_len = ceilPowTwo(bin.size());
        bin.resize(new_len, 0);

        return bin;
    }


    // **********************************************************************************************
    // Setters:

    uint64_t & BigBits::at(unsigned int i)
    {
        return number.at(i);
    }

    BigBits & BigBits::randomize(unsigned int min_power, unsigned int max_power)
    {
        unsigned int bin_digits = rand() % (max_power - min_power + 1) + min_power;
        cout << bin_digits << endl;
        vector<unsigned int> bin(bin_digits, 0);

        bin.at(bin.size()-1) = 1;
        for (unsigned int i = 0; i<bin.size()-1; i++)
        {
            bin.at(i) = rand() % 2;
        }

        BigBits temp;
        temp.fromBin(bin);
        *this = temp;

        return *this;
    }

    // CHANGE: need to store num as BigBits, 
    // but I need more operators to do that than I currently have 3/8/23
    BigBits & BigBits::fromBin(vector<unsigned int> bin)
    {
        unsigned int num=0;

        for (unsigned int i=0; i<bin.size(); i++)
        {
            if (bin.at(i) == 1)
            {
                num += pow(2, i);
            }
        }

        *this = BigBits(num);

        return *this;
    }


    // **********************************************************************************************
    // Mutators:

    void BigBits::expand()
    {
        number.resize(number.size()*2, 0);
    }

    void BigBits::resize(unsigned int elements)
    {   
        // I still need to handle the case where elements < *this.size()
        if (elements >= number.size())
        {
            number.resize(elements, 0);
        }
    }


    // **********************************************************************************************
    // Other:

    BigBits & BigBits::findMinSize()
    {
        unsigned int counter = 0;
        for (unsigned int i=0; i < this->size(); i++)
        {
            uint64_t currentVal = this->at(i);
            do
            {
                counter++;
                currentVal /= 2;
            } while (currentVal > 0);
        }
        unsigned int new_size = ceilPowTwo(counter);
        this->number.resize(new_size);

        return *this;
    }


    // Operation Overloading:
    // **********************************************************************************************
    // Direct Assignment:

    BigBits & BigBits::operator =(const BigBits &n)
    {
        number = n.getVect();
        return *this;
    }

    BigBits & BigBits::operator =(const uint64_t &n)
    {
        number.at(0) = n;
        return *this;
    }

    // I need BigBits multiplication to handle the case where the string represents a num > 2^64
    BigBits & BigBits::operator =(const string &s)
    {
        BigBits temp;
        for (unsigned int i=0; i < s.size(); i++)
        {
            uint64_t nextDigit = stoi(s.substr((s.size() - i - 1), 1));
            uint64_t nextNum = nextDigit * pow(10, i);
            temp += nextNum;
        }

        *this = temp;
        return *this;
    }

    BigBits & BigBits::operator =(const char *s)
    {
        *this = string(s);
        return *this;
    }


    // **********************************************************************************************
    // Comparison Operators

    bool BigBits::operator ==(const BigBits &b)
    {
        BigBits a = *this;

        if (a.size() != b.size())
        {
            return false;
        }

        for (unsigned int i=0; i < a.size(); i++)
        {
            if (a.at(i) != b.at(i))
            {
                return false;
            }
        }

        return true;
    }

    bool BigBits::operator !=(const BigBits &b)
    {
        BigBits a = *this;
        return !(a == b);
    }

    bool BigBits::operator >(const BigBits &b)
    {
        BigBits a = *this;

        if (a.size() > b.size())
        {
            return true;
        }
        if (a.size() < b.size())
        {
            return false;
        }

        for (unsigned int i = a.size() - 1; i>=0; i-- != 0)
        {
            if (a.at(i) > b.at(i))
            {
                return true;
            }
        }

        return false;
    }

    bool BigBits::operator >=(const BigBits &b)
    {
        BigBits a = *this;

        if (a > b || a == b)
        {
            return true;
        }

        return false;
    }

    bool BigBits::operator <(const BigBits &b)
    {
        BigBits a = *this;
        return !(a > b && a == b);
    }

    bool BigBits::operator <=(const BigBits &b)
    {
        BigBits a = *this;

        if (a < b || a == b)
        {
            return true;
        }

        return false;
    }

    bool BigBits::operator ==(const uint64_t &b)
    {
        BigBits temp = b;
        return *this == temp;
    }

    bool BigBits::operator !=(const uint64_t &b)
    {
        BigBits temp = b;
        return *this != temp;
    }

    bool BigBits::operator >(const uint64_t &b)
    {
        BigBits temp = b;
        return *this > temp;
    }

    bool BigBits::operator >=(const uint64_t &b)
    {
        BigBits temp = b;
        return *this >= temp;
    }

    bool BigBits::operator <(const uint64_t &b)
    {
        BigBits temp = b;
        return *this < temp;
    }

    bool BigBits::operator <=(const uint64_t &b)
    {
        BigBits temp = b;
        return *this <= temp;
    }

    bool BigBits::operator ==(const string &b)
    {
        BigBits temp = b;
        return *this == temp;
    }

    bool BigBits::operator !=(const string &b)
    {
        BigBits temp = b;
        return *this != temp;
    }

    bool BigBits::operator >(const string &b)
    {
        BigBits temp = b;
        return *this > temp;
    }

    bool BigBits::operator >=(const string &b)
    {
        BigBits temp = b;
        return *this >= temp;
    }

    bool BigBits::operator <(const string &b)
    {
        BigBits temp = b;
        return *this < temp;
    }

    bool BigBits::operator <=(const string &b)
    {
        BigBits temp = b;
        return *this <= temp;
    }

    bool BigBits::operator ==(const char *b)
    {
        BigBits temp = b;
        return *this == temp;
    }

    bool BigBits::operator !=(const char *b)
    {
        BigBits temp = b;
        return *this != temp;
    }

    bool BigBits::operator >(const char *b)
    {
        BigBits temp = b;
        return *this > temp;
    }

    bool BigBits::operator >=(const char *b)
    {
        BigBits temp = b;
        return *this >= temp;
    }

    bool BigBits::operator <(const char *b)
    {
        BigBits temp = b;
        return *this < temp;
    }
    
    bool BigBits::operator <=(const char *b)
    {
        BigBits temp = b;
        return *this <= temp;
    }


    // **********************************************************************************************
    // Incrementation/decrementation

    BigBits & BigBits::operator ++()
    {
        BigBits temp = 1;
        *this += temp;
        return *this;
    }

    BigBits BigBits::operator ++(int temp)
    {
        ++(*this);
        return *this;
    }


    // **********************************************************************************************
    // Addition and Subtraction:

    BigBits & BigBits::operator +=(const BigBits &rhs)
    {
        BigBits a = *this;
        BigBits b = rhs;
        BigBits result;

        bool carryIn, carryOut=false;
        uint64_t inverseA;
        const uint64_t MAX = 18446744073709551615; // 2^^64 - 1

        // Resize so a, b, and result are the same size
        if (a.size() > b.size())
        {
            b.resize(a.size());
        }
        else if (a.size() < b.size())
        {
            a.resize(b.size());
        }
        result.resize(a.size());
        unsigned int end = result.size(); // Prime for loop

        // For each element in result's number vector, add the two corresponding elements of a and b
        for (unsigned int i=0; i < end; i++)
        {
            carryIn = carryOut;
            end = result.size();
            inverseA = MAX - a.at(i);

            // Determine the carry out state
            if (inverseA < b.at(i))
            {
                // Sum of a and b will be more than MAX
                carryOut = true;
            }
            else if (inverseA == b.at(i))
            {   
                // Sum of a and b will == MAX
                carryOut = carryIn;
            }
            else // (inverseA > b.at(i))
            {
                // Sum of a and b will be less than MAX
                carryOut = false;
            }

            // Determine if a resize is necessary
            if ((i == result.size()-1) && carryOut)
            {
                result.expand();
                result.at(i+1) = carryOut;
            }

            // Actual add operation
            result.at(i) = carryIn + a.at(i) + b.at(i);
        }

        // result.findMinSize(); // I think this is only needed for subtraction
        number = result.getVect();

        return *this;
    }

    BigBits BigBits::operator +(BigBits &b)
    {
        BigBits temp = *this;
        temp += b;
        return temp;
    }

    BigBits & BigBits::operator +=(const uint64_t &n)
    {
        return *this += BigBits(n);
    }

    BigBits BigBits::operator +(const uint64_t &n)
    {
        BigBits temp = *this;
        temp += n;
        return temp;
    }


    // **********************************************************************************************
    // Stream Operators:

    // Eventually I might need to use Binary to BCD
    ostream & operator <<(ostream &os, const BigBits &a)
    {
        /*
        // temp method
        for (unsigned int i=0; i < a.size(); i++)
        {
            os << i+1 << ": " << a.at(i) << endl;
        }
        */

        string s = a.toString();
        os << s;

        /*
        // string method
        string s = "";
        // for element in number vector
        unsigned int i = a.size();
        do
        {
            i--;
            unsigned long long currentNum = a.at(i);
            do
            {
                s += to_string(currentNum % 10);
                currentNum /= 10;
            } while (currentNum > 0);
        } while (i != 0);
        cout << s;
        */
        
        /*
        for (unsigned int i = (a.size() - 1); i>=0; i--)
        {
            cout << "i: " << i << endl;
            unsigned long long currentNum = a.at(i);
            do
            {
                s += to_string(currentNum % 10);
                currentNum /= 10;
            } while (currentNum > 0);
        }
        cout << s;
        */

        cout << endl;

        return os;
    }


    // **********************************************************************************************
    // Private Functions:

    // Takes an unsigned int n and returns the smallest power of two that is >= n and >= 64
    unsigned int BigBits::ceilPowTwo(unsigned int n) const
    {
        unsigned int ceil_num = pow(2, ceil(log2(n)));

        // Since BigBits uses 64 bit numbers, the smallest relevant power is 64
        if (ceil_num < 64)
        {
            return 64;
        }
        
        return ceil_num;
    }

    //TODO: Debug
    //      It produces the correct output for even numbers <= 8
    //      But thats not very useful, all other inputs seem to produce
    //      incorrect outputs
    string BigBits::toString() const
    {   
        int bcdSize = 1;
        int bbSize = this->size() * 64;
        vector<Nibble> bcd;
        string result = "";
        bool shiftIn, 
             shiftOut = this->leftShiftOut(this->size() - 1);

        // First iteration
        bcd.resize(bcdSize);
        bcd.at(0) = shiftOut;

        // For every bit in *this
        for (int i=1; i < bbSize; i++)
        {
            // Shift out next bit from *this
            shiftOut = this->leftShiftOut(bbSize - i - 1);

            // For every nibble in bcd
            for (int j=0; j < bcdSize; j++)
            {
                shiftIn = shiftOut;

                // Apply double dabble
                if (bcd.at(j) > 4)
                {
                    bcd.at(j) += 3;
                }
                shiftOut = bcd.at(j).shift(shiftIn);

                // Check if bcd needs to be expanded
                if ((j == (bcdSize - 1)) && shiftOut)
                {
                    bcdSize++;
                    bcd.resize(bcdSize, shiftOut);
                }
            }
        }

        //Translate BCD bits to string
        for (unsigned int i=0; i<bcd.size(); i++)
        {
            result += bcd.at(i).toChar();
        }

        return result;
    }

    bool BigBits::leftShiftOut(unsigned int i) const
    {
        vector<unsigned int> bin = this->toBin();
        return bin.at(i);
    }


    // **********************************************************************************************
    // Nibble:
    // **********************************************************************************************
    // Constructors:

    Nibble::Nibble()
    {
        low = 0;
        high = 0;
    }

    Nibble::Nibble(uint8_t n)
    {
        low = (n & 0xF);
        high = 0;
    }

    // **********************************************************************************************
    // Helper Functions:

    bool Nibble::shift(const bool shiftIn)
    {
        bool shiftOut = low & 0b00001000;
        low = low << 1;
        low += shiftIn;
        return shiftOut;
    }

    char Nibble::toChar() const
    {
        return low + '0';
    }

    // **********************************************************************************************
    // Operator Overloading:

    Nibble & Nibble::operator =(const uint8_t n)
    {
        low = (n & 0xF);
        return *this;
    }

    Nibble & Nibble::operator +=(const uint8_t n)
    {
        low += (n & 0xF);
        return *this;
    }

    bool Nibble::operator >(const uint8_t n)
    {
        return low > (n & 0xF);
    }

} // End of namespace BB