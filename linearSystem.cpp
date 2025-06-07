#include "linearSystem.h"
#include "vector.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cassert>
using namespace std;

LinearSystem::LinearSystem(const Matrix& A, const Vector& b) {
    assert(A.GetNumRows() == b.size());
    mSize = A.GetNumRows();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

Vector LinearSystem::Solve() {
    int n = mSize;
    Matrix A = *mpA; // copy to avoid modifying the original
    Vector b = *mpb;

    // Forward elimination
    for (int i = 1; i <= n-1; ++i) {
        // Pivoting
        int maxRow = i;
        for (int k = i + 1; k <= n; ++k) {
            if (abs(A(k, i)) > abs(A(maxRow, i))) {
                maxRow = k;
            }
        }
        for (int k = 1; k <= n; ++k) {
            swap(A(i, k), A(maxRow, k));
        }
        swap(b[i], b[maxRow]);

        // Make all rows below this one 0 in current column
        for (int k = i + 1; k <= n; ++k) {
            double factor = A(k, i) / A(i, i);
            for (int j = i; j <= n; ++j) {
                A(k, j) -= factor * A(i, j);
            }
            b[k] -= factor * b[i];
        }
    }

    // Back substitution
    Vector x(n);
    for (int i = n; i >= 1; --i) {
        double sum = b[i];
        for (int j = i + 1; j <= n; ++j) {
            sum -= A(i, j) * x[j];
        }
        x(i) = sum / A(i, i);
    }

    return x;
}

Vector LinearSystem::SolvebyMoorePenrose() const{
    // Giải hệ Ax = b với A không vuông bằng A^+ b
    // Sẽ dùng công thức x = (A^T A)^(-1) A^T b (cho over-determined) - tức là số pt > số ẩn

    const Matrix& A = *mpA;
    const Vector& b = *mpb;

    if(A.GetNumRows() > A.GetNumCols()){
        // over-determined
        Matrix At = A.transpose();
        Matrix AtA = At * A;
        Matrix AtA_inv = AtA.inverse();
        Vector result = AtA_inv * At * b;
        return result;
    }
    else {
        // under-determined
        Matrix At = A.transpose();
        Matrix AAt = (*mpA) * At;
        Matrix AAt_inv = AAt.inverse();
        Vector result = At * AAt_inv * b;
        return result;
    }
}

// (AᵗA + λI)⁻¹ Aᵗ b
Vector LinearSystem::SolvebyTikhonov(double lambda) const{
    const Matrix& A = *mpA;
    const Vector& b = *mpb;

    Matrix At = A.transpose();
    Matrix AtA = At * A;

    int n = A.GetNumCols();
    Matrix I(n, n);
    for(int i = 1; i <= n; ++i){
        I(i,i) = 1.0;
    }
    Matrix M = AtA + (I * lambda);
    Vector Atb = At * b;
    Vector result = M.inverse() * Atb;
    return result;
}

