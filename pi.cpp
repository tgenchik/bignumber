#include "LongNumber.hpp"
#include <iostream>
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
int main () {
    return 0;
}
