// readfile.h
#ifndef READFILE_H
#define READFILE_H

#pragma once
#include <string>
#include "matrix.h"
#include "vector.h"
using namespace std;

namespace utils {
    // Hàm đọc file machine.data, lấy 6 cột features (MYCT, MMIN, MMAX, CACH, CHMIN, CHMAX)
    // và cột PRP làm vector b.
    // filename: đường dẫn file data
    // A: matrix đầu ra với kích thước (numRows x 6)
    // b: vector đầu ra kích thước (numRows)
    // numRows: số dòng thực tế trong file (sẽ trả về)
    void readMachineData(const string& filename, Matrix& A, Vector& b, Vector& erp, int& numRows);

    void splitdataset(const Matrix& A_full, const Vector& b_full, const Vector& erp_full,
                    Matrix& A_train, Vector& b_train,
                    Matrix& A_test, Vector& b_test,
                    Vector& erp_test,
                    double train_ratio = 0.8);

    double computeRMSE(const Vector& predicted, const Vector& actual);
}

#endif