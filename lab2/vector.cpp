#include <math.h>
#include <exception>
#include "vector.h"

Vector::Vector() {
    this->n = 0;
}

Vector::Vector(int n) {
    this->n = n;
    values = new double[n];
    for(int i = 0; i < n; i++) {
        values[i] = 0;
    }
}

Vector::Vector(int n, double* array) {
    this->n = n;
    values = new double[n];
    for(int i = 0; i < n; i++) {
        values[i] = array[i];
    } 
}

Vector::Vector(const Vector& vObj) {
    n = vObj.length();
    values = new double[ n ];
    for(int i = 0; i < n; i++) {
        values[i] = vObj.values[i];
    } 
}

Vector::~Vector() {
    delete [] values;
}

// calculating vector's absolute value
double Vector::abs() const {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += values[i]*values[i];
    }
    return sqrt(sum);
}

// addition of other vector
void Vector::add(const Vector& vObj) {
    if (vObj.length() != this->length()) {
        // can't calculate the sum or the difference of two vectors with different lengths
        throw std::exception();
    }
            
    for(int i = 0; i < n; i++) {
        values[i] += vObj.values[i];
    }
}

// multiplying by a constant scalar value
void Vector::mul(const double val) {
    for(int i = 0; i < n; i++) {
        values[i] *= val;
    }
}

//  subtacting other vector
void Vector::sub(const Vector& vObj) {
    if (vObj.length() != this->length()) {
        // can't calculate the sum or the difference of two vectors with different lengths
        throw std::exception();
    }
            
    for(int i = 0; i < n; i++) {
        values[i] -= vObj.values[i];
    }
}

int Vector::length() const {
    return n;
}

double& Vector::operator[](const int index) {
    return values[index];
}

Vector& Vector::operator=(const Vector &rv) {
    // if lvalueObj != rvalueObj
    if (&rv != this) {
        // if objects have different lengths we should reinit our array
        if (rv.length() != this->length()) {
            delete [] values;
            values = new double[rv.length()];
        }

        // copying
        for(int i = 0; i < rv.length(); i++) {
            values[i] = rv.values[i];
        }
    }
    return *this;
}

Vector Vector::operator+(const Vector &rv) {
    Vector v(n, values);
    v.add(rv);
    return v;
}

Vector Vector::operator-(const Vector &rv) {
    Vector v(n, values);
    v.sub(rv);
    return v;
}

Vector Vector::operator*(const double val) {
    Vector v(n, values);
    v.mul(val);
    return v;
}

// pre/post inc/dec

Vector& Vector::operator++() {
    
}

Vector Vector::operator++(int) {
    
}

Vector& Vector::operator--() {
    
}

Vector Vector::operator--(int) {
    
}
