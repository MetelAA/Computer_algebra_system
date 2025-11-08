#include "Polynomial.h"

// P-10 Остаток от деления полиномов
// Касимова Варвара 4385
Polynomial::Polynomial remainder(const Polynomial& other) const {
    // Находим неполное частное от деления
    Polynomial incomplete_quotient = this->quotient(other);
    // Умножаем неполное частное на делитель
    Polynomial product = incomplete_quotient.multiply(other);
    // Вычитаем из исходного полинома произведение, получаем остаток от деления
    return this->subtract(product);
};

// P-11 НОД полиномов
// Касимова Варвара 4385
Polynomial::Polynomial GCD(const Polynomial& other) const {
    // Инициализируем 2 полинома для применения к ним алгоритма Евклида
    Polynomial* polynom1 = new Polynomial(*this);
    Polynomial* polynom2 = new Polynomial(other);
    // Находим остаток от деления первого на второй
    Polynomial* remainder = new Polynomial(this->remainder(other));

    // Пока остаток не станет равен 0, то есть пока количетво коэффициентов больше 1
    // Или пока единственный коэффициент не 0, применяем алгоритм Евклида
    while(!(remainder->coefficients.size() == 1 && 
            remainder->coefficients[0].numerator->getSign() == 0)){
        // Очищаем память от первого полинома, его мы уже обработали
        delete polynom1;
        // Новыми данными для применения алгоритма становятся 
        // второй полином и остаток от деления первого на второй
        polynom1 = polynom2;
        polynom2 = remainder_ptr;
        // Вычисляем новый остаток
        remainder = new Polynomial(polynom1->remainder(*polynom2));
    }

    // Сохраняем НОД, это предпоследий остаток, 
    // то есть тот полином, на который делили в последний раз
    Polynomial gcd = Polynomial(*polynom2);

    // Так как все полиномы делятся на константу, и она не несет смысловой нагрузки,
    // сделаем многочлен приведенным (старший коэффициент 1)
    // Для этого нужно поделить на старший коэффицинет или умножить на обратный к нему
    RationalNumber highest_coeff = polynom2->coefficients[polynom2->getDegree()];
    RationalNumber unit = RationalNumber(IntegerNumber({1}, false), NaturalNumber({1}));
    RationalNumber anti_highest_coeff = unit.division(highest_coeff);

    gcd = gcd.multiplyByRational(anti_highest_coeff);

    // Очищаем память
    delete polynom1;
    delete polynom2;
    delete remainder;

    return gcd;
};

// P-12 Производная полинома
// Касимова Варвара 4385
Polynomial::Polynomial derivative() const {
    // Создаем новый элемент дляхранения производной
    Polynomial* derivative = new Polynomial(*this);
    // Начиная с 1 степени переменной, перебираем все коэффициенты
    for(size_t i = 1; i < this->coefficients.size(); i++){
        // Переводим показатель степени в дробное представление 
        std::string str = std::to_string(i) + "/1";
        RationalNumber power = RationalNumber(str);
        // Так как при дифференцировании степень переменной понижается,
        // результат умножения коэффициента на показатель степени записываем 
        // в ячейку, соответствующую меньшей степени переменной
        derivative.coefficients[i - 1] = this->coefficients[i].multiply(power);
    }
    // так как копировали исходный полином, а степень производной на 1 меньше,
    // последняя ячейка, которая соответствует старшему коэффициенту, больше не нужна
    derivative->pop_back();
    return derivative;
};

// P-13 Многочлен с корнями 1 кратности
// Касимова Варвара 4385
Polynomial::Polynomial makeSquareFree() const {
    // Найдем производную полинома
    Polynomial derivative = this->derivative();
    // НОД полином и его производной будет содеражть все кратные корни
    Polynomial gcd = GCD(derivative);
    // Поделим на НОД, чтобы остались только корни кратности 1
    return derivative.remainder(gcd);
};
