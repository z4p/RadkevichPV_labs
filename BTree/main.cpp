#include <iostream>
#include "BPlusTree.h"

using namespace std;

int main(int argc, char** argv) {
    int arr[] = {2,24,15,1,49,81,14,7,72,12,21};
    BPlusTree t;
    for(int i = 0; i < sizeof(arr); i++) {
        t.insert( arr[i] );
    }
    
    return 0;
}

