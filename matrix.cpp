#include "matrix.h"
#include <cassert>
#include <cmath>

Matrix::Matrix(int numRows, int numCols)
    : mNumRows(numRows), mNumCols(numCols) {
    mData = new double*[mNumRows + 1];

    mData[0] = nullptr; // khởi tạo mData[0] trước cho an toàn, vì matrix dùng 1-based
    
    for (int i = 1; i <= mNumRows; ++i) {
        mData[i] = new double[mNumCols + 1];
        for (int j = 1; j <= mNumCols; ++j) {
            mData[i][j] = 0.0;
        }
    }
}

// copy constructor
Matrix::Matrix(const Matrix& other)
    : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    mData = new double*[mNumRows + 1];
    for (int i = 1; i <= mNumRows; ++i) {
        mData[i] = new double[mNumCols + 1];
        for (int j = 1; j <= mNumCols; ++j) {
            mData[i][j] = other.mData[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 1; i <= mNumRows; ++i) {
        delete[] mData[i];
    }
    delete[] mData;
}

int Matrix::GetNumRows() const {
    return mNumRows;
}

int Matrix::GetNumCols() const {
    return mNumCols;
}

double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i][j];
}

double Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i][j];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;
    for (int i = 1; i <= mNumRows; ++i) {
        delete[] mData[i];
    }
    delete[] mData;

    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;

    mData = new double*[mNumRows + 1];
    for (int i = 1; i <= mNumRows; ++i) {
        mData[i] = new double[mNumCols + 1];
        for (int j = 1; j <= mNumCols; ++j) {
            mData[i][j] = other.mData[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= mNumCols; ++j)
            result(i, j) = -mData[i][j];
    return result;
}

Matrix Matrix::operator+(const Matrix& other) {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= mNumCols; ++j)
            result(i, j) = mData[i][j] + other(i, j);
    return result;
}

Matrix Matrix::operator-(const Matrix& other) {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= mNumCols; ++j)
            result(i, j) = mData[i][j] - other(i, j);
    return result;
}

Matrix Matrix::operator*(const Matrix& other) {
    assert(mNumCols == other.mNumRows);
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= other.mNumCols; ++j)
            for (int k = 1; k <= mNumCols; ++k)
                result(i, j) += mData[i][k] * other(k, j);
    return result;
}

Vector Matrix::operator*(const Vector& v) const {
    assert(mNumCols == v.size());
    Vector result(mNumRows);

    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= mNumCols; ++j)
            result(i) += (*this)(i,j) * v(j);
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= mNumCols; ++j)
            result(i, j) = mData[i][j] * scalar;
    return result;
}

Matrix Matrix::minorMatrix(int rowToRemove, int colToRemove) {
    assert(mNumRows == mNumCols); // Chỉ dùng cho ma trận vuông

    Matrix minor(mNumRows - 1, mNumCols - 1); // Ma trận con nhỏ hơn 1 dòng, 1 cột

    int newRow = 1; // Dòng trong ma trận con
    for (int i = 1; i <= mNumRows; ++i) {
        if (i == rowToRemove) continue; // Bỏ dòng này

        int newCol = 1; // Cột trong ma trận con
        for (int j = 1; j <= mNumCols; ++j) {
            if (j == colToRemove) continue; // Bỏ cột này

            // Copy giá trị từ ma trận gốc
            minor(newRow, newCol) = (*this)(i, j);
            newCol++;
        }
        newRow++;
    }

    return minor;
}

// Tính định thức (determinant) đệ quy cho ma trận vuông
double Matrix::determinant() {
    assert(mNumRows == mNumCols); // Chỉ ma trận vuông mới có định thức

    int n = mNumRows;

    // Trường hợp 1x1
    if (n == 1) {
        return (*this)(1, 1);
    }

    // Trường hợp 2x2
    if (n == 2) {
        return ((*this)(1, 1) * (*this)(2, 2)) - ((*this)(1, 2) * (*this)(2, 1));
    }

    // n x n
    double det = 0.0;

    for (int col = 1; col <= n; ++col) {
        Matrix minor = this->minorMatrix(1, col); // Bỏ dòng 1 và cột col
        double sign = (col % 2 == 0) ? -1.0 : 1.0; // Xen kẽ dấu + -

        det += sign * (*this)(1, col) * minor.determinant(); // Đệ quy
    }

    return det;
}


// Tính ma trận phụ hợp (adjugate)
Matrix Matrix::adjugate() {
    assert(mNumRows == mNumCols);
    Matrix adjugate(mNumRows, mNumCols);

    for (int i = 1; i <= mNumRows; ++i) {
        for (int j = 1; j <= mNumCols; ++j) {
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            double cofactor = sign * (this->minorMatrix(i, j).determinant());
            adjugate(j, i) = cofactor; // Chuyển vị tại đây
        }
    }
    return adjugate;
}


// Transpose (chuyển vị)
Matrix Matrix::transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 1; i <= mNumRows; ++i) {
        for (int j = 1; j <= mNumCols; ++j) {
            result(j, i) = mData[i][j];
        }
    }
    return result;
}

// Inverse ma trận vuông (A^-1 = adj(A)/det(A))
Matrix Matrix::inverse() {
    assert(mNumRows == mNumCols);
    double det = determinant();
    if (det == 0) {
        throw std::runtime_error("Matrix is singular, cannot invert.");
    }
    Matrix adj = adjugate();
    return adj * (1.0 / det); 
}

// Pseudo-inverse (Moore-Penrose) dùng cho matrix không vuông
Matrix Matrix::pseudo_inverse() {
    // Nếu A là m x n
    if (mNumRows >= mNumCols) {
        // over-determined: A+ = (A^T A)^-1 A^T
        Matrix At = this->transpose();
        Matrix AtA = At * (*this);
        Matrix AtA_inv = AtA.inverse();
        return AtA_inv * At;
    } else {
        // under-determined: A+ = A^T (A A^T)^-1
        Matrix At = this->transpose();
        Matrix AAt = (*this) * At;
        Matrix AAt_inv = AAt.inverse();
        return At * AAt_inv;
    }
}
