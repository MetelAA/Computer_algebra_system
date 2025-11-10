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

Polynomial Polynomial::add(const Polynomial& other) const {
    const std::vector<RationalNumber>& longer  = (this->coefficients.size() >= other.coefficients.size())
        ? this->coefficients
        : other.coefficients;
    const std::vector<RationalNumber>& shorter = (this->coefficients.size() >= other.coefficients.size())
        ? other.coefficients
        : this->coefficients;

    std::vector<RationalNumber> resultCoeffs;
    resultCoeffs.reserve(longer.size());

    std::size_t diff = longer.size() - shorter.size();

    for (std::size_t i = 0; i < diff; ++i) {
        resultCoeffs.push_back(longer[i]);
    }

    for (std::size_t i = diff; i < longer.size(); ++i) {
        RationalNumber sum = longer[i].add(shorter[i - diff]);
        resultCoeffs.push_back(sum);
    }

    return Polynomial(resultCoeffs);
}

Polynomial Polynomial::subtract(const Polynomial& other) const {
    const std::vector<RationalNumber>& longer  = (this->coefficients.size() >= other.coefficients.size())
        ? this->coefficients
        : other.coefficients;
    const std::vector<RationalNumber>& shorter = (this->coefficients.size() >= other.coefficients.size())
        ? other.coefficients
        : this->coefficients;

    std::vector<RationalNumber> resultCoeffs;
    resultCoeffs.reserve(longer.size());

    std::size_t diff = longer.size() - shorter.size();

    bool thisIsLonger = (this->coefficients.size() >= other.coefficients.size());

    for (std::size_t i = 0; i < diff; ++i) {
        if (thisIsLonger)
            resultCoeffs.push_back(longer[i]);
        else
            resultCoeffs.push_back(RationalNumber(0, 1).subtract(longer[i]));
    }

    for (std::size_t i = diff; i < longer.size(); ++i) {
        RationalNumber first_value = thisIsLonger ? longer[i] : RationalNumber(0, 1);
        RationalNumber second_value = thisIsLonger ? shorter[i - diff] : longer[i - diff];
        RationalNumber res_value = thisIsLonger ? first_value.subtract(second_value) : second_value.subtract(first_value);
        resultCoeffs.push_back(res_value);
    }

    return Polynomial(resultCoeffs);
}