#include "numbers.h"
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include "matrix.h"
#include "q.h"
#include "poly.h"
#include <string_view>
#include <sstream>
#include "utils.h"
using std::vector;
using std::string;
using std::string_view;
template<const uint64_t N>void make_addition_table(const std::vector<Poly<Zn<N>>> values, Poly<Zn<N>> p){
    std::vector<std::vector<Poly<Zn<N>>>> vec = {};
    for(size_t i = 0; i<values.size(); i++){
        std::vector<Poly<Zn<N>>> tmp = {};
        for(size_t j =0; j<values.size(); j++){
            auto a = values[i];
            auto b = values[j];
            auto c = (a+b)%p;
            tmp.push_back(c);
        }
        vec.push_back(tmp);
    }
    std::string out="";
    out += utils::right_pad("+",10);
    out += "|";
    for(size_t i =0; i<values.size(); i++){
        out += utils::right_pad(values[i], 10);
        out +="|";
    }
    std::string brek = utils::repeat_string("-", out.size());
    out += "\n";
    out += brek;
    out += "\n";
    for(size_t i =0; i<values.size(); i++){
        out += utils::right_pad(values[i], 10);
        out += "|";
        for(size_t j =0; j<values.size(); j++){
            out += utils::right_pad(vec[j][i], 10);
            out += "|";
        }
        out += "\n";
        out += brek;
        out += "\n";
    }
    std::cout <<out<<"\n";
}
template<const uint64_t N>void make_multiplication_table(const std::vector<Poly<Zn<N>>> values, Poly<Zn<N>> p){
    std::vector<std::vector<Poly<Zn<N>>>> vec = {};
    for(size_t i = 0; i<values.size(); i++){
        std::vector<Poly<Zn<N>>> tmp = {};
        for(size_t j =0; j<values.size(); j++){
            auto a = values[i];
            auto b = values[j];
            auto c = (a*b)%p;
            tmp.push_back(c);
        }
        vec.push_back(tmp);
    }
    std::string out="";
    out += utils::right_pad("x",10);
    out += "|";
    for(size_t i =0; i<values.size(); i++){
        out += utils::right_pad(values[i], 10);
        out +="|";
    }
    std::string brek = utils::repeat_string("-", out.size());
    out += "\n";
    out += brek;
    out += "\n";
    for(size_t i =0; i<values.size(); i++){
        out += utils::right_pad(values[i], 10);
        out += "|";
        for(size_t j =0; j<values.size(); j++){
            out += utils::right_pad(vec[j][i], 10);
            out += "|";
        }
        out += "\n";
        out += brek;
        out += "\n";
    }
    std::cout <<out<<"\n";
}

int main(void){
    srand(time(0));
    
}