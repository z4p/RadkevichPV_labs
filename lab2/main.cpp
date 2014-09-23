/* 
 * main.cpp
 * 
 * Lab 02
 * Task 03
 * Разработать класс «Вектор» – Vector размерности n.
 * Определить несколько конструкторов, в том числе конструктор 
 * копирования. Реализовать методы для вычисления модуля вектора, 
 * скалярного произведения, сложения, вычитания, умножения на 
 * константу. Перегрузить операции сложения, вычитания, умножения, 
 * инкремента, декремента, индексирования, присваивания для данного 
 * класса. Создать массив объектов. Написать функцию, которая для 
 * заданной пары векторов будет определять, являются ли они коллинеарными 
 * или ортогональными.
 * 
 * Developed by Paul z4p Radkevich
 */
#include <iostream>
#include "vector.h"

using namespace std;

const int VECTORS_NONSPECIAL = 0;
const int VECTORS_COLLINEAR = 1;
const int VECTORS_ORTHOGONAL = 2;

int testVectors(const Vector &v1, const Vector &v2) {
    if (v1.length() != v2.length()) {
        throw std::exception();
    }
    
    int res = VECTORS_NONSPECIAL;
    bool f = true;
    double d;
    
    // collin testing
    int i;
    for(i = 0; i < v1.length() && v2[i] == 0; i++) {}
    d = v1[i] / v2[i];
    
    for(int j = i; j < v1.length(); j++) {
        if (v1[j] != d * v2[j]) {
            f = false;
            break;
        }
    }
    
    if (f) {
        res = VECTORS_COLLINEAR;
    } else {
        // orthog testing
        if (v1 * v2 == 0) {
            res = VECTORS_ORTHOGONAL;
        }
    }
    
    return res;
}


// writes to output stream
ostream& operator<<(ostream& out, const Vector& vec) {
    out << "(";
    for(int i = 0; i < vec.length(); i++) {
        out << vec[i] << (i == vec.length()-1 ? "" : ",");
    }
    out << ")";
    return out;
}

int main(int argc, char** argv) {
    // some magic vectors for testing
    double v0c[] = {1,0,0,1};
    double v1c[] = {1,2,3,4};
    double v2c[] = {0,-2,0,1};
    double v3c[] = {2,4,6,8};
    
    Vector vs[4];
    
    vs[0] = Vector(4, v0c);
    vs[1] = Vector(4, v1c);
    vs[2] = Vector(4, v2c);
    vs[3] = Vector(4, v3c);
            
    // unit test parody
    if (
            VECTORS_NONSPECIAL != testVectors(vs[0], vs[2]) || 
            VECTORS_ORTHOGONAL != testVectors(vs[1], vs[2]) || 
            VECTORS_COLLINEAR  != testVectors(vs[1], vs[3]) ||
            (vs[1]*2 - vs[3]).abs() != 0
       ) {
        cout << "Something doen't work =(" << endl;
    }

//    testVectors(vs[0], Vector(3)); // exception
    
    Vector v1 = vs[0];    // (1,0,0,1)
    v1[1] = 2;            // (1,2,0,1)
    Vector v2( v1*4 );    // (4,8,0,4)
    
    cout << v1 << endl << v2 << endl;
    
    int r = testVectors(v1, v2);
    switch (r) {
        case VECTORS_NONSPECIAL:
            cout << "There is nothing interesting here" << endl;
            break;
        case VECTORS_COLLINEAR:
            cout << "Vectors are collinear" << endl;
            break;
        case VECTORS_ORTHOGONAL:
            cout << "Vectors are orthogonal" << endl;
            break;
        default:
            cout << "Nechakanasc" << endl;
    }
    
    return 0;
}
