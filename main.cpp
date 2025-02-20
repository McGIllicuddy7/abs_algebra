#include "numbers.h"
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include "q.h"
#include "poly.h"
using std::vector;
using std::string;
int main(void){
    constexpr int max = 16000;
    srand(time(0));
    for(int i =0; i<10'000'000; i++){
        vector<int> first_terms = {rand()%max+1, rand()%max+1, rand()%max+1};
        vector<int> second_terms = {rand()%max+1, rand()%max+1};
        Poly<int> p1 = first_terms;
        Poly<int> p2 = second_terms;
        Poly<int> p = p1*p2;
        assert(p/p2 == p1);
        assert(p/p1 == p2);
        //std::cout<< "p1: "<<(string)p1 << " p2: "<<(string)p2 << " p: " << (string)p << " p/p1: "<<(string)(p/p1) << " p/p2: " << (string)(p/p2)<<"\n";
        if (i%1000 ==0){
            std::cout <<i<<"\n";
        }
    }
}

