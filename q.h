#include "numbers.h"
class Q{
    public: 
    int64_t num;
    int64_t denum;
    Q(){
        num =0;
        denum =1;
    }
    Q(int64_t in_num, int64_t in_denum){
        num = in_num;
        denum = in_denum;
        *this = simplify();
    }
    Q inverse()const noexcept{
        Q out;
        out.denum = num;
        out.num = denum;
        out = out.simplify();
        return out;
    }
    Q simplify()const noexcept{
        uint64_t tnum =abs(num);
        uint64_t tdenum =denum;
        uint64_t g = gcd(tnum, tdenum);
        uint64_t sign; if (denum<0){sign =-1;} else{sign = 1;};
        Q out;
        out.num = num/g*sign;
        out.denum =denum/g*sign;
        return out;
    }
    Q operator +(const Q& rhs) const noexcept{
        if (num == 0){
            return rhs;
        }
        if (rhs.num == 0){
            return *this;
        }
        auto g1 = gcd(num, rhs.denum);
        auto g2 = gcd(rhs.num, denum);
        auto n1 = num/g1;
        auto n2 = rhs.num/g2;
        auto d1 = rhs.denum;
        auto d2 = denum;
        return Q(n1*d1+n2*d2, d1/g1*d2/g2);
    }
    Q operator-() const noexcept{
        return Q(-num, denum);
    }
    Q operator-(const Q& rhs) const noexcept{
        return *this + -rhs;
    } 
    Q operator*(const Q& rhs) const noexcept{
        return Q(num*rhs.num, denum*rhs.denum);
    }
    Q operator /(const Q& rhs) const noexcept{
        return Q(num*rhs.denum, denum*rhs.num);
    }
    bool operator==(const Q& rhs) const noexcept{
        return num == rhs.num && denum == rhs.denum;
    }
    bool operator <(const Q& rhs) const noexcept{
        auto p1 = num*rhs.denum;
        auto p2 = rhs.num*denum;
        return p1<p2;
    }
    bool operator >(const Q& rhs) const noexcept{
        auto p1 = num*rhs.denum;
        auto p2 = rhs.num*denum;
        return p1<p2;
    }
    bool operator <= (const Q& rhs) const noexcept{
        auto p1 = num*rhs.denum;
        auto p2 = rhs.num*denum;
        return p1<=p2; 
    }
    bool operator >= (const Q& rhs) const noexcept{
        auto p1 = num*rhs.denum;
        auto p2 = rhs.num*denum;
        return p1>=p2;  
    }
};