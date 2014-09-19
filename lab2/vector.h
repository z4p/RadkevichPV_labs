// vector.h
// contains Vector class declaration

class Vector {
private:
    int n;
    double *values;
    
public:
    Vector();
    explicit Vector(int n);
    Vector(int n, double *array);
    Vector(const Vector &vObj);
    ~Vector();
    
    double abs() const;                // absolute value
    void add(const Vector &vObj);      // addition
    void sub(const Vector &vObj);      // subtraction
    double scalar(const Vector &vObj); // scalar multiplication
    void mul(const double val);        // multiplying by scalar value
    int length() const;                // count of elements
    
    Vector& operator=(const Vector &rv);
    Vector operator+(const Vector &rv) const;
    Vector operator-(const Vector &rv) const;
    double operator*(const Vector &rv) const;
    Vector& operator++();
    Vector operator++(int);
    Vector& operator--();
    Vector operator--(int);
    double& operator[](const int index) const;
};
