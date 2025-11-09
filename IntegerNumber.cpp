//
// Created by Artem on 02.11.2025.
//

#include "IntegerNumber.h"
#include "Exceptions/UniversalStringException.h"

bool IntegerNumber::isNegative() const noexcept {
    return this->isNegativeFlag;
}

IntegerNumber::IntegerNumber(const std::string &s) {
    if (s.empty())
        throw UniversalStringException("wrong argument, the string of numbers should not be empty");
    this->isNegativeFlag = s[0] == '-';
    if (isNegativeFlag)
        this->number = new NaturalNumber(s.substr(1));
    else
        this->number = new NaturalNumber(s);
}

IntegerNumber::IntegerNumber(long long int a) {
    this->isNegativeFlag = a < 0;
    this->number = new NaturalNumber(isNegativeFlag ? a*(-1) : a);
}

std::string IntegerNumber::toString() const {
    return (isNegativeFlag ? "-" : "") + this->number->toString();
}

const std::vector<uint8_t>& IntegerNumber::getNumbers() const noexcept {
    return this->number->getNumbers();
}

// Z-8: Умножение целых чисел.
IntegerNumber IntegerNumber::multiply(const IntegerNumber &other) const {
    // getSign() дает ноль, если число равно нулю. Поэтому юзаю его.
    // Тут простая проверка, если первое или второе число ноль - умножение равно нулю.
    uint8_t numberSign = this->getSign();
    uint8_t otherSign = other.getSign();
    if (numberSign == 0 || otherSign == 0) {
        return IntegerNumber("0");
    }

    // Берем модуль числа для умножения и умножаем числа.
    NaturalNumber numberAbs = this->abs();
    NaturalNumber otherAbs = other.abs();
    NaturalNumber multiplyAbs = numberAbs.multiply(otherAbs);

    // Вспоминаем, какой знак был у нашего числа.
    // Отрицательное, если знаки у обоих чисел не одинаковые.
    bool resultIsNegative = numberSign != otherSign;

    return IntegerNumber(multiplyAbs.getNumbers(), resultIsNegative);
};

NaturalNumber IntegerNumber::abs() {
    return NaturalNumber(*this->number);
}

uint8_t IntegerNumber::getSign() {
    if (this->number->isEqualZero()) {
        return 0;
    }
    return this->isNegativeFlag ? 1 : 2;
}

IntegerNumber IntegerNumber::negate() {
    return IntegerNumber(*this->number, !this->isNegativeFlag);
}

IntegerNumber IntegerNumber::toInteger(const NaturalNumber& other) {
    return IntegerNumber(other.getNumbers(), false);
}

NaturalNumber IntegerNumber::toNatural(const IntegerNumber& other) {
    if (other.isNegativeFlag) {
        throw UniversalStringException("to convert an integer to a natural, it must be greater than or equal to 0.");
    }
    return NaturalNumber(*other.number); 
}

IntegerNumber IntegerNumber::add(const IntegerNumber& other) {
    NaturalNumber absThis = this->abs();
    NaturalNumber absOther = other.abs();
    size_t maxSize = std::max(absThis.getNumbers().size(), absOther.getNumbers().size());
    std::vector<uint8_t> resultNumbers(maxSize + 1, 0);

    if (this->getSign() == other.getSign()) {
        NaturalNumber sum = absThis.add(absOther);
        bool isNeg = this->isNegativeFlag;
        return IntegerNumber(sum.getNumbers(), isNeg);
    } else {
        uint8_t cmp = absThis.cmp(&absOther);
        if (cmp == 0) {
           return IntegerNumber(std::vector<uint8_t>{0}, false);
        } else if (cmp == 2) {
            NaturalNumber diff = absThis.subtract(absOther);
            return IntegerNumber(diff.getNumbers(), this->isNegativeFlag);
        } else {
            NaturalNumber diff = absOther.subtract(absThis);
            return IntegerNumber(diff.getNumbers(), other.isNegativeFlag);
        }
   }
}

IntegerNumber IntegerNumber::subtract(const IntegerNumber& other) {
    IntegerNumber negOther = other.negate();
    return this->add(negOther);
}
