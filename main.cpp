#include <stdio.h>
#include <iostream>
#include <cmath>
#include "matrix.h"
#include "vector.h"
#include "readfile.h"
#include "posSymLinSystem.h"
#include "linearSystem.h"
using namespace std;

int main() {
    cout << "Hello from main!" << endl;
    //cout << "Matrix A: " << A << endl;
    
    
    Matrix A(2, 3);
    A(1, 1) = 1.1;
    A(1, 2) = 1.2;
    A(2, 3) = 2.3;

    Matrix B(2, 3);
    B = A; // Gán A vào B

    cout << "B(1,1): " << B(1, 1) << endl;
    cout << "B(1,2): " << B(1, 2) << endl;
    cout << "B(2,3): " << B(2, 3) << endl;

    cout << "Number of rows: " << A.GetNumRows() << endl;
    cout << "Number of columns: " << A.GetNumCols() << endl;

    cout << "Elements at (1,1): " << A(1,1) << endl;
    //return 0;
    

    
    // Tạo ma trận 2x3
    Matrix M(2, 3);
    M(1,1) = 1; M(1,2) = 2; M(1,3) = 3;
    M(2,1) = 4; M(2,2) = 5; M(2,3) = 6;

    // Tạo vector có 3 phần tử
    Vector v4(3);
    v4(1) = 1;
    v4(2) = 2;
    v4(3) = 3;


    for(int i = 1; i <= M.GetNumRows(); ++i){
        for(int j = 1; j <= M.GetNumCols(); ++j){
            cout << M(i,j) << " ";
        }
        cout << endl;
    }

    for(int i = 1; i <= v4.size(); ++i){
        cout << v4(i) << " ";
    }
    // Nhân M * v4
    Vector result = M * v4;

    // In kết quả

    cout << "\nResult of M * v4:" << endl;
    for (int i = 1; i <= result.size(); ++i) {
        cout << "result[" << i << "] = " << result[i] << endl;
    }
    //return 0;
    

    int n = 3;
    Matrix G(n, n);
    G(1,1) = 2; G(1,2) = 3; G(1,3) = 1;
    G(2,1) = 0; G(2,2) = 5; G(2,3) = 2;
    G(3,1) = 0; G(3,2) = 0; G(3,3) = 4;

    Vector v5(n);
    v5[1] = 9;
    v5[2] = 17;
    v5[3] = 8;

    LinearSystem system(G, v5);

    Vector x_linear_system = system.Solve();

    cout << "Solution vector x:" << endl;
    for (int i = 1; i <= n; ++i) {
        cout << "x[" << i << "] = " << x_linear_system[i] << endl;
    }

    

    // test posSymLinSystem
    // int n = 3;
    // Matrix A(n, n);
    // Vector b(n);

    // // Nhập ma trận A (1-based indexing)
    // A(1,1) = 4; A(1,2) = 1; A(1,3) = 1;
    // A(2,1) = 1; A(2,2) = 3; A(2,3) = 0;
    // A(3,1) = 1; A(3,2) = 0; A(3,3) = 2;

    // // Nhập vector b
    // b[1] = 6;
    // b[2] = 5;
    // b[3] = 6;

    // // Giải hệ bằng conjugate gradient
    // PosSymLinSystem system(A, b);
    // Vector x = system.Solve();

    // cout << "Nghiem cua he la:\n";
    // for (int i = 1; i <= n; ++i) {
    //     cout << "x[" << i << "] = " << x[i] << endl;
    // }

    // return 0;
    

    //test ma trận symmetric
    Matrix F(2, 2);
    F(1,1) = 1;
    F(1,2) = 2;
    F(2,1) = 2; // đối xứng
    F(2,2) = 3;

    Vector v2(2);
    v2[1] = 4;
    v2[2] = 5;

    try {
        PosSymLinSystem sys(F, v2);
        std::cout << "Symmetric matrix accepted.\n";
    } catch (...) {
        std::cout << "Not symmetric.\n";
    }

    // Test ma trận không đối xứng
    F(2,1) = 9; // khác A[1][2]

    try {
        PosSymLinSystem sys2(F, v2);
        std::cout << "Symmetric matrix accepted.\n";
    } catch (...) {
        std::cout << "Not symmetric.\n";
    }

    // TESST MOORORE PENROSE
    
    Matrix C(2, 3);
    C(1,1) = 1;  C(1,2) = 2;  C(1,3) = 3;
    C(2,1) = 4;  C(2,2) = 5;  C(2,3) = 6;

    // Tạo vector b (size 2)
    Vector v3(2);
    v3(1) = 7;
    v3(2) = 8;

    // Tạo hệ tuyến tính
    LinearSystem ls(C, v3);

    // Giải hệ bằng Moore-Penrose
    Vector x = ls.SolvebyMoorePenrose();

    // In kết quả
    cout << "Solution vector x:" << endl;
    for (int i = 1; i <= x.size(); ++i) {
        cout << "x(" << i << ") = " << x(i) << endl;
    }
    

    // test readfile
    int numSamples = 209;
    const int numFeatures = 6;

    Matrix A_full(numSamples, numFeatures);
    Vector b_full(numSamples), erp_full;

    utils::readMachineData("machine.data", A_full, b_full, erp_full, numSamples);

    Matrix A_train(0, 0);
    Vector b_train(0);
    Matrix A_test(0, 0);
    Vector b_test(0), erp_test;
    
    utils::splitdataset(A_full, b_full, erp_full, A_train, b_train, A_test, b_test, erp_test, 0.8);

    //In ra thử vài dòng train và test
    cout << "Train data:" << endl;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= numFeatures; ++j) {
            cout << A_train(i, j) << " ";
        }
        cout << "| " << b_train[i] << endl;
    }

    cout << "Test data:" << endl;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= numFeatures; ++j) {
            cout << A_test(i, j) << " ";
        }
        cout << "| " << b_test[i] << endl;
    }

    LinearSystem sys(A_train, b_train);
    double lambda = 1.0;
    Vector weights = sys.SolvebyTikhonov(lambda);

    cout << "Weight vector:" << endl;
    for (int i = 1; i <= weights.size(); ++i) {
        cout << weights[i] << " ";
    }
    cout << endl;

    Vector prediction = A_test * weights; // lấy weights đã học từ 80% và * với 20% còn lại rồi lưu vào prediction để so sánh với ERP

    // Sau đó so sánh với erp_test
    for (int i = 1; i <= prediction.size(); ++i) {
        cout << "Predicted: " << prediction[i]
            << ", ERP (expected): " << erp_test[i] << endl;
    }

    double rmse = utils::computeRMSE(prediction, erp_test);
    cout << "RMSE: " << rmse << endl;

    return 0;
}

    
    
    
    
    


