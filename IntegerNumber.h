    //
    // Created by Artem on 02.11.2025.
    //

    #ifndef DMATGCOLLOQUIUM_INTEGERNUMBER_H
    #define DMATGCOLLOQUIUM_INTEGERNUMBER_H

    #include <cstdint>
    #include "NaturalNumber.h"

    class IntegerNumber {
    public:
        IntegerNumber(const std::vector<uint8_t>& numbers, bool isNegative): isNegativeFlag(isNegative){
            this->number = new NaturalNumber(numbers);
        };
        IntegerNumber(const std::string& s); //основной конструктор
        IntegerNumber(long long a); //решение для облегченного тестирования, потом будет выпелено

        IntegerNumber(const IntegerNumber& other): isNegativeFlag(other.isNegativeFlag), number(new NaturalNumber(*other.number)) {}
        IntegerNumber(IntegerNumber&& other) noexcept: isNegativeFlag(other.isNegativeFlag), number(other.number) {other.number = nullptr;}

        IntegerNumber& operator=(const IntegerNumber& other) {
            if (this != &other) {
                delete this->number;
                this->number = new NaturalNumber(*other.number);
                this->isNegativeFlag = other.isNegativeFlag;
            }
            return *this;
        }
        IntegerNumber& operator=(IntegerNumber&& other) noexcept {
            if (this != &other) {
                delete this->number;
                this->number = other.number;
                this->isNegativeFlag = other.isNegativeFlag;
                other.number = nullptr;
            }
            return *this;
        }

        ~IntegerNumber() {
            delete this->number;
        }


        bool isNegative() noexcept;
        std::string toString();
        const std::vector<uint8_t>& getNumbers() noexcept;


    private:
        NaturalNumber *number;
        bool isNegativeFlag;
    };


    #endif //DMATGCOLLOQUIUM_INTEGERNUMBER_H
