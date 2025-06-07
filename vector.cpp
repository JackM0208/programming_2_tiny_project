#include "vector.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cassert>
using namespace std;

Vector::Vector(){
    this->mSize = 0;    
    this->mData = nullptr;
}

Vector::Vector(int size){
    this->mSize = size;
    this->mData = new double[mSize + 1];
    for (int i = 1; i <= mSize; i++){
        mData[i-1] = 0.0;
    }
}

// copy constructor
Vector::Vector(const Vector& other) {
    mSize = other.mSize;
    mData = new double[mSize + 1];
    for (int i = 1; i <= mSize; ++i) {
        mData[i] = other.mData[i];
    }
}


Vector::~Vector(){
    delete[] mData;
}

Vector& Vector::operator=(const Vector& other){
    if(this == &other){
        return *this;
    }

    delete[] mData;

    this->mSize = other.mSize;

    this->mData = new double[mSize];

    for(int i = 0; i < mSize; i++){
        this->mData[i] = other.mData[i];
    }

    return *this;
}

Vector Vector::operator-() const{
    Vector result(mSize); // create a local vector using constructor (int size)

    for(int i = 0; i<mSize; i++){
        result.mData[i] = -mData[i];
    }
    return result;
}

Vector Vector::operator+(const Vector& other) const{
    if (this->mSize != other.mSize){
        cerr << "Cannot add 2 vectors with different size";
        exit(1);
    }
    else{
        Vector result(mSize);
        for(int i = 1; i <= mSize; i++){
            result.mData[i-1] = this->mData[i-1] + other.mData[i-1];
        }
        return result;
    }
}

Vector Vector::operator-(const Vector& other) const{
    if (this->mSize != other.mSize){
        cerr << "Cannot subtract 2 vectors with different size";
        exit(1);
    }
    else{
        Vector result(mSize);
        for(int i = 1; i <= mSize; i++){
            result.mData[i-1] = this->mData[i-1] - other.mData[i-1];
        }
        return result;  
    }
}
double Vector::operator*(const Vector& other) const{
    if (this->mSize != other.mSize) {
        cerr << "Cannot dot product 2 vectors with different size" << endl;
        exit(1);
    }
    double result = 0.0;
    for(int i = 1;i < mSize; i++){
        result += this->mData[i-1] * other.mData[i-1];
    }
    return result;
}

Vector Vector::operator*(double scalar) const{
    if (mSize == 0){
        return Vector();
    }
    else{
        Vector result(mSize);
        for(int i = 1; i<mSize; i++){
            result.mData[i-1] = this->mData[i-1] * scalar;
        }
        return result;
    }
}

double& Vector::operator[](int i){
    if (i < 1 || i > mSize){
        cerr << "Index is OUT of bound!!!";
        exit(1);
    }
    return this->mData[i - 1];
}

const double& Vector::operator[](int i) const{  
    return mData[i-1];
}

double& Vector::operator()(int i){
    assert(i >= 1 && i <= mSize && "Index out of range");
    return mData[i-1];
}

const double& Vector::operator()(int i) const{
    assert(i >= 1 && i <= mSize && "Index out of range");
    return mData[i-1];
}

double Vector::Norm() const {
    double sum = 0.0;
    for (int i = 0; i < mSize; ++i) {
        double val = mData[i];
        cout << "Norm debug val[" << i << "] = " << val << endl;  // debug từng phần tử
        sum += val * val;
    }
    double result = sqrt(sum);
    cout << "Norm debug sum = " << sum << ", sqrt = " << result << endl;
    return result;
}

