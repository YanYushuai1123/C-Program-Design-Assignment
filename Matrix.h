//
//
//

#ifndef AS4_MATRIX_H
#define AS4_MATRIX_H

#include <ostream>

class Matrix{
private:
    int rows;
    int columns;
    float **data;
public:
    Matrix();
    Matrix(int rows,int columns);
    Matrix(const Matrix& );//copy constructor
    ~Matrix();

    Matrix multiplication(Matrix & other)const;

    Matrix operator*(const Matrix& other)const;
    Matrix & operator=(const Matrix& other);
    Matrix operator*(float a)const;

     friend Matrix operator*(float a,const Matrix& other);
     friend std::ostream & operator <<(std::ostream & os,const Matrix & other);

};

#endif //AS4_MATRIX_H
