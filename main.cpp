#include <iostream>
#include "Matrix.h"
using namespace std;

int main() {

    Matrix A(5,6);//set some random matrices
    Matrix B(6,5);
    Matrix C(7,8);
    const Matrix& D(A);
    float a=3,b=4;

    cout<<"Implementation test:"<<endl;
    cout<<"Matrix A:\n"<<A<<endl;
    cout<<"Matrix B:\n"<<B<<endl;
    cout<<"Matrix C:\n"<<C<<endl;
    cout<<"result of A*B:\n"<<A*B<<endl;
    cout<<"result of A*b (b=4):\n"<<A*b<<endl;
    cout<<"result of a*B (a=3):\n"<<a*B<<endl;
    cout<<"result of A*C :\n"<<A*C<<endl;


    return 0;
}
