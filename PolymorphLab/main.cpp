#include "MultiThreadServer.h"
#include "AsyncServer.h"
#include "stdio.h"

using namespace std;

const int N = 9;

Request rs[N] = {
    {OPERATION_MUL, 2, 2, 0},
    {OPERATION_MUL, 3, 3, 0},
    {OPERATION_SUM, 0, 1, 0},
    {OPERATION_MUL, 4, 4, 0},
    {OPERATION_SUM, 0, 2, 0},
    {OPERATION_MUL, 5, 5, 0},
    {OPERATION_MUL, 6, 6, 0},
    {OPERATION_SUM, 0, 3, 0},
    {OPERATION_SUM, 0, 4, 0},
};

int main(int argc, char** argv) {
    Server *mt = new MultiThreadServer(); 
    Server *as = new AsyncServer();
    
    for(int i = 0; i < N; i++) {
        mt->addClientRequest( rs[i] );
        as->addClientRequest( rs[i] );
    }
    
    printf("time\tmultithread\t| async");
    for(int tm = 0; tm < 30; tm++) {
        mt->tick();
        as->tick();
        printf("\n%2d: ", tm);
        mt->sendResult();
        printf("\t| ");
        as->sendResult();
    }
    
    return 0;
}
