#ifndef BIGINTEGER_H_INCLUDED
#define BIGINTEGER_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>

class BigInteger{
private:
    std::vector<int> digits;//������� �����
    bool sign;//����
    void cutzeros();//�������� ������� ���� � ������� ����� � ����
    BigInteger(bool s,const std::vector<int>& d);//����������� ����������� � ������� �������������� ����������

public:
    static const int MOD = 1000000000;//������ ��������� ��� ������ ������
    BigInteger();//������ 0
    BigInteger(long long x);//������ �� long long � �� ��� � ���� �����������
    BigInteger(const BigInteger& x);//����������� �����
    BigInteger(std::string x);//����������� �� ������ (� int ��� �� �����)
    ~BigInteger();//����������
    std::string to_string() const;//������� � string
    BigInteger& operator=(const BigInteger& x);//�������� ������������
    //���� ���������
    bool operator== (const BigInteger& x) const;
    bool operator!= (const BigInteger& x) const;
    bool operator< (const BigInteger& x) const;
    bool operator> (const BigInteger& x) const;
    bool operator<= (const BigInteger& x) const;
    bool operator>= (const BigInteger& x) const;
    bool absGreater(const BigInteger& x) const;
    //���� ����������� � �����������
    BigInteger& operator++ ();
    BigInteger operator++ (int);
    BigInteger& operator-- ();
    BigInteger operator-- (int);
    //���� ����������
    BigInteger operator- () const;
    BigInteger operator+ (const BigInteger& x) const;
    BigInteger operator- (const BigInteger& x) const;
    BigInteger operator* (const BigInteger& x) const;
    BigInteger operator/ (const BigInteger& x) const;
    BigInteger operator% (const BigInteger& x) const;
    //���� ���������������� ����������
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
