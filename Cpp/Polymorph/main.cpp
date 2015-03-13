#include "MultiThreadServer.h"
#include "AsyncServer.h"
#include "stdio.h"

const int N = 9;

Request rs1[N] = {
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


Request rs2[N] = {
    {OPERATION_SUM, 0, 1, 0},
    {OPERATION_SUM, 0, 2, 0},
    {OPERATION_SUM, 0, 3, 0},
    {OPERATION_SUM, 0, 4, 0},
    {OPERATION_SUM, 0, 5, 0},
    {OPERATION_SUM, 0, 6, 0},
    {OPERATION_MUL, 2, 2, 0},
    {OPERATION_MUL, 3, 3, 0},
    {OPERATION_MUL, 4, 4, 0},
};


//можна зрабіць масіў паказальнікаў
int main(int argc, char** argv) {
    Server *mt = new MultiThreadServer();
    Server *as = new AsyncServer();

    Request *rs = rs2;

    for(int i = 0; i < N; i++) {
        mt->addClientRequest( rs[i] );
        as->addClientRequest( rs[i] );
    }


    printf("time\t| mt\t| async");
    for(int tm = 0; tm < 25; tm++) {
        mt->tick();
        as->tick();
        printf("\n%2d: \t|", tm);
        mt->sendResult();
        printf("\t| ");
        as->sendResult();
    }
    printf("\n\n");

    return 0;
}
