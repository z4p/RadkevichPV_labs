// vector.h
// contains Vector class declaration
#include <iostream>

class Vector {
private:
    int n;
    double *values;
    
    void clear(int newSize = 0);
    
public:
    Vector();                          // constructor without parameters
    explicit Vector(int n);
    Vector(int n, double *array);
    Vector(const Vector &vObj);        // copy constructor
    Vector(const Vector &&vObj);       // move constructor
    ~Vector();                         // destructor
    
    double abs() const;                // absolute value
    void add(const Vector &vObj);      // addition
    void sub(const Vector &vObj);      // subtraction
    double scalar(const Vector &vObj); // scalar multiplication
    void mul(const double val);        // multiplying by scalar value
    int length() const;                // count of elements
    
    Vector& operator=(const Vector &rv);       // copy assignment       
    //Vector& operator=(const Vector &&rv);      // move assignment       
    Vector operator+(const Vector &rv) const;
    Vector operator-(const Vector &rv) const;
    double operator*(const Vector &rv) const;
    Vector operator*(const double val) const;
    Vector& operator++();
    Vector operator++(int);
    Vector& operator--();
    Vector operator--(int);
    double& operator[](const int index) const;
    
    friend std::ostream& operator<<(std::ostream& out, const Vector& vec);
};
