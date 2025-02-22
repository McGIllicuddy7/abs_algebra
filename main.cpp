#include "numbers.h"
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include "matrix.h"
#include "q.h"
#include "poly.h"
using std::vector;
using std::string;
int main(void){
    srand(time(0));
   Poly<double> a = std::vector<double>({1.0, 3.0, -1.0});
    std::cout << (string)a<<"\n";
    Poly<double> a_pr= a.derivitive_of();
    std::cout << (string)a_pr<<"\n";
    double root = find_root((std::function<double(const double &)>)a, (std::function<double(const double &)>)a_pr);
    std::cout << "root:"<<root <<"\n"<< "f(root)"<< a(root)<< "\n";
    std::vector<Poly<double>> polys = a.factorize();
    for(auto &p: polys){
        std::cout <<(string)p <<"\n";
    }
}