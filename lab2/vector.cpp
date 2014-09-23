// vector.cpp
// contains Vector class implementation

#include <math.h>
#include <exception>
#include "vector.h"

// constructor without parameters
Vector::Vector() : n(0), values(nullptr) {}

Vector::Vector(int n) : n(n), values(nullptr) {
    values = new double[n];
    for(int i = 0; i < n; i++) {
        values[i] = 0;
    }
}

Vector::Vector(int n, double* array) : n(n), values(nullptr) {
    this->n = n;
    values = new double[n];
    for(int i = 0; i < n; i++) {
        values[i] = array[i];
    } 
}

// copy constuctor
Vector::Vector(const Vector& vObj) : n(n), values(nullptr) {
    n = vObj.length();
    values = new double[ n ];
    for(int i = 0; i < n; i++) {
        values[i] = vObj.values[i];
    } 
}

// move constructor
Vector::Vector(const Vector &&obj) :
        n(std::move(obj.n)),
        values(std::move(obj.values)) {}

// destructor
Vector::~Vector() {
    clear();
}

// erases vector's data, may create a new one (private)
void Vector::clear(int newSize /* = 0 */ ) {
    n = newSize;
    delete [] values;
    if (newSize != 0) {
        values = new double[newSize];
    }
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

// scalar multiplication
double Vector::scalar(const Vector &vObj) {
    if (vObj.length() != this->length()) {
        // can't calculate scalar multiplication of two vectors with different lengths
        throw std::exception();
    }
    
    double s = 0;
    for(int i = 0; i < n; i++) {
        s += values[i] * vObj.values[i];
    }
    
    return s;
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

// count of vector's elements
int Vector::length() const {
    return n;
}

// indexing of vector
double& Vector::operator[](const int index) const {
    if (values == nullptr) {
        throw std::exception(); // vector's data hasn't been initialised
    }
    if (index < 0 || index >= n) {
        throw std::exception(); // index is out of range
    }
    return values[index];
}

// copy assignment
Vector& Vector::operator=(const Vector &rv) {
    // if lvalueObj != rvalueObj
    if (&rv != this) {
        // if objects have different lengths we should reinit our array
        if (rv.length() != this->length()) {
            clear( rv.length() );
        }

        // copying
        n = rv.n;
        for(int i = 0; i < rv.length(); i++) {
            values[i] = rv.values[i];
        }
    }
    return *this;
}

// move assignment
Vector& Vector::operator=(const Vector&& rv) {
    // if lvalueObj != rvalueObj
    if (&rv != this) {
        n = std::move(rv.n);
        values = std::move(rv.values);
    }
    return *this;
}

Vector Vector::operator+(const Vector &rv) const {
    Vector v(n, values);
    v.add(rv);
    return v;
}

Vector Vector::operator-(const Vector &rv) const {
    Vector v(n, values);
    v.sub(rv);
    return v;
}

double Vector::operator*(const Vector &rv) const {
    Vector v(n, values);
    return v.scalar(rv);
}

Vector Vector::operator*(const double val) const {
    Vector v(n, values);
    v.mul(val);
    return v;
}

// pre/post inc/dec

Vector& Vector::operator++() {
    for(int i = 0; i < n; i++) {
        values[i] += 1;
    }
    return *this;
}

Vector Vector::operator++(int) {
    Vector v = *this;
    ++*this;
    return v;
}

Vector& Vector::operator--() {
    for(int i = 0; i < n; i++) {
        values[i] -= 1;
    }
    return *this;
}

Vector Vector::operator--(int) {
    Vector v = *this;
    --*this;
    return v;
}
