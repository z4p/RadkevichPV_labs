#include "MultiThreadServer.h"
#include "stdio.h"

using namespace std;

int main(int argc, char** argv) {
    MultiThreadServer m;
    m.addClientRequest( Request(OPERATION_MUL, 2, 2) );
    m.addClientRequest( Request(OPERATION_MUL, 3, 3) );
    m.addClientRequest( Request(OPERATION_SUM, 0, 1) );
    m.addClientRequest( Request(OPERATION_MUL, 4, 4) );
    m.addClientRequest( Request(OPERATION_SUM, 0, 2) );
    m.addClientRequest( Request(OPERATION_MUL, 5, 5) );
    m.addClientRequest( Request(OPERATION_MUL, 6, 6) );
    m.addClientRequest( Request(OPERATION_SUM, 0, 3) );
    m.addClientRequest( Request(OPERATION_SUM, 0, 4) );
    
    for(int time = 0; time < 40; time++) {
        printf("\n%2d: ", time);
        m.tick();
    }
    
    return 0;
}

