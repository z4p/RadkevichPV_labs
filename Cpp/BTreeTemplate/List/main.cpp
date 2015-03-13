/*
 * Лаба 6 для двусвязного списка
 */
#include <iostream>
#include "List.h"
#include "SmartPtr.h"

using namespace std;

int main() {
    int N = 8;
    int keys[] = {2, 24, 15, 1, 49, 81, 14, 2};
    float vals[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    List<int,double> *l = new List<int,double>();
    SmartPtr< List<int,double> > lptr(l);
    
    try {
        for(int i = 0; i < N; i++) {
            lptr->insert( keys[i], vals[i] );
        }
    }
    catch(DuplicateKeyException& e) {
        // do nothing, we allow these tryes
    }
    
    try {
        lptr->remove(3);        // unexisting element
    }
    catch(NotFoundException& e) {
        cerr << e.what() << endl;
    }
    
    for(auto i = lptr->begin(); i != lptr->end(); ++i) {
        cout << *i << endl;
    }
    
    return 0;
}
