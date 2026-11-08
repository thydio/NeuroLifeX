#include "helper.hpp"
#include <iostream>
using namespace std;


int main(void){
    Matrix<int> m(3,4);

    cout << m.rows() << endl;
    cout << m.columns() << endl;


    for (int i = 0; i < 3;i++){
        for(int j = 0; j < 4; j++){
            m.set(i,j,i+j);
        }
    }

    print_m(m);
    RandomGen gen;


    cout << gen.uniform(2.0,6.0) << endl;

    cout << gen.uniformi(2,7) << endl;
    
    
    return 0;
}