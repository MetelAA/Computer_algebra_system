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

void RationalNumber::reduce() {
    NaturalNumber numeratorAbs = this->numerator->abs();
    NaturalNumber gcd = numeratorAbs.GCD(*this->denominator);

    const std::vector<uint8_t> &gcdDigits = gcd.getNumbers();
    size_t digitsCount = gcdDigits.size();
    if (digitsCount == 1) {
        if (gcdDigits[0] == 1) {
            return;
        }
    }

    IntegerNumber reducedNumerator = this->numerator->quotient(gcd);
    NaturalNumber denominator = *this->denominator;
    NaturalNumber reducedDenominator = denominator.quotient(gcd);
    
    delete this->numerator;
    delete this->denominator;

    this->numerator = new IntegerNumber(reducedNumerator);
    this->denominator = new NaturalNumber(reducedDenominator);
}

bool RationalNumber::isInteger() {
    NaturalNumber denominator = *this->denominator;
    const std::__1::vector<uint8_t> &denomDigits = denominator.getNumbers();

    if (denomDigits.size() == 1) {
        if (denomDigits[0] == 1) {
            return true;
        }
    }

    return false;
}

RationalNumber RationalNumber::fromInteger(const IntegerNumber &other) {
    NaturalNumber denominator(1);

    return RationalNumber(other, denominator);
}