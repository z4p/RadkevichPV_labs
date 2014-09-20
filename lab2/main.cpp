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
    
    // collin test
    for(int i = 0; i < v1.length(); i++) {
        if (v1[i] != v2[i]) {
            f = false;
            break;
        }
    }
    
    if (f) {
        res = VECTORS_COLLINEAR;
    } else {
        // orthog test
        if (v1*v2 == 0) {
            res = VECTORS_ORTHOGONAL;
        }
    }
    
    return res;
}

int main(int argc, char** argv) {
    int M = 3;
    int N = 4;
    Vector **vs = new Vector*[M];
    
    
    for (int i = 0; i < M; i++) {
        vs[i] = new Vector(N);
        cout << i << ": ";
        for (int j = 0; j < N; j++) {
            cin >> (*vs)[i][j];
        }
    }
    
    int r = testVectors(*vs[0], *vs[2]);
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
