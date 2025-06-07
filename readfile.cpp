#include "readfile.h"
#include "matrix.h"
#include "vector.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

namespace utils {
    void readMachineData(const string& filename, Matrix& A, Vector& b, Vector& erp, int& numRows) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Lỗi: không mở được file " << filename << endl;
            numRows = 0;
            return;
        }

        string line;
        numRows = 0;

        // Đếm số dòng trong file để khởi tạo đúng kích thước cho A và b
        while (getline(fin, line)) {
            if (line.empty()) continue;
            ++numRows;
        }

        // Quay lại đầu file đọc thật
        fin.clear();
        fin.seekg(0, ios::beg);

        // Khởi tạo A và b theo số dòng đọc được, 6 cột features
        A = Matrix(numRows, 6);
        b = Vector(numRows);
        erp = Vector(numRows);

        int row = 1; // index 1-based cho ma trận A

        while (getline(fin, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string token;

            // Cột 1: vendor name (bỏ)
            getline(ss, token, ',');

            // Cột 2: model name (bỏ)
            getline(ss, token, ',');

            // Cột 3: MYCT
            getline(ss, token, ',');
            double MYCT = stod(token);

            // Cột 4: MMIN
            getline(ss, token, ',');
            double MMIN = stod(token);

            // Cột 5: MMAX
            getline(ss, token, ',');
            double MMAX = stod(token);

            // Cột 6: CACH
            getline(ss, token, ',');
            double CACH = stod(token);

            // Cột 7: CHMIN
            getline(ss, token, ',');
            double CHMIN = stod(token);

            // Cột 8: CHMAX
            getline(ss, token, ',');
            double CHMAX = stod(token);

            // Cột 9: PRP - target
            getline(ss, token, ',');
            double PRP = stod(token);

            // Cột 10: ERP
            getline(ss, token, ','); double ERP = stod(token);

            // Gán vào matrix A (6 feature cột)
            A(row,1) = MYCT;
            A(row,2) = MMIN;
            A(row,3) = MMAX;
            A(row,4) = CACH;
            A(row,5) = CHMIN;
            A(row,6) = CHMAX;

            // Gán vào vector b
            b[row] = PRP;  // Vector bạn index 1-based
            erp[row] = ERP; // lưu erp vào vector
            
            ++row;
        }

        fin.close();
    }

    void splitdataset(const Matrix& A_full, const Vector& b_full, const Vector& erp_full,
                        Matrix& A_train, Vector& b_train,
                        Matrix& A_test, Vector& b_test,
                        Vector& erp_test, 
                        double train_ratio) {

        int numSamples = 209;        // tổng số mẫu dữ liệu
        int numFeatures = 6;         // số cột đặc trưng

        int train_size = static_cast<int>(train_ratio * numSamples);
        int test_size = numSamples - train_size;

        // Khởi tạo ma trận và vector train/test theo kích thước
        A_train = Matrix(train_size, numFeatures);
        b_train = Vector(train_size);
        A_test = Matrix(test_size, numFeatures);
        b_test = Vector(test_size);
        erp_test = Vector(test_size); // erp test Vector

        // Chia thẳng theo thứ tự, 80% đầu cho train, 20% sau cho test
        for (int i = 1; i <= train_size; i++) {
            for (int j = 1; j <= numFeatures; j++) {
                A_train(i, j) = A_full(i, j);
            }
            b_train[i] = b_full[i];
        }

        for (int i = 1; i <= test_size; i++) {
            for (int j = 1; j <= numFeatures; j++) {
                A_test(i, j) = A_full(i + train_size, j);
            }
            b_test[i] = b_full[i + train_size];
            erp_test[i] = erp_full[i + train_size];
        }
    }

    double computeRMSE(const Vector& predicted, const Vector& actual){
        assert(predicted.size() == actual.size());
        int n = predicted.size();
        double sumSquared = 0.0;
        for(int i = 1; i <= n; ++i){
            double diff = predicted[i] - actual[i];
            sumSquared += diff * diff;
        }
        return sqrt(sumSquared/n);
    }
}