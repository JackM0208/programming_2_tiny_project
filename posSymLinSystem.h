#pragma once
#include "linearSystem.h"
using namespace std;

class PosSymLinSystem : public LinearSystem{
    private:
    bool isSymmetric(const Matrix& A) const;

    public:
    PosSymLinSystem(const Matrix& A, const Vector& b);

    ~PosSymLinSystem();

    Vector Solve() override;


};