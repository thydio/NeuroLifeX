#include "helper.hpp"
#include <iostream>
using namespace std;


int main(void){

    Matrix<double> m(3,4);

    RandomGen gen;

    m.randomize(gen,0,1);

    Matrix<double> j(3,5);


    j.randomize(gen,0,1);


    print_m(m);
    print_m(j);

    print_m(m+j);
    return 0;
}