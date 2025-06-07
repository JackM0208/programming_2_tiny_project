#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "vector.h"
#include "matrix.h"
#include <cassert>
#include "linearsystem.h"
#include "posSymLinSystem.h"
using namespace std;

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b){
    if(!isSymmetric(A)){
        throw invalid_argument("Matrix is not symmetric");
    }

    assert(A.GetNumRows() == b.size());
    assert(A.GetNumRows() == A.GetNumCols());

    // lớp cha Linear System đã giải quyết chỗ này
}

PosSymLinSystem::~PosSymLinSystem(){
    // lớp cha Linear System đã giải quyết chỗ này
}

bool PosSymLinSystem::isSymmetric(const Matrix& A) const{
    int n = A.GetNumRows();
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(A(i,j) != A(j,i)){
                return false;
            }
        }
    }
    return true;
}

Vector PosSymLinSystem::Solve(){
    cout << "Dang giai he phuong trinh bang Conjugate Gradient...\n";

    assert(mpA != nullptr && mpb != nullptr);

    int n = mSize;
    Vector x(n);              // Khởi tạo nghiệm ban đầu = 0
    Vector r = (*mpb) - (*mpA) * x; // r = b - A*x = b (vì x = 0)
    Vector p = r;

    double tol = 1e-10;
    int max_iter = n * 10;

    for (int k = 1; k <= max_iter; ++k) {
        cout << "Iteration k = " << k << endl;

        Vector Ap = (*mpA) * p;
        double numerator = (r * r);
        double denominator = (p * Ap);

        cout << "r*r = " << numerator << ", p*Ap = " << denominator << endl;

        if (denominator == 0.0) {
            cout << "Denominator is zero, cannot continue." << endl;
            break;
        }

        double alpha = numerator / denominator;
        cout << "alpha = " << alpha << endl;

        x = x + alpha * p;
        Vector r_new = r - alpha * Ap;

        cout << "r_new size = " << r_new.size() << ", mData ptr = " << (void*)(&r_new[1]) << endl;

        double norm_val = r_new.Norm();
        cout << "Debug: Norm value = " << norm_val << endl;

        double res_norm = r_new.Norm();
        cout << "Residual norm: " << res_norm << endl;

        cout << "Checking residual norm: " << r_new.Norm() << " < tol: " << tol << " ?" << endl;

        if (res_norm < tol){ 
            cout << "Converged at iteration " << k << endl;
            break; // Đã hội tụ
        }

        double beta = (r_new * r_new) / (r * r);
        cout << "beta = " << beta << endl;

        p = r_new + beta * p;
        r = r_new;
    }

    return x;
}




