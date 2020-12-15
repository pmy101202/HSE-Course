#ifndef BIGINTEGER_H_INCLUDED
#define BIGINTEGER_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>

class BigInteger{
private:
    std::vector<int> digits;//Разряды числа
    bool sign;//Знак
    void cutzeros();//Обрезает ведущие нули и убирает минус у нуля
    BigInteger(bool s,const std::vector<int>& d);//Техничесикй конструктор с лобовой инициализацией переменных

public:
    static const int MOD = 1000000000;//Просто константа для взятия модуля
    BigInteger();//Создаёт 0
    BigInteger(long long x);//Создаёт из long long и всё что в него расширяется
    BigInteger(const BigInteger& x);//Конструктор копий
    BigInteger(std::string x);//Конструктор из строки (а int так не умеет)
    ~BigInteger();//Деструктор
    std::string to_string() const;//Перевод в string
    BigInteger& operator=(const BigInteger& x);//Оператор присваивания
    //Блок сравнений
    bool operator== (const BigInteger& x) const;
    bool operator!= (const BigInteger& x) const;
    bool operator< (const BigInteger& x) const;
    bool operator> (const BigInteger& x) const;
    bool operator<= (const BigInteger& x) const;
    bool operator>= (const BigInteger& x) const;
    bool absGreater(const BigInteger& x) const;
    //Блок инкрементов и декрементов
    BigInteger& operator++ ();
    BigInteger operator++ (int);
    BigInteger& operator-- ();
    BigInteger operator-- (int);
    //Блок арифметики
    BigInteger operator- () const;
    BigInteger operator+ (const BigInteger& x) const;
    BigInteger operator- (const BigInteger& x) const;
    BigInteger operator* (const BigInteger& x) const;
    BigInteger operator/ (const BigInteger& x) const;
    BigInteger operator% (const BigInteger& x) const;
    //Блок присваивательной арифметики
    BigInteger& operator+= (const BigInteger& x);
    BigInteger& operator-= (const BigInteger& x);
    BigInteger& operator*= (const BigInteger& x);
    BigInteger& operator/= (const BigInteger& x);
    BigInteger& operator%= (const BigInteger& x);

    friend BigInteger abs(const BigInteger x);
};

std::ostream &operator<<(std::ostream& str, const BigInteger& x);
std::istream &operator>>(std::istream& str, BigInteger& x);

BigInteger abs(const BigInteger x);

#endif // BIGINTEGER_H_INCLUDED
