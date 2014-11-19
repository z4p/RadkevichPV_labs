/*
 * Лаба 6 для двусвязного списка
 * просто черновик
 * дабы разобраться на простом и применить к сложному
 */
#include <iostream>
#include "List.h"

using namespace std;

int main() {
    int N = 8;
    int keys[] = {2, 24, 15, 1, 49, 81, 14, 2};
    float vals[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    List<int,double> l;
    
    try {
        for(int i = 0; i < N; i++) {
            l.insert( keys[i], vals[i] );
        }
    }
    catch(DuplicateKeyException& e) {
        // do nothing, we allow these tryes
    }
    
    try {
        l.remove(3);        // unexisting element
    }
    catch(NotFoundException& e) {
        cerr << e.what() << endl;
    }
    
    for(List<int,double>::Iterator i = l.begin(); i != l.end(); ++i) {
        cout << *i << endl;
    }
    
    return 0;
}
