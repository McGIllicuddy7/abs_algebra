#pragma once 
#include <vector> 
template <typename T> T one(const T & value){
    (void)value;
    return 1;
}
template <typename T> T zero(const T & value){
    (void)value;
    return 0;
}
template<typename T>
concept Ring = requires (T a, T b){
    {zero(a)}->std::convertible_to<T>;
    {a+b}->std::convertible_to<T>;
    {a*b}->std::convertible_to<T>;
    {2*a}->std::convertible_to<T>;
    {a == b}->std::convertible_to<bool>;
};
template <typename T> concept ModRing = requires (T a,T b){
    {a/b} ->std::convertible_to<T>; 
    {a%b} ->std::convertible_to<T>;
    {zero(a)}->std::convertible_to<T>;
    {a+b}->std::convertible_to<T>;
    {a*b}->std::convertible_to<T>;
    {2*a}->std::convertible_to<T>;
    {a == b}->std::convertible_to<bool>;
};
template<typename T> concept DivisionRing = requires (T a, T b){
    {a/b} ->std::convertible_to<T>;
    {a+b}->std::convertible_to<T>;
    {a*b}->std::convertible_to<T>;
    {2*a}->std::convertible_to<T>;
    {zero(a)}->std::convertible_to<T>;
    {a == b}->std::convertible_to<bool>;
};
template<typename T> concept Field= requires(T a, T b){
    {a/b} ->std::convertible_to<T>;
    {a+b}->std::convertible_to<T>;
    {a*b}->std::convertible_to<T>;
    {2*a}->std::convertible_to<T>;
    {a == b}->std::convertible_to<bool>;
    {one(a)}->std::convertible_to<T>; 
};
/*pub fn gcd<T:Ring+Div<Output = T>+Identity+Rem<Output = T>+PartialOrd>(a0:T, b0:T)->T{
    let mut a = a0;
    let mut b = b0;
    if b>a{
        return gcd(b,a);
    }
    else if a== b{
        return a;
    }
    loop{
        let r = a.clone()%b.clone();
        if r == T::zero(){
            return b;
        } else{
            a = b;
            b = r;
        }
    }
}*/
template <ModRing T> T gcd (const T & a0, const T & b0){
    T a = a0;
    T b = b0;
    if (b>a){
        return gcd(b,a);
    } else if (a == b){
        return a;
    }
    for(;;){
        T r = a%b;
        if (r == zero(b)){
            return b;
        } else{
            a = b;
            b = r;
        }
    }
}
template <const uint64_t N> class Zn{
    static_assert(N>0);
    public:
    uint64_t value;
    operator uint64_t (){
        return value;
    }
    Zn(){

    }
    Zn(uint64_t in_value){
        value = in_value%N;
    }
    Zn<N> operator-()const noexcept{
        return (N-value)%N;
    }
    Zn<N> operator -(Zn<N> other)const noexcept{
        return (value-other.value);
    }
    Zn<N> operator +(Zn<N> other)const noexcept{
        return (value+other.value);
    }
    Zn<N> operator *(Zn<N> other)const noexcept{
        return (value*other.value);
    }
    Zn<N> operator /(Zn<N> other)const noexcept{
        return (value/other.value);
    }
    Zn<N> operator %(Zn<N> other) const noexcept{
        return (value%other.value);
    }
    bool operator == (Zn<N> other)const noexcept{
        return value == other.value;
    }
    bool operator <(Zn<N> other)const noexcept{
        return value %N < other.value %N; 
    }
    bool operator >(Zn<N> other)const noexcept{
        return value %N > other.value %N; 
    }
    bool operator >=(const Zn<N>& other)const noexcept{
        return value >= other.value;
    }
    bool operator <=(const Zn<N>& other)const noexcept {
        return value <= other.value;
    }
    bool operator != (const Zn<N>& other) const noexcept=default;
    bool operator +=(const Zn<N>& other)const noexcept{
        *this = *this+other;
    }
    bool operator -=(const Zn<N>& other)const noexcept{
        *this = *this-other;
    }
    bool operator *= (const Zn<N>& other) const noexcept{
        *this = *this*other;
    }
    bool operator /= (const Zn<N>& other) const noexcept{
        *this = *this/other;
    }
    bool operator %= (const Zn<N>& other) const noexcept{
        *this = *this%other;
    }
};
template<typename T> T suc(const T & prev){
    return prev+1;
}