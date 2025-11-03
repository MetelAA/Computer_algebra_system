//
// Created by Artem on 02.11.2025.
//

#ifndef DMATGCOLLOQUIUM_NATURALNUMBER_H
#define DMATGCOLLOQUIUM_NATURALNUMBER_H

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>

class NaturalNumber {
public:

    explicit NaturalNumber(const std::vector<uint8_t> &CpNumbers);
    NaturalNumber(unsigned long long a); //решение для облегченного тестирования, потом будет выпелено
    NaturalNumber(const std::string& a); //основной конструктор

    NaturalNumber(const NaturalNumber& other) : numbers(other.numbers) {}
    NaturalNumber(NaturalNumber&& other) noexcept : numbers(std::move(other.numbers)) {
        other.numbers = {0};
    }

    NaturalNumber& operator=(const NaturalNumber& other) {
        if (this != &other) {
            numbers = other.numbers;
        }
        return *this;
    }
    NaturalNumber& operator=(NaturalNumber&& other) noexcept {
        if (this != &other) {
            numbers = std::move(other.numbers);
        }
        return *this;
    }

    std::string toString() noexcept;
    const std::vector<uint8_t>& getNumbers() noexcept;


private:
    std::vector<uint8_t> numbers;
};


#endif //DMATGCOLLOQUIUM_NATURALNUMBER_H
