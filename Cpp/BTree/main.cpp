#include <iostream>
#include "BPlusTree.h"

using namespace std;

int main(int argc, char** argv) {
    int N = 8;
    int arr[] = {2,24,15,1,49,81,14,72};
    BPlusTree t;
    for(int i = 0; i < N; i++) {
        t.insert( arr[i] );
        t.draw(cout);
        cout << "\n============\n";
    }
    
    
    return 0;
}
