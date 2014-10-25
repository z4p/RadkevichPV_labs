#include "MultiThreadServer.h"
#include <stdio.h>

MultiThreadServer::MultiThreadServer() : Server(), threads(nullptr) {
    threads = new Request[threads_count];
}

MultiThreadServer::MultiThreadServer(const MultiThreadServer& orig) {
}

MultiThreadServer::~MultiThreadServer() {
    delete [] threads;
}

void MultiThreadServer::tick() {
    //printf("<mt tick emptyRequests=%d>", requestsEmpty());
    for(int i = 0; i < threads_count; i++) {
        if (threads[i].needproctime > 0) {
            threads[i].needproctime--;
            if (threads[i].needproctime == 0) {
                // success
                resultAdd(threads[i]);
            }
        } else {
            if (!requestsEmpty()) {
                threads[i] = requestPop();
                switch(threads[i].operation) {
                    case OPERATION_SUM:
                        threads[i].needproctime = TIME_SUM;
                        break;
                    case OPERATION_MUL:
                        threads[i].needproctime = TIME_MUL;
                        break;
                    default:
                        printf("unknown operation '%d' in tick()\n", threads[i].operation);
                        throw std::exception();
                        break;
                }
                threads[i].needproctime--;
                if (threads[i].needproctime == 0) {
                    // success
                    resultAdd(threads[i]);
                }
            }
        }
    }
}
