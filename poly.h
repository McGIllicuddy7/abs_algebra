#pragma once 
#include "numbers.h"
#include <vector>
#include <optional>
#include <string>
#include <algorithm>
#include <iostream>
template <Ring T> struct Term{
    T coef; 
    uint64_t pow;
    Term(){

    }
    Term(T value, uint64_t power){
        coef = value;
        pow = power;
    }
    Term(T value){
        coef = value;
        pow =0;
    }
    bool operator >(const Term<T> & other)const {
        if(other.pow == pow){
            return coef > other.coef;
        } else{
            return pow>other.pow;
        }
    }
    bool operator <(const Term<T> & other)const {
        if(other.pow == pow){
            return coef < other.coef;
        } else{
            return pow<other.pow;
        }
    }
    bool operator ==(const Term<T> & other)const {
        return pow == other.pow && coef == other.coef;
    }
    bool operator ==(const T& other)const {
        return pow == 0 && other == coef;
    }
    bool operator<=(const Term<T>&) const = default;
    bool operator>=(const Term<T>&) const = default;
    Term<T> operator-()const{
        return Term{-coef, pow};
    }
    Term<T> operator/(const Term<T> & other)const {
        return Term(coef/other.coef, pow-other.pow);
    }
    
    operator std::string(){
        std::string out;
        out += std::to_string(coef);
        if(pow > 0){
            out += "x";
            if (pow>1){
                out += "^";
                out += std::to_string(pow);
            }
        }
        return out;
    }
};
template<typename T> Term<T> zero(Term<T> a){
    return Term(zero(a.coef),1);
}
template<Ring T> std::optional<T> contains_power(const std::vector<Term<T>> & terms, const Term<T> & term){
    for(size_t i =0; i<terms.size(); i++){
        if (terms[i].pow == term.pow){
            return i;
        }
    }
    return {};
}
template <Ring T> class Poly{
    public:
    std::vector<Term<T>> terms;
    Poly() noexcept{
        
    }
    Poly(std::vector<Term<T>> inputs) noexcept{
        terms= inputs;
        collect_like();
    }
    Poly(std::vector<T> inputs){
        for(size_t i =0; i<inputs.size(); i++){
            terms.push_back(Term<T>{inputs[i], i});
        }
        collect_like();
    }
    void collect_like() noexcept{
        std::vector<Term<T>> new_terms;
        for(auto& i: terms){
            if(i.coef ==zero(i)){
                continue;
            }
           std::optional<size_t> a = contains_power(new_terms, i);
           if(a.has_value()){
                new_terms[*a].coef = new_terms[*a].coef+i.coef;
           } else if (i.coef != zero(i.coef)){
                new_terms.push_back(i);
           }
        }
        std::sort(new_terms.begin(), new_terms.end());
        terms = new_terms;
    }
    bool operator==(const Poly & other) const noexcept{
        if (terms.size() <= 1 && other.terms.size()<=1){
            if (terms.size() == 0 && other.terms.size() == 0){
                return true;
            } else if (terms.size() == 0 && other.terms.size() == 1){
                return zero(other.terms[0].coef) == other.terms[0].coef; 
            } else if (other.terms.size() == 0 && terms.size() == 1){
                return terms[0].coef == zero(terms[0].coef); 
            }
            else{
                return terms[0].coef == other.terms[1].coef && terms[0].pow == other.terms[0].pow;
            }
        }
        if (terms.size() != other.terms.size()){
            return false;
        }
        for(size_t i =0; i<terms.size(); i++){
                if((terms[i].pow != other.terms[i].pow || terms[i].coef != other.terms[i].coef) && (terms[i].coef != zero(terms[i].coef) && other.terms[i].coef != zero(other.terms[i].coef))){
                    return false;
                }
        }
        return true;
    }
    Poly<T> operator*(const Term<T>& other) const noexcept{
        std::vector<Term<T>> new_terms = terms;
        for(auto & i: new_terms){
            i.pow = i.pow+other.pow ;
            i.coef =i.coef* other.coef;
        }
        return new_terms;
    }
    Poly<T> operator+(const Poly<T>& other) const noexcept{
        std::vector<Term<T>> new_terms = terms;
        for(auto & i:other.terms){
            new_terms.push_back(i);
        }
        return new_terms;
    } 
    void operator += (const Poly<T> & other)noexcept{
        std::vector<Term<T>> new_terms = terms;
        for(auto & i:other.terms){
            new_terms.push_back(i);
        }
        *this = new_terms;
    }
    Poly<T> operator-(const Poly<T>& other) const noexcept{
        std::vector<Term<T>> new_terms = terms;
        for(auto & i:other.terms){
            new_terms.push_back(-i);
        }
        return new_terms;
    } 
    void operator -= (const Poly<T> & other)noexcept{
        std::vector<Term<T>> new_terms = terms;
        for(auto & i:other.terms){
            new_terms.push_back(-i);
        }
        *this = new_terms;
    }
    Poly<T> operator*(const Poly<T>& other) const noexcept{
        Poly<T> out;
        for(auto& i : other.terms){
            out += *this*i;
        }
        return out;
    } 
    void operator*=(const Poly<T>& other) noexcept{
        Poly<T> out;
        for(auto& i : other.terms){
            out += *this*i;
        }
        *this = out;
    } 
    Poly<T> operator/(const Term<T> & other) const noexcept{
        (void)other;
        std::vector<Term<T>> out_terms;
        for(const Term<T> &i : terms){
            if(i.pow>=other.pow){
                T cf = i.coef/other.coef;
                T pw = i.pow-other.pow;
                out_terms.push_back(Term<T>(cf, pw));
            }
        }
        return out_terms;
    }
    Poly<T> operator%(const Term<T> & other) const noexcept{
        Poly<T> q = *this/other;
        return *this-(q*other);
    }
    Poly<T> operator/(const Poly<T>& other) const noexcept{
        Poly<T> remainder = *this;
        std::vector<Term<T>> out;
        auto old_degree = remainder.degree() +1;
        int steps =0;
        while(remainder.degree()> other.degree()){
            old_degree = remainder.degree();
            auto old_remainder = remainder;
            Term tmp = remainder.largest_term()/other.largest_term();
            remainder = remainder - other*tmp; 
           // std::cout <<"remainder:"<<(std::string)remainder<< " remainder largest: "<< (std::string)remainder.largest_term()<< " other*tmp: " << (std::string)(other*tmp)<<"\n";
            out.push_back(tmp);
            if(other.degree()  == 0){
                break;
            }
            steps++;
            if (steps>1000){
                break;
            }
        }
        return out;
    }
    Poly<T> operator%(const Poly<T> & other)const noexcept{
        Poly<T> base = *this/other;
        return *this-base*other;
    }
    uint64_t degree()const noexcept{
        uint64_t out = 0;
        for(const auto &i: terms){
            if(i.pow>out){
                out = i.pow;
            }
        }
        return out;
    }
    Term<T> largest_term()const noexcept{
        Term<T> out;
        out.coef = 0;
        out.pow =0;
        for(const auto &i: terms){
            if(i.pow>out.pow && i.coef != 0){
                out = i;
            }
        }
        return out; 
    }
    Term<T> constant_term()const noexcept{
        Term<T> out;
        out.coef = 0;
        out.pow = 0;
        for(const auto &i: terms){
            if(i.pow == 0){
                return Term(i.coef,0);
            }
        }
        return 0;
    }
    Poly<T> derivitive_of()const noexcept{
        std::vector<Term<T>> new_terms;
        for(const auto &i: terms){
            if (i.pow == 0){
                continue;
            }
            else{
                Term<T> t = i;
                t.coef *= t.pow;
                t.pow -=1;
                new_terms.push_back(t);
            }
        }
        return new_terms;
    }
    T operator()(const T &operand)const noexcept{
        T out = zero(operand);
        const auto power = [](const T & base, uint64_t power){
            T out = one(base);
            for(size_t i =0; i<power; i++){
                out *= base;
            }
            return out;
        };
        for(const auto &i: terms){
            out += i.coef*power(operand, i.pow);
        }
        return out;
    }
    operator std::function<T(const T&)>() const noexcept{
        auto a = *this;
        return [a](const T& value){return a(value);};
    }
    std::vector<Poly<T>> factorize_non_continous()const noexcept{
        if(degree() == 1){
            return {*this};
        }
        T zilch = zero(terms[0].coef);
        Poly<T> p0 = Poly<T>(std::vector({zilch}));
        T p1 = suc(zilch);
        T p2 = zilch;
        bool hit =false;
        Poly<T> term;
        bool start = true;
        T ct= constant_term().coef;
        while(p1 != zilch && abs(p1)<=abs(ct)){
            while ((p2 != zilch || start) && abs(p2)<=abs(ct) ){
                start = false;
                term = Poly<T>(std::vector({p1, p2}));
                Poly<T> rem = (*this)%term;
                if (rem == p0){
                    hit = true;
                    break;
                }
                p2 = suc(p2);
            }
            p2 = zilch;
            if(hit){
                break;
            }
            p1 = suc(p1);
        }
        Poly<T> poly = *this/term;
        if (poly == *this){
            return std::vector<Poly<T>>({*this});
        }
        std::cout <<"poly:"<< (std::string)poly<<"\n";
        std::vector<Poly<T>> terms = poly.factorize();
        terms.push_back(poly);
        return terms;
    }
    std::vector<Poly<T>> factorize() const noexcept{
        if (this->degree() == 0){
            return std::vector<Poly<T>>();
        }
        const auto root = find_root((std::function<T(const T&)>)(*this), (std::function<T(const T&)>)(this->derivitive_of()));
        if (abs((*this)(root)) < epsilon(root)){
            Poly<T> factor =Poly<T>(std::vector<T>{zero(root)-root, one(root)});
            Poly<T> to_factor = (*this)/factor;
            std::cout <<(std::string)to_factor<<"\n";
            std::vector<Poly<T>> factors = to_factor.factorize();
            factors.push_back(factor);
            return factors;
        } else{
            return std::vector<Poly<T>>({*this});
        }
    }
    operator std::string(){
        std::string out;
        if (terms.size() == 1 && terms[0].coef == zero(terms[0].coef)){
            return "0";
        }
        for(size_t i =0; i<terms.size(); i++){
            if (terms[i].coef == zero(terms[i].coef)&& terms.size() != 1){
                continue;
            }
            std::string tmp = terms[i];
            if (i != 0){
                if(tmp[0] == '-'){
                    out += tmp;
                } else{
                    out += "+";
                    out += tmp;
                }
            } else{
                out += tmp;
            }
        }
        if(out == ""){
            out = "0";
        }
        return out;
    }
};