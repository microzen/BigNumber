#include "BigBits.h"
using namespace std;


namespace BB
{
    // **********************************************************************************************
    // Constructors:

    BigBits::BigBits()
    {
        number.resize(1, 0);
    }

    BigBits::BigBits(unsigned long long n)
    {
        number.resize(1, 0);
        number.at(0) = n;
    }

    BigBits::BigBits(const BigBits &other)
    {
        *this = other;
    }


    // **********************************************************************************************
    // Getters:

    const uint64_t & BigBits::at(unsigned int i) const
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

    vector<unsigned int> BigBits::toBin()
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
        for (unsigned int i=0; i<this->size(); i++)
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


    // **********************************************************************************************
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
        
        // if a.size() == b.size()
        for (unsigned int i=0; i<a.size(); i++)
        {
            if (a.at(i) < b.at(i))
            {
                return false;
            }
        }

        if (a == b)
        {
            return false;
        }

        return true;
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


    // **********************************************************************************************
    // Addition and Subtraction:

    BigBits & BigBits::operator +=(const BigBits &rhs)
    {
        BigBits a = *this;
        BigBits b = rhs;
        BigBits result;

        const uint64_t MAX = 18446744073709551615; // 2^^64 - 1
        uint64_t overflowA, overflowB;
        bool carryIn, carryOut=false;

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

        // For each element in result's number vector, add the two corresponding elements of a and b
        for (unsigned int i=0; i < result.size(); i++)
        {
            carryIn = carryOut;

            overflowA = MAX - a.at(i);
            overflowB = MAX - b.at(i);

            result.at(i) = carryIn + a.at(i) + b.at(i);

            if (a.at(i) > overflowB || b.at(i) > overflowA)
            {
                // sum of two overflows will be less than MAX, but sum of a and b will be more than MAX
                carryOut = true;
            }
            else if (a.at(i) == overflowB || b.at(i) == overflowA)
            {
                // sum of two overflows will be == to MAX, so will sum of a and b
                carryOut = carryIn;
            }
            else
            {
                // sum of two overflows will be more than MAX, but sum of a and b will be less than MAX
                carryOut = false;
            }

            if ((i == result.size()-1) && carryOut)
            {
                result.expand();
                result.at(i+1) = 1;
            }
        }

        number = result.getVect();

        return *this;
    }

    BigBits operator +(BigBits &a, BigBits &b)
    {
        BigBits temp = a;
        temp += b;
        return temp;
    }


    // **********************************************************************************************
    // Stream Operators:

    ostream & operator <<(ostream &os, const BigBits &a)
    {
        for (unsigned int i=0; i < a.size(); i++)
        {
            os << i+1 << ": " << a.at(i) << endl;
        }

        return os;
    }


    // **********************************************************************************************
    // Private Functions:

    unsigned int BigBits::ceilPowTwo(unsigned int value)
    {
        unsigned int ceil_num = pow(2, ceil(log2(value)));

        if (ceil_num < 64)
        {
            return 64;
        }
        
        return ceil_num;
    }


} // End of namespace BB