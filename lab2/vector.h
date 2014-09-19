// vector.h

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
    
    double abs() const;           // absolute value
    void add(const Vector &vObj); // addition
    void sub(const Vector &vObj); // subtraction
    void mul(const double val);   // multiplying by scalar value
    int length() const;           // 
    
    Vector& operator=(const Vector &rv);
    Vector operator+(const Vector &rv);
    Vector operator-(const Vector &rv);
    Vector operator*(const double val);
    Vector& operator++();
    Vector operator++(int);
    Vector& operator--();
    Vector operator--(int);
    double& operator[](const int index);
};
