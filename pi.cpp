#include "LongNumber.hpp"
#include <iostream>
#include <chrono>

LongNumber makePI(int acur) {
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

int main(int argc, char *argv[]) {
    int dec_precision{100};

    if(argc == 2) {
        try {
            dec_precision = std::stoi(argv[1]);
        }
        catch(...) {
            std::cerr << "Conversion error\n";
            return EXIT_FAILURE;
        }
    }

    if(dec_precision < 0) {
        std::cerr << "Negative precision\n";
        return EXIT_FAILURE;
    }


    auto start{ std::chrono::high_resolution_clock::now() };
    LongNumber pi = makePI(dec_precision);
    auto end{ std::chrono::high_resolution_clock::now() };
    auto duration { std::chrono::duration_cast<std::chrono::milliseconds>(end - start) };
    
    std::cout << "First " << dec_precision << " digits after the decimal point of pi are:\n";
    std::cout << pi.toString(dec_precision) << "\n\n";
    std::cout << "Computed in: " << duration << '\n';

    return 0;
}
