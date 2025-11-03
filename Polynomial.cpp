//
// Created by Artem on 03.11.2025.
//

#include "Polynomial.h"
#include "Exceptions/UniversalStringException.h"



const std::vector<RationalNumber>& Polynomial::getCoefficients() noexcept {
    return this->coefficients;
}

std::string Polynomial::toString() {
    if (this->coefficients.empty())
        throw UniversalStringException("atypical behavior, the vector of coefficients should not be empty");
    std::string result;
    for (int i = this->coefficients.size() - 1; i >= 0; --i) {
        result += this->coefficients.at(i).toString() + "x^" + std::to_string(i);
        if (i!=0)
            result += " + ";
    }
    return result;
}

Polynomial::Polynomial(const std::vector<std::string>& coefficientsA) {
    if (coefficientsA.empty())
        throw UniversalStringException("wrong argument, the string of numbers should not be empty");
    std::size_t i = coefficientsA.size() - 1;
    while (true) {
        this->coefficients.emplace_back(RationalNumber(coefficientsA[i]));
        if (i != 0)
            i--;
        else
            break;
    }
}

Polynomial::Polynomial(const std::vector<rationalSupport> &coefficientsA) {
    if (coefficientsA.empty())
        throw UniversalStringException("wrong argument, the string of numbers should not be empty");
    std::size_t i = coefficientsA.size() - 1;
    while (true) {
        this->coefficients.emplace_back(RationalNumber(coefficientsA[i].numerator, coefficientsA[i].denominator));
        if (i != 0)
            i--;
        else
            break;
    }
}

