#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class bignumber{
public:
    int max(int a, int b) const {
        return a > b ? a : b;
    }
    int min(int a, int b) const {
        return a < b ? a : b;
    }               
    int sign = 1;
    std::vector <int> digits;
    std::vector <int> accuracy;

    bignumber(std::string str) {
        int i = 0;
        if (str[i] == '-'){
            sign = -1;
            i++;
        }
        while (i < str.size() && str[i] != '.')
            digits.push_back(str[i++] - '0');
        i++;
        
        while (i < str.size())
            accuracy.push_back(str[i++] - '0');
    }

    bignumber (std::vector <int> dig,  std::vector <int> accur, int sig) {
        digits = dig;
        accuracy = accur;
        sign = sig;
    }

    bignumber operator + (const bignumber& other) const {
        std::vector <int> now_dig;
        std::vector <int> now_acur;
        
        int extra_digit = 0;
        for (int i = 0; i < max(accuracy.size(), other.accuracy.size()); i++) {
            int now = extra_digit;
            extra_digit = 0;
            if (accuracy.size() >= i)
                now += accuracy[accuracy.size() - i - 1];

            if (other.accuracy.size() >= i)
                now += other.accuracy[other.accuracy.size() - i - 1];

            
            if (now > 1) {
                extra_digit = 1;
                now -= 2;
            }
            now_acur.push_back(now);
        }
        
        for (int i = 0; i < max(digits.size(), other.digits.size()); i++) {
            int now = extra_digit;
            extra_digit = 0;
            if (digits.size() >= i)
                now += digits[digits.size() - i - 1];

            if (other.digits.size() >= i)
                now += other.digits[other.digits.size() - i - 1];

            
            if (now > 1) {
                extra_digit = 1;
                now -= 2;
            }
            now_dig.push_back(now);
        }
        if (extra_digit)
            now_dig.push_back(1);
        
        reverse(now_dig.begin(), now_dig.end());
        reverse(now_acur.begin(), now_acur.end());
        return bignumber(now_dig, now_acur, sign);
    }

    bignumber operator * (const bignumber& other) const {
        std::vector <int> number_1;
        std::vector <int> number_2;

        for (int i = 0; i < digits.size(); i++)
            number_1.push_back(digits[i]);
        for (int i = 0; i < accuracy.size(); i++)
            number_1.push_back(accuracy[i]);

        for (int i = 0; i < other.digits.size(); i++)
            number_2.push_back(other.digits[i]);

        for (int i = 0; i < other.accuracy.size(); i++)
            number_2.push_back(other.accuracy[i]);
        
            

        std::vector <int> ans(number_1.size() + number_2.size());

        // for (int i = number_1.size() - 1; i > - 1 ; i--) {
        //     for (int j = number_2.size() - 1; j > - 1; j--) {
        //         if (number_1[i] && number_2[j]) {
        //             ans[i + j]++;
        //         }
        //     }
        // }

        for (int i = 0; i < number_1.size(); i++) {
            for (int j = 0; j < number_2.size(); j++) {
                if (number_1[i] && number_2[j]) {
                    ans[number_1.size() + number_2.size() - i - j - 2]++;
                }
            }
        }

        for (int i = 0; i < ans.size() - 1; i++){
            ans[i + 1] += ans[i] / 2;
            ans[i] %= 2;
        }

        // for (int i = 0; i < number_1.size(); i++)
        //     std::cout << number_1[i];
        // std::cout << "\n";

        // for (int i = 0; i < number_2.size(); i++)
        //     std::cout << number_2[i];
        // std::cout << "\n";

        for (int i = 0; i < ans.size(); i++)
            std::cout << ans[i];
        std::cout << "\n";

        int extra = 0;
        reverse(ans.begin(), ans.end());
        while(ans.size() && ans.back() == 0){
            ans.pop_back();
        }

        
        
        while(ans.size() && ans.back() == 0){
            ans.pop_back();
            
        }
        
        std::cout << extra << "\n";
        int size_acur = accuracy.size() + other.accuracy.size();
        std::vector <int> acur;
        std::vector <int> dig;
        for (int i = ans.size() - size_acur; i < ans.size(); i++)
            acur.push_back(ans[i]);
        
        for (int i = 0; i < ans.size() - size_acur; i++)
            dig.push_back(ans[i]);
        return bignumber(dig, acur, sign * other.sign);

    }

    bignumber operator - (const bignumber &other) const {
        if (sign != other.sign) {
            return *this + other;
        }

        std::vector <int> number_1;
        std::vector <int> number_2;

        for (int i = 0; i < digits.size(); i++)
            number_1.push_back(digits[i]);
        for (int i = 0; i < accuracy.size(); i++)
            number_1.push_back(accuracy[i]);

        for (int i = 0; i < other.digits.size(); i++)
            number_2.push_back(other.digits[i]);
        for (int i = 0; i < accuracy.size(); i++)
            number_2.push_back(other.accuracy[i]);
        

    }
    bignumber& bignumber::operator += (const bignumber &other) {
        return *this = *this + other;
    }
    bignumber& bignumber::operator *= (const bignumber &other) {
        return *this = *this * other;
    }
    bool is_zero (const bignumber) const{
        return digits.size() == 1 && accuracy.size() == 0 && digits[0] == 0;
    }
    bool operator == (const bignumber &other) const {
        if (is_zero(*this) && is_zero(other))
            return 1;
        if (digits.size() != other.digits.size() || accuracy.size() != other.accuracy.size() || sign != other.sign)
            return 0;
        for (int i = 0; i < digits.size(); i++) 
            if (digits[i] != other.digits[i])
                return 0;
        
        for (int i = 0; i < accuracy.size(); i++) 
            if (accuracy[i] != other.accuracy[i])
                return 0;
        
        return 1;
    }
    bool operator != (const bignumber &other) const {
        return !(*this == other);
    }
    bool operator < (const bignumber &other) const {
        if (sign != other.sign) {


            
        }

        if (digits.size() < other.digits.size())
            return 0;
        else if (digits.size() < other.digits.size())
            return 1;
        
    }

};



std::ostream& operator << (std::ostream& out, const bignumber& t){
	for (int i = 0; i < t.digits.size(); i++) 
        out << t.digits[i];

    out << '.';
    
    for (int i = 0; i < t.accuracy.size(); i++) 
        out << t.accuracy[i];
    
	return out;
}


int main(){
    std::string s1 = "101"; //5,328125
    std::string s2 = "1111.000001"; // 15,125
    bignumber a1(s1);
    bignumber a2(s2);
    std::cout << a1 * a2;
}

// if (now.size() - i < max(accuracy, other.accuracy)) {
//                 int digit = number[number.size() - i - 1];
//                 digit +=
//             }

// int diff = accuracy - other.accuracy;
//         int min_accur = min(accuracy, other.accuracy);

//         if (diff > 0)
//             for (int i = 0; i < accuracy; i++)
//                 now.push_back(number[number.size() - i - 1]);
//         else if (diff < 0)
//             for (int i = 0; i < other.accuracy; i++)
//                 now.push_back(other.number[other.number.size() - i - 1]);


//         int extra_digit = 0;
//         for (int i = 0; i < max(digits, other.digits) + min_accur; i++) {
//             if (number[digits + min_accur - i - 1] == '.') {
//                 now.push_back('.');
//                 continue;
//             }

//             int now_digit = extra_digit;
//             if (digits + min_accur - i  > 0) 
//                 now_digit += number[digits + min_accur - i - 1] - '0';

//             if (other.digits + min_accur - i  > 0)
//                 now_digit += other.number[other.digits + min_accur - i - 1] - '0';
            
//             if (now_digit > 1) {
//                 now_digit -= 2;
//                 extra_digit = 1;
//             }
//             else {
//                 extra_digit = 0;
//             }
//             now.push_back(now_digit + '0');
//         }
//         if (extra_digit) {
//             now.push_back('1');
//         }
//         reverse(now.begin(), now.end());
//         return bignumber(now);


    // int dig = 0, accur = 0;
    //         number = str;
    //         for (int i = 0; i < str.size(); i++) {
    //             if (str[i] != '.')
    //                 dig++;
    //             else
    //                 break;
    //         }
    //         accur = str.size() - dig;
    //         digits = dig;
    //         accuracy = accur;