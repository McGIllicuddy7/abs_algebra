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
    Q inverse(){
        Q out;
        out.denum = num;
        out.num = denum;
        out.simplify();
        return out;
    }
    Q simplify(){
        uint64_t tnum =abs(num);
        uint64_t tdenum =denum;
        uint64_t g = gcd(tnum, tdenum);
        uint64_t sign; if (denum<0){sign =-1;} else{sign = 1;};
        Q out;
        out.num = num/g*sign;
        out.denum =denum/g*sign;
        return out;
    }
};