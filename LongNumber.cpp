#include "LongNumber.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>

int max(int a, int b) {
        return a > b ? a : b;
}
int min(int a, int b) {
        return a < b ? a : b;
}

class decimal{
public:
    std::vector <int> num;

    decimal (int number) {
        num.push_back(number);
    }
    decimal(std::vector<int> arr){
        num = arr;
    }
    decimal(){
    }

    decimal operator+(const decimal& other) const { // большее с меньшим
        decimal result;
        int extra_digit = 0;
        for (int i = 0; i < max(num.size(), other.num.size()); i++) { // max
            int now = extra_digit;
            extra_digit = 0;
            if (i < num.size())
                now += num[num.size() - 1 - i];

            if (i < other.num.size())
                now += other.num[other.num.size() - 1 - i];

            if (now > 9) {
                now -= 10;
                extra_digit = 1;
            }
            result.num.push_back(now);
        }
        if (extra_digit)
            result.num.push_back(1);
        std::reverse(result.num.begin(), result.num.end());
        return result;
    }

    decimal operator-(const decimal& other) const { // большее с меньшим
        decimal result;
        int extra_digit = 0;
        for (int i = 0; i < num.size(); i++) { // max
            int now = extra_digit;
            extra_digit = 0;
            if (i < num.size())
                now += num[num.size() - 1 - i];

            if (i < other.num.size())
                now -= other.num[other.num.size() - 1 - i];

            if (now < 0) {
                now += 10;
                extra_digit = -1;
            }
            result.num.push_back(now);
        }
        while(result.num.size() && result.num.back() == 0)
            result.num.pop_back();
        std::reverse(result.num.begin(), result.num.end());
        return result;
    }

    bool operator < (const decimal& other) const {
        if (num.size() < other.num.size())
            return 1;
        else if (num.size() > other.num.size())
            return 0;

        for (int i = 0; i < num.size(); i++) {
            if (num[i] < other.num[i]) {
                return 1;
            }
            else if (num[i] > other.num[i]) {
                return 0;
            }
        }
        return 0;
    }
    bool operator == (const decimal& other) const {
        if (num.size() != other.num.size())
            return 0;
        for (int i = 0; i < num.size(); i++) {
            if (num[i] != other.num[i])
                return 0;
        }
        return 1;
    }
    bool operator <= (const decimal& other) const {
        return *this < other || *this == other;
    }
};
decimal division(decimal &t) {
        int extra_digits = 0;
        for (int i = 0; i < t.num.size(); i++){
            int now = extra_digits + t.num[i] / 2;
            if (t.num[i] % 2)
                extra_digits = 5;
            else
                extra_digits = 0;

            t.num[i] = now;
        }
        reverse(t.num.begin(), t.num.end());
        while(t.num.size() && t.num.back() == 0)
            t.num.pop_back();
        reverse(t.num.begin(), t.num.end());  
        return t;
}


LongNumber::LongNumber() : precision(0), isNegative(false), accuracy(0) {}


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
LongNumber::LongNumber(std::string number) {
    isNegative = 0;
    precision = 0;
    if (number[0] == '-')
        isNegative = 1;
    decimal integer;
    int last = 0;
    for (int i = isNegative; i < number.size() && number[i] != '.'; i++) {
        integer.num.push_back(number[i] - '0');
        last = i;
    }
    decimal bit(1);
    int digits_count = 1;
    while (bit < integer) {
        bit = bit + bit;
        digits_count++;
    }
    while(digits_count--) {
        if (bit <= integer) { 
            integer = integer - bit;
            digits.push_back(1);
        }
        else {
            if (digits.size())
                digits.push_back(0);
        }
        division(bit);
        
    }

    last += 2;
    decimal fraction;
    for (int i = last; i < number.size(); i++) {
        fraction.num.push_back(number[i] - '0');
    }
    int boost_accuracy = 40;
    bit.num.clear();
    bit.num.push_back(5);
    for (int i = 1; i < fraction.num.size() + boost_accuracy; i++) {
        bit.num.push_back(0);
    }
    digits_count = fraction.num.size();
    digits_count += boost_accuracy;
    while(digits_count--) {
        if (bit <= fraction) {
            fraction = fraction - bit;
            digits.push_back(1);
        }
        else {
            if (digits.size())
                digits.push_back(0);
        }
        division(bit);
        precision++;
    }
    accuracy = precision;

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
    long double accuracy_count = 0.5, eps = 1e-30;
    while (accuracy_count > eps && number > eps) {
        precision++;
        if (number >= accuracy_count) {
            number -= accuracy_count;
            digits.push_back(1);
        }
        else {
            digits.push_back(0);
        }
        accuracy_count /= 2;
    }
    accuracy = precision;
}

LongNumber::LongNumber(int number) {
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
}

LongNumber::LongNumber(const LongNumber& other)
    : digits(other.digits), precision(other.precision), isNegative(other.isNegative), accuracy(other.accuracy) {}

LongNumber::~LongNumber() {}

LongNumber LongNumber::operator-() const {
    LongNumber inverse(*this);
    inverse.isNegative = !isNegative;
    return inverse;
}

LongNumber& LongNumber::operator=(const LongNumber& other) {
        digits = other.digits;
        precision = other.precision;
        accuracy = other.precision;
        isNegative = other.isNegative;

    return *this;
}

LongNumber LongNumber::operator+(const LongNumber& other) const {
    if (isNegative != other.isNegative) {
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
    int last_1 = digits.size() - 1;
    int last_2 = other.digits.size() - 1;
    for (int i = 0; i < max_precision; i++) {
        int now = extra_digit;
        extra_digit = 0;

        if (max_precision - precision <= i)
            now += digits[last_1--];


        if (max_precision - other.precision <= i)
            now += other.digits[last_2--];


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
    int last_1 = digits.size() - 1;
    int last_2 = other.digits.size() - 1;
        for (int i = 0; i < max_precision; i++) {
            int now = extra_digit;
            extra_digit = 0;
            if (max_precision - precision <= i)
                now += digits[last_1--];

            if (max_precision - other.precision <= i)
                now -= other.digits[last_2--];

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

            if (now < 0) {
                extra_digit = -1;
                now += 2;
            }
            result.digits[result.digits.size() - result.precision - i - 1] = now;
        }

        result.isNegative = isNegative;
        result.deleteZeros();
        return result;
}

LongNumber& LongNumber::operator-=(const LongNumber& other) {
   return *this = *this - other;
}

void LongNumber::deleteZeros() {
    while (digits.size() && precision && digits.back() == 0) {
        digits.pop_back();
        precision--;
    }
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
    LongNumber divisible = *this;
    LongNumber divider = other;
    result.isNegative = (isNegative + other.isNegative) % 2;
    divider.isNegative = 0;
    divisible.isNegative = 0;

    int diff = (digits.size() - precision) - (other.digits.size() - other.precision); // 0...
    result.accuracy = 330;
    LongNumber now(1);
    for (int i = 0; i < diff; i++) {
        now.digits.push_back(0);
    }

    for (int i = 0; i <= diff; i++) {
        if (divisible >= now * divider) {
            divisible = divisible - (now * divider);
            result.digits.push_back(1);

        }
        else
            result.digits.push_back(0);

        if (i != diff) {
            now.digits[0] = 0;
            now.digits[1] = 1;
            now.deleteZeros();
        }
    }

    if (result.digits.size() == 0)
        result.digits.push_back(0);
    now = 0.5_longnum;
    while(result.precision < result.accuracy) {
        if (divisible >= now * divider) {
           divisible = (divisible - (now * divider));
            result.digits.push_back(1);
        }
        else
            result.digits.push_back(0);

        result.precision++;
        now.digits.back() = 0;
        now.digits.push_back(1);
        now.precision++;

    }
    result.deleteZeros();
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

        if (digits.size() - precision > other.digits.size() - other.precision){
            if (isNegative == 0)
                return 0;
            else 
                return 1;
        }
        else if (digits.size() - precision < other.digits.size() - other.precision) {
            if (isNegative == 0)
                return 1;
            else 
                return 0;
        }

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

         if (digits.size() - precision > other.digits.size() - other.precision){
            if (isNegative == 0)
                return 1;
            else 
                return 0;
        }
        else if (digits.size() - precision < other.digits.size() - other.precision) {
            if (isNegative == 0)
                return 0;
            else 
                return 1;
        }

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
bool LongNumber::operator>=(const LongNumber& other) const {
    return *this > other || *this == other;
}
bool LongNumber::operator<=(const LongNumber& other) const {
    return *this < other || *this == other;
}
void LongNumber::setPrecision(int binaryDigits) {
    accuracy = binaryDigits;
    while(precision > accuracy) {
        precision--;
        digits.pop_back();
    }
}


LongNumber operator"" _longnum(long double number) {
    return LongNumber(number);
}

LongNumber makePI(int acur){
    LongNumber pi(0);
    LongNumber multiplier(1), denominator(16);
    LongNumber a1(4), b1(2), c1(1), d1(1);
    LongNumber den1(1), den2(4), den3(5), den4(6);
    LongNumber eight(8);

    for (int i = 0; i < acur; i++) {
        pi = pi + multiplier * ((a1 / den1) - (b1 / den2) - (c1 / den3) - (d1 / den4));
        multiplier = multiplier / denominator;
        den1 = den1 + eight;
        den2 = den2 + eight;
        den3 = den3 + eight;
        den4 = den4 + eight;
    }
    return pi;
}
void LongNumber::addDigit(int digit) {
    digits.push_back(digit);
}





std::ostream& operator << (std::ostream& out, const decimal& t){
    for (int i = 0; i < t.num.size(); i++)
        out << t.num[i];
	return out;
}



std::string LongNumber::toString(int accur = 0) const {
    std::string result_int;
    std::string result_float;
    if (isNegative)
        result_int = '-';
    decimal res, bit(1);
    for (int i = digits.size() - precision - 1; i > -1; i--) {
        if (digits[i])
            res = res + bit;
        bit = bit + bit;
        
    }
    
    for(int i = 0; i < res.num.size(); i++) {
        result_int.push_back(res.num[i] + '0');
    }
    if (precision == 0) 
        return result_int;
    std::vector <int> arr(precision, 0);
    arr[0] = 5;
    decimal now(arr);
    decimal res_float;
    for (int i = digits.size() - precision; i < digits.size(); i++) {
        if (digits[i])
            res_float = res_float + now;
       division(now);
    }

    for(int i = 0; i < accur; i++) {
        result_float.push_back(res_float.num[i] + '0');
    }

    if (precision != 0) {
        result_int = result_int + "." + result_float;
    }
    return result_int;
}
