//
// Created by Artem on 03.11.2025.
//

#include "RationalNumber.h"

RationalNumber::RationalNumber(long long numeratorA, long long denominatorA) {
    this->numerator = new IntegerNumber(numeratorA);
    this->denominator = new NaturalNumber(denominatorA);
}

RationalNumber::RationalNumber(const std::string &numeratorA, const std::string &denominatorA) {
    this->numerator = new IntegerNumber(numeratorA);
    this->denominator = new NaturalNumber(denominatorA);
}

std::string RationalNumber::toString() {
    return this->numerator->toString() + "/" + this->denominator->toString();
}

const IntegerNumber &RationalNumber::getIntegerNumerator() noexcept {
    return *this->numerator;
}

const NaturalNumber &RationalNumber::getNaturalDenominator() noexcept {
    return *this->denominator;
}

RationalNumber::RationalNumber(const std::string &s) {
    size_t delimiterPos = s.find('/');
    std::string numeratorS = s.substr(0, delimiterPos);
    std::string denominatorS = s.substr(delimiterPos + 1);
    this->numerator = new IntegerNumber(numeratorS);
    this->denominator = new NaturalNumber(denominatorS);
}


