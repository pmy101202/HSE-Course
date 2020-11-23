#include <biginteger.h>

void BigInteger::cutzeros(){
    while (digits.back()==0&&digits.size()>1)
        digits.pop_back();
    if (digits.size()==1&&digits[0]==0) sign = false;
}

BigInteger::BigInteger(bool s,const std::vector<int>& d):sign(s),digits(d){
}

BigInteger::BigInteger(){
    digits = std::vector<int>(1,0);
    sign = false;
}

BigInteger::BigInteger(long long x){
    sign = (x<0);
    digits = std::vector<int>();
    if (x<0) x=-x;
    if (x==0) digits.push_back(0);
    while (x>0){
        digits.push_back(x%MOD);
        x /= MOD;
    }
}

BigInteger::BigInteger(const BigInteger& x){
    sign = x.sign;
    digits = x.digits;
}

BigInteger::BigInteger(std::string x){
    digits = std::vector<int>();
    if (x[0]=='-'){
        sign = true;
        x = x.substr(1,x.size()-1);
    } else if (x[0]=='+'){
        sign = false;
        x = x.substr(1,x.size()-1);
    } else sign = false;
    for (int i = 0; i<x.size(); ++i){
        if (x[i]<'0'||x[i]>'9') throw std::runtime_error("Not-a-number was inputed");
    }
    for (int i = 0; i<x.size()/2; ++i)
        std::swap(x[i],x[x.size()-1-i]);
    if (x=="0") sign = false;
    while (x!=""){
        std::string s = x.substr(0,std::min(9,(int)x.size()));
        for (int i = 0; i<s.size()/2; ++i)
            std::swap(s[i],s[s.size()-1-i]);
        digits.push_back(stoi(s));
        if (x.size()>9)
            x = x.substr(9,x.size()-9);
        else
            x = "";
    }
}

BigInteger::~BigInteger(){};

std::string BigInteger::to_string() const{
    std::string x = "";
    std::string s = "";
    if (sign) x = "-";
    x += std::to_string(digits.back());
    for (int i = digits.size()-2; i>=0; --i){
        s = std::to_string(digits[i]);
        while (s.size()<9) s = '0'+s;
        x+=s;
    }
    return x;
}

BigInteger& BigInteger::operator=(const BigInteger& x){
    sign = x.sign;
    digits = x.digits;
    return *this;
}

bool BigInteger::operator== (const BigInteger& x) const{
    return (sign==x.sign)&&(digits==x.digits);
}

bool BigInteger::operator!= (const BigInteger& x) const{
    return !(*this==x);
}

bool BigInteger::operator< (const BigInteger& x) const{
    if (sign&&!x.sign) return true;
    if (!sign&&x.sign) return false;
    if (sign&&x.sign) return !(abs(*this)<abs(x));
    if (digits.size()<x.digits.size()) return true;
    if (digits.size()>x.digits.size()) return false;
    for (int i = digits.size()-1; i>=0; ++i){
        if (digits[i]<x.digits[i]) return true;
        if (digits[i]>x.digits[i]) return false;
    }
    return false;
}

bool BigInteger::operator> (const BigInteger& x) const{
    return !(*this<x)&&(*this!=x);
}

bool BigInteger::operator<= (const BigInteger& x) const{
    return !(*this>x);
}

bool BigInteger::operator>= (const BigInteger& x) const{
    return !(*this<x);
}

BigInteger BigInteger::operator- () const{
    return BigInteger(!sign,digits);
}

BigInteger BigInteger::operator+ (const BigInteger& x) const{
    if (!sign&&!x.sign){
        BigInteger y(0);
        std::vector<int> d1 = digits, d2 = x.digits;
        y.digits.resize(1+std::max(d1.size(),d2.size()),0);
        d1.resize(y.digits.size()-1,0);
        d2.resize(y.digits.size()-1,0);
        for (int i = 0; i<d1.size(); ++i){
            y.digits[i]+=(y.digits[i]+d1[i]+d2[i])%MOD;
            y.digits[i+1]+=(y.digits[i]+d1[i]+d2[i])/MOD;
        }
        y.cutzeros();
        return y;
    }
    if (!sign&&x.sign){
        if (*this>=abs(x)){
            std::vector<int> d1 = digits, d2 = x.digits;
            d1.resize(std::max(d1.size(),d2.size()),0);
            d2.resize(std::max(d1.size(),d2.size()),0);
            for (int i = 0; i<d1.size(); ++i){
                d1[i]-=d2[i];
                if (d1[i]<0){
                    d1[i]+=MOD;
                    --d1[i+1];
                }
            }
            BigInteger y(false,d1);
            y.cutzeros();
            return y;
        } else {
            return -(-x-*this);
        }
    }
    if (sign&&!x.sign)
        return x+*this;
    if (sign&&x.sign)
        return -(-*this+(-x));
}

BigInteger BigInteger::operator- (const BigInteger& x) const{
    return *this+(-x);
}

BigInteger BigInteger::operator* (const BigInteger& x) const{
    if (sign&&x.sign) return (-*this)*(-x);
    if (sign&&!x.sign) return -((-*this)*x);
    if (!sign&&x.sign) return -(*this*(-x));
    if (x==0) return 0;
    if (x%2==0){
        BigInteger y = *this*(x/2);
        return y+y;
    } else {
        BigInteger y = *this*(x/2);
        return y+y+*this;
    }
}

BigInteger BigInteger::operator/ (const BigInteger& x) const{
    BigInteger y(*this);
    if (sign&&x.sign) return (-*this)/(-x);
    if (sign&&!x.sign) return -((-*this)/x);
    if (!sign&&x.sign) return -(*this/(-x));
    if (*this==0) return 0;
    if (x==0) throw std::runtime_error("Dividing by zero");
    if (x==2){
        for (int i = 0; i<y.digits.size()-1; ++i)
            y.digits[i] = y.digits[i+1]%2*MOD+y.digits[i]/2;
        y.digits.back()=y.digits.back()/2;
        y.cutzeros();
        return y;
    }
    BigInteger l(0), r(*this+1), m;
    while (r-l>1){
        m = (l+r)/2;
        if (m*x>*this)
            r = m;
        else
            l = m;
    }
    return l;
}

BigInteger BigInteger::operator% (const BigInteger& x) const{
    if (x==2) return digits[0]%2;
    if (*this==0) return 0;
    if (x==0) throw std::runtime_error("Dividing by zero");
    return *this-x*(*this/x);
}

BigInteger& BigInteger::operator++ (){
    return *this+=1;
}

BigInteger BigInteger::operator++ (int){
    BigInteger x(*this);
    *this+=1;
    return x;
}

BigInteger& BigInteger::operator-- (){
    return *this-=1;
}

BigInteger BigInteger::operator-- (int){
    BigInteger x(*this);
    *this-=1;
    return x;
}

BigInteger& BigInteger::operator+= (const BigInteger& x){
    *this = *this+x;
    return *this;
}

BigInteger& BigInteger::operator-= (const BigInteger& x){
    *this = *this-x;
    return *this;
}

BigInteger& BigInteger::operator*= (const BigInteger& x){
    *this = *this*x;
    return *this;
}

BigInteger& BigInteger::operator/= (const BigInteger& x){
    *this = *this/x;
    return *this;
}

BigInteger& BigInteger::operator%= (const BigInteger& x){
    *this = *this%x;
    return *this;
}

std::ostream &operator<<(std::ostream& str, const BigInteger& x){
    str << x.to_string();
    return str;
};

std::istream &operator>>(std::istream& str, BigInteger& x){
    std::string s;
    str >> s;
    x = s;
    return str;
}

BigInteger abs(const BigInteger x){
    if (x.sign) return -x;
    return x;
}
