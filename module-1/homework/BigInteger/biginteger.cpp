#include "biginteger.h"

std::vector<int> operator+ (std::vector<int> a, std::vector<int> b){
    for (int i = 0; i<b.size(); ++i)
        a.push_back(b[i]);
    return a;
}

std::vector<int> operator* (std::vector<int> a, int b){
    std::vector<int> c(a.size()+1,0);
    for(int i = 0; i<a.size(); ++i){
        c[i+1] = (c[i]+(long long)(a[i])*b)/BigInteger::MOD;
        c[i] = (c[i]+(long long)(a[i])*b)%BigInteger::MOD;
    }
    return c;
}

void BigInteger::cutzeros(){
    while (digits.back()==0&&digits.size()>1)
        digits.pop_back();
    if (digits.size()==1&&digits[0]==0) sign = false;
}

BigInteger::BigInteger(bool s,const std::vector<int>& d):sign(s),digits(d){
    cutzeros();
}

BigInteger::BigInteger(){
    digits = std::vector<int>(1,0);
    sign = false;
}

BigInteger::BigInteger(int x){
    sign = (x<0);
    digits = std::vector<int>();
    if (x<0) x=-x;
    if (x==0) digits.push_back(0);
    while (x>0){
        digits.push_back(x%MOD);
        x /= MOD;
    }
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

std::string BigInteger::toString() const{
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
    if (sign&&x.sign) return absGreater(x);
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

bool BigInteger::absGreater(const BigInteger& x) const{
    if (digits.size()>x.digits.size()) return true;
    if (digits.size()<x.digits.size()) return false;
    for (int i = digits.size()-1; i>=0; --i){
        if (digits[i]>x.digits[i]) return true;
        if (digits[i]<x.digits[i]) return false;
    }
    return false;
}

BigInteger BigInteger::operator- () const{
    return BigInteger(!sign,digits);
}

BigInteger BigInteger::operator+ (const BigInteger& x) const{
    return BigInteger(*this)+=x;
}

BigInteger BigInteger::operator- (const BigInteger& x) const{
    return BigInteger(*this)-=x;
}

BigInteger BigInteger::operator* (const BigInteger& x) const{
    return BigInteger(*this)*=x;
}

BigInteger BigInteger::operator/ (const BigInteger& x) const{
    return BigInteger(*this)/=x;
}

BigInteger BigInteger::operator% (const BigInteger& x) const{
    return BigInteger(*this)%=x;
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

BigInteger& BigInteger::operator+= (const BigInteger x){
    if (sign^x.sign){
        if (absGreater(x)){
            for (int i = 0; i<digits.size(); ++i){
                if (i<x.digits.size())
                    digits[i]-=x.digits[i];
                if (digits[i]<0){
                    digits[i]+=MOD;
                    --digits[i+1];
                }
            }
        } else {
            sign = !sign;
            digits.resize(x.digits.size(),0);
            for (int i = 0; i<digits.size(); ++i){
                digits[i] = x.digits[i] - digits[i];
                if (digits[i]<0){
                    digits[i]+=MOD;
                    ++digits[i+1];
                }
            }
        }
    } else {
        if (absGreater(x)){
            digits.push_back(0);
            for (int i = 0; i<digits.size(); ++i){
                if (i<x.digits.size())
                    digits[i]+=x.digits[i];
                if (digits[i]>=MOD){
                    digits[i]-=MOD;
                    ++digits[i+1];
                }
            }
        } else {
            digits.resize(x.digits.size()+1,0);
            for (int i = 0; i<digits.size()-1; ++i){
                digits[i]+=x.digits[i];
                if (digits[i]>=MOD){
                    digits[i]-=MOD;
                    ++digits[i+1];
                }
            }
        }
    }
    cutzeros();
    return *this;
}

BigInteger& BigInteger::operator-= (const BigInteger x){
    if (!sign^x.sign){
        if (absGreater(x)){
            for (int i = 0; i<digits.size(); ++i){
                if (i<x.digits.size())
                    digits[i]-=x.digits[i];
                if (digits[i]<0){
                    digits[i]+=MOD;
                    --digits[i+1];
                }
            }
        } else {
            sign = !sign;
            digits.resize(x.digits.size(),0);
            for (int i = 0; i<digits.size(); ++i){
                digits[i] = x.digits[i] - digits[i];
                if (digits[i]<0){
                    digits[i]+=MOD;
                    ++digits[i+1];
                }
            }
        }
    } else {
        if (absGreater(x)){
            digits.push_back(0);
            for (int i = 0; i<digits.size(); ++i){
                if (i<x.digits.size())
                    digits[i]+=x.digits[i];
                if (digits[i]>=MOD){
                    digits[i]-=MOD;
                    ++digits[i+1];
                }
            }
        } else {
            digits.resize(x.digits.size()+1,0);
            for (int i = 0; i<digits.size(); ++i){
                digits[i]+=x.digits[i];
                if (digits[i]>=MOD){
                    digits[i]-=MOD;
                    ++digits[i+1];
                }
            }
        }
    }
    cutzeros();
    return *this;
}

BigInteger& BigInteger::operator*= (const BigInteger x){
    sign = sign^x.sign;
    std::vector<int> d(digits);
    digits = std::vector<int>(1,0);
    for (int i = 0; i<x.digits.size(); ++i){
        *this+=BigInteger(sign,std::vector<int>(i,0)+d*x.digits[i]);
    }
    cutzeros();
    return *this;
}

BigInteger& BigInteger::operator/= (const BigInteger x){
    bool sgn = sign^x.sign;
    sign = x.sign;
    if (x==0) throw std::runtime_error("dividing by zero");
    if (x==2){
        for (int i = digits.size()-1; i>0; --i){
            if (digits[i]%2==1)
                digits[i-1]+=MOD;
            digits[i]/=2;
        }
        digits[0]/=2;
        cutzeros();
        return *this;
    }
    BigInteger l = 0, r = (*this)*2, m;
    while ((r-l).absGreater(1)){
        m = (r+l)/2;
        if (absGreater(m*x)||m*x==*this)
            l = m;
        else
            r = m;
    }
    *this = l;
    cutzeros();
    sign = sgn;
    return *this;
}

BigInteger& BigInteger::operator%= (const BigInteger x){
    return *this-=*this/x*x;
}

std::ostream &operator<<(std::ostream& str, const BigInteger& x){
    str << x.toString();
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

