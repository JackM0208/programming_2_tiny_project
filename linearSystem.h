# pragma once
#include <iostream>
#include <cstdlib>
#include "vector.h"
#include "matrix.h"
#include <cassert>
using namespace std;

class LinearSystem{
    protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

    private:
    // làm ơn đừng copy, hãy làm người bình thường đừng làm khó coder
    LinearSystem(const LinearSystem& other);

    // tránh dùng default constructor để tạo ls mà k biết tạo làm gì :)) LoL
    LinearSystem() = delete;

    public:
    LinearSystem(const Matrix& A, const Vector& b);

    // destructor
    ~LinearSystem();

    virtual Vector Solve();

    Vector SolvebyMoorePenrose() const;

    Vector SolvebyTikhonov(double lambda) const;

};