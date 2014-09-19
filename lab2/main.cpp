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

// testing of properties of two vectors
// returns 0 if no, 1 - collinear, 2 - orthogonal
int testVectors(const Vector &v1, const Vector &v2) {
    if (v1.length() != v2.length()) {
        throw std::exception();
    }
    
    int res = 0;
    bool f = true;
    
    // collin test
    for(int i = 0; i < v1.length(); i++) {
        if (v1[i] != v2[i]) {
            f = false;
            break;
        }
    }
    
    if (f) {
        res = 1;
    } else {
        // orthog test
        if (v1*v2 == 0) {
            res = 2;
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
        case 0:
            cout << "There is nothing interesting here" << endl;
            break;
        case 1:
            cout << "Vectors are collinear" << endl;
            break;
        case 2:
            cout << "Vectors are orthogonal" << endl;
            break;
        default:
            cout << "Nechakanasc" << endl;
    }
    
    return 0;
}
