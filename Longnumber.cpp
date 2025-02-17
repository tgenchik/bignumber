#include "LongNumber.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

LongNumber::LongNumber() : precision(0), isNegative(false) {}
int max(int a, int b) {
        return a > b ? a : b;
    }
int min(int a, int b) {
        return a < b ? a : b;
}    

std::ostream& operator << (std::ostream& out, const LongNumber& t){
    if (t.isNegative)
        out << '-';
    
	for (int i = 0; i < t.digits.size(); i++) {
        out << t.digits[i];
        if (t.digits.size() - t.precision - 1 == i && i != t.digits.size() - 1) 
            out << '.';
    }
	return out;
}

LongNumber::LongNumber(long double number) {
    precision = 0;
    isNegative = 0;
    if (number < 0) {
        isNegative = 1;
        number = - number;
    }
   
    u_int64_t now_digit = (1ull << 63);
    while(now_digit) {
        if (number >= now_digit) {
            number -= now_digit;
            digits.push_back(1);
        }
        else {
            if (digits.size())
                digits.push_back(0);
        }
        now_digit /= 2;
    }
    if (digits.size() == 0)
        digits.push_back(0);
    long double accuracy = 0.5, eps = 1e-10;
    while (accuracy > eps && number > eps) {
        precision++;
        if (number >= accuracy) {
            number -= accuracy;
            digits.push_back(1);
        }
        else {
            digits.push_back(0);
        }
        accuracy /= 2;
    }
}

LongNumber::LongNumber(const LongNumber& other) 
    : digits(other.digits), precision(other.precision), isNegative(other.isNegative) {}

LongNumber::~LongNumber() {}

LongNumber LongNumber::operator-() const {
    LongNumber inverse(*this);
    inverse.isNegative = !isNegative;
    return inverse;
}

LongNumber& LongNumber::operator=(const LongNumber& other) {
    if (this != &other) {
        digits = other.digits;
        precision = other.precision;
        isNegative = other.isNegative;
    }
    return *this;
}

LongNumber LongNumber::operator+(const LongNumber& other) const {
    if (isNegative != isNegative) {
            if (other.isNegative) return *this - (-other);
            return other - (- *this);
        }

    LongNumber result;
    int max_precision = max(precision, other.precision);
    int max_digit = max(digits.size() - precision, other.digits.size() - other.precision);
    int diff = precision - other.precision;

    result.digits.resize(max_precision + max_digit + 1);
    result.precision = max_precision;
    int extra_digit = 0;
        for (int i = 0; i < max_precision; i++) {
            int now = extra_digit;
            extra_digit = 0;
            if (precision >= i)
                if (diff >= 0)
                    now += digits[digits.size() - i - 1];
                else
                    now += digits[digits.size() - i - 1 - diff];

            if (other.precision >= i)
                if (diff <= 0)
                    now += other.digits[other.digits.size() - i - 1];
                else
                    now += other.digits[other.digits.size() - i - 1 + diff];
            
            if (now > 1) {
                extra_digit = 1;
                now -= 2;
            }
            result.digits[result.digits.size() - 1 - i] = now;
        }

        for (int i = 0; i < max_digit; i++) {
            int now = extra_digit;
            extra_digit = 0;
            if (digits.size() - precision >= i + 1)
                now += digits[digits.size() - precision - i - 1];

            if (other.digits.size() - other.precision >= i + 1)
                now += other.digits[other.digits.size() - other.precision - i - 1];

            if (now > 1) {
                extra_digit = 1;
                now -= 2;
            }
            result.digits[result.digits.size() - result.precision - i - 1] = now;
        }
        if (extra_digit)
            result.digits[0] = 1;

        result.deleteZeros();
        return result;
}

LongNumber LongNumber::operator-(const LongNumber& other) const { 
    if (other.isNegative) return *this + (-other);
        else if (isNegative) return -(- *this + other);

    if (isNegative == 0) {
        if (*this < other)
            return -(other - *this);
    }
    else {
        if (*this > other)
            return -(other - *this);
    }

    LongNumber result;
    int max_precision = max(precision, other.precision);
    int max_digit = max(digits.size() - precision, other.digits.size() - other.precision);
    int diff = precision - other.precision;

    result.digits.resize(max_precision + max_digit + 1);
    result.precision = max_precision;
    int extra_digit = 0;
        for (int i = 0; i < max_precision; i++) {
            int now = extra_digit;
            extra_digit = 0;
            if (precision >= i)
                if (diff >= 0)
                    now += digits[digits.size() - i - 1];
                else
                    now += digits[digits.size() - i - 1 - diff];

            if (other.precision >= i)
                if (diff <= 0)
                    now -= other.digits[other.digits.size() - i - 1];
                else
                    now -= other.digits[other.digits.size() - i - 1 + diff];
            
            if (now < 0) {
                extra_digit = -1;
                now += 2;
            }
            result.digits[result.digits.size() - 1 - i] = now;
        }

        for (int i = 0; i < max_digit; i++) {
            int now = extra_digit;
            extra_digit = 0;
            if (digits.size() - precision >= i + 1)
                now += digits[digits.size() - precision - i - 1];

            if (other.digits.size() - other.precision >= i + 1)
                now -= other.digits[other.digits.size() - other.precision - i - 1];

            //std::cout << now << " ";
            if (now < 0) {
                extra_digit = -1;
                now += 2;
            }
            //std::cout << now << "\n";
            result.digits[result.digits.size() - result.precision - i - 1] = now;
        }
        result.isNegative = isNegative;
        result.deleteZeros();
        return result;
}

void LongNumber::deleteZeros() {
    reverse(digits.begin(), digits.end());
    while (digits.size() - precision > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.empty()) {
        digits.push_back(0);
        isNegative = false;
    }
    reverse(digits.begin(), digits.end());
    
}

LongNumber LongNumber::operator*(const LongNumber& other) const {
    LongNumber ans;
   
    ans.isNegative = (isNegative + other.isNegative) % 2;
    ans.digits.resize(digits.size() + other.digits.size() + 1);
    //std::cout << other << "\n";
    for (int i = 0; i < digits.size(); i++) {
            for (int j = 0; j < other.digits.size(); j++) {
                if (digits[i] && other.digits[j]) {
                    ans.digits[digits.size() + other.digits.size() - i - j - 2]++;
                }
            }
        }

    for (int i = 0; i < ans.digits.size() - 1; i++){
            ans.digits[i + 1] += ans.digits[i] / 2;
            ans.digits[i] %= 2;
    }
    
    reverse(ans.digits.begin(), ans.digits.end());
    ans.precision = precision + other.precision;
    ans.deleteZeros();
    return ans;
}

LongNumber LongNumber::operator/(const LongNumber& other) const {
    LongNumber result;
    
    return result;
}

bool LongNumber::operator==(const LongNumber& other) const {
    return digits == other.digits && precision == other.precision && isNegative == other.isNegative;
}

bool LongNumber::operator!=(const LongNumber& other) const {
    return !(*this == other);
}

bool LongNumber::operator<(const LongNumber& other) const {
    if (isNegative != other.isNegative) 
            return isNegative == 1;

        if (digits.size() - precision > other.digits.size() - other.precision)
            return 0;
        else if (digits.size() - precision < other.digits.size() - other.precision)
            return 1;
        
        for (int i = 0; i < min(digits.size(), other.digits.size()); i++) {
            if (digits[i] < other.digits[i] && isNegative == 0) 
                return 1;
            if (digits[i] < other.digits[i] && isNegative == 1) 
                return 0;
            if (digits[i] > other.digits[i] && isNegative == 0) 
                return 0;
            if (digits[i] > other.digits[i] && isNegative == 1) 
                return 1;
        }
        
        if (digits.size() < other.digits.size()) 
            return isNegative == 0;
        if (digits.size() > other.digits.size())
            return isNegative == 1;
        return 0;
}

bool LongNumber::operator>(const LongNumber& other) const {
    if (isNegative != other.isNegative) 
            return isNegative == 0;

        if (digits.size() - precision > other.digits.size() - other.precision)
            return 1;
        else if (digits.size() - precision < other.digits.size() - other.precision)
            return 0;
        
        for (int i = 0; i < min(digits.size(), other.digits.size()); i++) {
            if (digits[i] < other.digits[i] && isNegative == 0) 
                return 0;
            if (digits[i] < other.digits[i] && isNegative == 1) 
                return 1;
            if (digits[i] > other.digits[i] && isNegative == 0) 
                return 1;
            if (digits[i] > other.digits[i] && isNegative == 1) 
                return 0;
        }
        
        if (digits.size() < other.digits.size()) 
            return isNegative == 1;
        if (digits.size() > other.digits.size())
            return isNegative == 0;
        return 0;
}

void LongNumber::setPrecision(int binaryDigits) {
    precision = binaryDigits;
}


LongNumber operator"" _longnum(long double number) {
    return LongNumber(number);
}


std::string LongNumber::toString() const {
    std::string result;
    if (isNegative) {
        result += '-';
    }
    for (int digit : digits) {
        result += std::to_string(digit);
    }
    return result;
}

void LongNumber::addDigit(int digit) {
    digits.push_back(digit);
}

