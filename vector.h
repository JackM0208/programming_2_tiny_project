#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>

class Vector {
    friend class Matrix;
    private:
    int mSize;
    double* mData;

    public:
    // constructor 
    Vector();
    Vector(int size);

    Vector(const Vector& other); 

    // destructor
    ~Vector();

    // get size
    int size() const {
        return mSize;
    }

    // operator = 
    Vector& operator=(const Vector& other);

    // operator sign swap, use const because operator- does not change the initial value *this
    Vector operator-() const;
    
    // binary operator
    Vector operator+(const Vector& other) const;

    Vector operator-(const Vector& other) const;

    double operator*(const Vector& other) const;

    Vector operator*(double scalar) const;

    // operator[] return the value at index i of a vector
    double& operator[] (int i);
    const double& operator[](int i) const;

    // operator() to access the element from 1 to mSize
    double& operator() (int i);
    const double& operator()(int i) const;

    double Norm() const;
};

// Cho phép double * Vector
inline Vector operator*(double scalar, const Vector& v) {
    return v * scalar; // Nếu bạn đã overload Vector * double
}

