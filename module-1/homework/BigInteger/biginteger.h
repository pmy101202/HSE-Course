#ifndef BIGINTEGER_H_INCLUDED
#define BIGINTEGER_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>

class BigInteger{
private:
    std::vector<int> digits;//Ðàçðÿäû ÷èñëà
    bool sign;//Çíàê
    void cutzeros();//Îáðåçàåò âåäóùèå íóëè è óáèðàåò ìèíóñ ó íóëÿ
    BigInteger(bool s,const std::vector<int>& d);//Òåõíè÷åñèêé êîíñòðóêòîð ñ ëîáîâîé èíèöèàëèçàöèåé ïåðåìåííûõ

public:
    static const int MOD = 1000000000;//Ïðîñòî êîíñòàíòà äëÿ âçÿòèÿ ìîäóëÿ
    BigInteger();//Ñîçäà¸ò 0
    BigInteger(long long x);//Ñîçäà¸ò èç long long è âñ¸ ÷òî â íåãî ðàñøèðÿåòñÿ
    BigInteger(const BigInteger& x);//Êîíñòðóêòîð êîïèé
    BigInteger(std::string x);//Êîíñòðóêòîð èç ñòðîêè (à int òàê íå óìååò)
    ~BigInteger();//Äåñòðóêòîð
    std::string to_string() const;//Ïåðåâîä â string
    BigInteger& operator=(const BigInteger& x);//Îïåðàòîð ïðèñâàèâàíèÿ
    //Áëîê ñðàâíåíèé
    bool operator== (const BigInteger& x) const;
    bool operator!= (const BigInteger& x) const;
    bool operator< (const BigInteger& x) const;
    bool operator> (const BigInteger& x) const;
    bool operator<= (const BigInteger& x) const;
    bool operator>= (const BigInteger& x) const;
    //Áëîê èíêðåìåíòîâ è äåêðåìåíòîâ
    BigInteger& operator++ ();
    BigInteger operator++ (int);
    BigInteger& operator-- ();
    BigInteger operator-- (int);
    //Áëîê àðèôìåòèêè
    BigInteger operator- () const;
    BigInteger operator+ (const BigInteger& x) const;
    BigInteger operator- (const BigInteger& x) const;
    BigInteger operator* (const BigInteger& x) const;
    BigInteger operator/ (const BigInteger& x) const;
    BigInteger operator% (const BigInteger& x) const;
    //Áëîê ïðèñâàèâàòåëüíîé àðèôìåòèêè
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
