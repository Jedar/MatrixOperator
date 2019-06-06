#ifndef MATRIX_H
#define MATRIX_H
#include "Bignum.h"
#include <iostream>

using namespace BIGNUM;

static void Matrix_error(string msg){
    using namespace std;
    cerr<<msg<<endl;
    exit(1);
}

class Matrix{
private:
    /*           col
     *       +---------+
     *       |         |
     *    row|         |
     *       |         |
     *       +---------+
     * 
     */
    int ROW_NUM;
    int COL_NUM;
    Bignum *arr;
public:
    Matrix();

    Matrix(int row, int col);

    Matrix(int *array);

    Matrix(string *array);

    Matrix(string *array,int row, int col);

    Matrix(string number);

    ~Matrix();

    Matrix(const Matrix& matrix);

    void print() const;

    string to_string() const;

    friend Matrix operator+(const Matrix& m1,const Matrix& m2);

    friend Matrix operator-(const Matrix& m1,const Matrix& m2);

    friend Matrix operator*(const Matrix& m1,const Matrix& m2);

    friend Matrix operator*(const Bignum& num,const Matrix& m);

    friend bool operator==(const Matrix& m1,const Matrix& m2);

    Matrix operator~() const;

    Matrix operator+() const;

    Matrix operator-() const;

    Matrix& operator=(const Matrix& m);

    Matrix& operator+=(const Matrix& m);

    Matrix& operator-=(const Matrix& m);
};

#endif/* MATRIX_H */
