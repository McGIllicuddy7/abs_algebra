#pragma once 
#include <vector> 
#include <functional>
#include <iostream>
#include <cstdint>
#include <assert.h>
template <typename T> T one(const T & value){
    (void)value;
    return 1;
}
template <typename T> T zero(const T & value){
    (void)value;
    return 0;
}
inline void nothing(size_t args,...){
    (void)args;
}
template <typename T, typename...Args> T random_value(Args...args){
    nothing(0, args...);
    return rand()%128;
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
    void operator +=(const Zn<N>& other)const noexcept{
        *this = *this+other;
    }
    void operator -=(const Zn<N>& other)const noexcept{
        *this = *this-other;
    }
    void operator *= (const Zn<N>& other) const noexcept{
        *this = *this*other;
    }
    void operator /= (const Zn<N>& other) const noexcept{
        *this = *this/other;
    }
    void operator %= (const Zn<N>& other) const noexcept{
        *this = *this%other;
    }
};
template<Ring T> T suc(const T & prev){
    return prev+1;
}
template<Ring T> T epsilon(const T & value){
    (void)value;
    return 0.001;
}
template <typename T> T nderive(const std::function<T(const T&)> func, const T& value){
    T eps = epsilon(value);
    T base = func(value);
    T second = func(value+eps);
    return (second-base)/(eps);
}

template<typename T, typename...Args> T find_root(std::function<T(const T&)> func, std::function<T(const T&)> derivitive, Args...args){
    T current = random_value<T>(args...);
    int count = 0;
    do{
        T value = func(current);
        if(value == zero(value)){
            return current;
        }
        T der = derivitive(current);
        current = current - value/der;
    }while(count <1000);
    return current;
}
template<typename T, typename...Args> T find_root(std::function<T(const T&)> func,Args...args){
    std::function<T(const T&)> der1 = func;
    std::function<T(const T&)> der = [der1](const T & x){return nderive(der1, x);};
    return find_root(func, der, args...);
}