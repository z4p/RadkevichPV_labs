#include <iostream>
#include "BTreeConsole.h"
#include "BTreePretty.h"

using namespace std;

int main(int argc, char** argv) {
    int N = 8;
    int arr[] = {2,24,15,1,49,81,14,72};
    BTreeConsole tc;
    BTreePretty tp;
    for(int i = 0; i < N; i++) {
        tc.insert( arr[i] );
        tp.insert( arr[i] );
        cout << "======Console======" << endl;
        tc.draw(cout);
        cout << endl << endl;
        cout << "======Pretty=======" << endl;
        tp.draw(cout);
        cout << endl << endl;
    }
    
    return 0;
}
