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

int main(void){
    srand(time(0));
    std::vector<int> a = {0,1,1,2,3,5};
    print("first {} fibbonacci numbers: {}\n", a.size(), a);

}