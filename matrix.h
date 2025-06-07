#pragma once
#include <iostream>
#include <cstdlib>
#include "vector.h"
using namespace std;

class Matrix{
    private:
    int mNumRows, mNumCols;
    double** mData = nullptr;

    public:
    Matrix(int numRows, int numCols);

    Matrix(const Matrix& other);

    ~Matrix();

    public:
    int GetNumRows() const;
    int GetNumCols() const;

    double& operator() (int numRows, int numCols);

    double operator()(int numRows, int numCols) const;

    // unary
    Matrix& operator=(const Matrix& other);

    Matrix operator-() const;

    

    // binary

    Matrix operator+(const Matrix& other);
    
    Matrix operator-(const Matrix& other);

    Matrix operator*(const Matrix& other);

    Vector operator*(const Vector& v) const;

    Matrix operator*(double scalar) const;


    // advance operations
    double determinant();

    Matrix minorMatrix(int rowToRemove, int colToRemove); // tính ma trận con

    Matrix adjugate(); // tính ma trận phụ hợp để tính inverse cho lẹ

    Matrix transpose() const; // crazy method để biến đổi matrix

    Matrix inverse();

    Matrix pseudo_inverse();
};
