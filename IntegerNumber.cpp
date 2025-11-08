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
}

//Z9: Частное от деления целого на целое (делитель отличен от нуля)
IntegerNumber IntegerNumber::quotient(const IntegerNumber &other) const {
    if (other.getSign() == 0) {
        throw UniversalStringException("you cannot divide by zero");
    }

    NaturalNumber dividend = this->abs();
    const NaturalNumber divisor = other.abs();

    if (dividend.cmp(&divisor) == 1) { // divisor > dividend => поделить не можем, вернем 0
        return IntegerNumber(std::vector<uint8_t>{0}, false);
    }

    IntegerNumber quotient(std::vector<uint8_t>{0}, false); // делаем нулевой контейнер для подсчета ответа

    while (dividend.cmp(&divisor) % 2 == 0) { // пока так, позже прикручу бинпоиск, будет log n
        dividend = dividend.subtract(divisor);
        quotient = quotient.add(IntegerNumber(std::vector<uint8_t>{1}, false));
    }

    return this->getSign() != other.getSign() ? quotient.negate() : quotient;
}

//Z10: Остаток от деления целого на целое(делитель отличен от нуля)
IntegerNumber IntegerNumber::remainder(const IntegerNumber &other) const {
    if (other.getSign() == 0) {
        throw UniversalStringException("you cannot divide by zero");
    }

    const NaturalNumber dividend_abs = this->abs();
    const NaturalNumber divisor_abs = other.abs();

    if (dividend_abs.cmp(&divisor_abs) == 1) {
        return *this;
    }

    IntegerNumber dividend(*this);
    IntegerNumber divisor(other);

    if (dividend.getSign() == 1) dividend = dividend.negate();
    if (divisor.getSign() == 1) divisor = divisor.negate();

    const IntegerNumber quotient = dividend.quotient(divisor);
    const IntegerNumber product = divisor.multiply(quotient);

    return IntegerNumber(dividend.subtract(product).getNumbers(), this->getSign());;
}
