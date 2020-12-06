//
//
//

#include "Matrix.h"
#include <random>
#include <iostream>

Matrix::Matrix() {
this->rows=0;
this->columns=0;
this->data= nullptr;
}

Matrix::Matrix(int rows, int columns) {
    std::random_device random;
    std::mt19937 mat(random());
    std::uniform_real_distribution<float> dat(1.0, 2.0);

    this->rows=rows;
    this->columns=columns;
    this->data=new float*[rows];
    for (int i = 0; i < rows; i++)
        this->data[i] = new float[columns];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            this->data[i][j]=dat(mat);
}

Matrix::Matrix(const Matrix & other) {

    this->rows=other.rows;
    this->columns=other.rows;
    this->data=other.data;
}
Matrix::~Matrix() {
    delete this->data;
}

Matrix& Matrix::operator = (const Matrix &other) {

    if(this==&other)
        return *this;

    this->rows=other.rows;
    this->columns=other.rows;
    this->data=other.data;

    return *this;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (this->columns != other.rows) {
        std::cout << "\nError! Two matrices can't do multiplication.\nPlease reset the row and column of matrices. " <<std::endl;
        return Matrix();
    }
    return multiplication(const_cast<Matrix &>(other));
}



Matrix operator*(float a, const Matrix &other) {

    Matrix result(other.rows,other.columns);

    for (int i = 0; i < other.rows; i++)
        for (int j = 0; j < other.columns; j++)
            result.data[i][j]=a*other.data[i][j];

    return result;
}


std::ostream &operator<<(std::ostream &os, const Matrix &other) {

    os<<other.rows<<" rows,"<<other.columns<<" columns\n"<<std::endl;

    for (int i = 0; i < other.rows; i++)
    {
        for (int j = 0; j < other.columns; j++)
            os<<other.data[i][j]<<" ";
        os<<std::endl;
    }

    return os;
}

Matrix Matrix::operator*(float a) const {

   Matrix result(this->rows,this->columns);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            result.data[i][j]=a*this->data[i][j];

            return result;
}

Matrix Matrix::multiplication(Matrix &other) const {
    Matrix result(this->rows,other.columns);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < other.columns; j++)
            result.data[i][j]=0;

    for(int i=0;i<result.rows;i++)
        for(int k=0;k<this->columns;k++)
            for(int j=0;j<result.columns;j++)
              result.data[i][j]+=this->data[i][k]*other.data[k][j];


            return result;
}

