#include <iostream>
#include <vector>

#include "NaturalNumber.h"
#include "IntegerNumber.h"
#include "RationalNumber.h"
#include "Polynomial.h"

int main() {
    std::vector<std::string> vec;

    vec.emplace_back("4/3");
    vec.emplace_back("3/1");
    vec.emplace_back("5/7");
    Polynomial polynomial(vec);

    std::vector<Polynomial::rationalSupport> vec2 = { {3, 4}, {-2, 1}, {2, 5} };
    Polynomial polynomial2(vec2);
    std::cout << polynomial2.toString();

//    std::vector<int> original = {1, 2, 3};
//    std::vector<int> reversed;
//    reversed.assign(original.rbegin(), original.rend());
//
//    for (int i = 0; i < reversed.size(); ++i) {
//        std::cout << reversed.at(i) << " ";
//
//    }

}
