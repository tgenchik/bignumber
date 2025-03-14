#ifndef LONGNUMBER_HPP
#define LONGNUMBER_HPP

#include <vector>
#include <string>

class LongNumber {
public:
    LongNumber();
    LongNumber(std::string number);
    LongNumber(long double number);
    LongNumber(const LongNumber& other);
    ~LongNumber();

    LongNumber& operator=(const LongNumber& other);
    LongNumber& operator-=(const LongNumber& other);
    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;

    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;
    bool operator>=(const LongNumber& other) const;
    bool operator<=(const LongNumber& other) const;

    LongNumber operator-() const;

    void setPrecision(int binaryDigits);

    std::string toString(int accur) const;

    std::vector<int> digits;
    int precision;          
    bool isNegative; 
    int accuracy;        

   
    void deleteZeros();
    void addDigit(int digit);
    LongNumber makePi(int acur);
};
LongNumber operator ""_longnum(long double);
#endif 
