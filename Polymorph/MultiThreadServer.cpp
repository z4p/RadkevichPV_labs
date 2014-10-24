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
    for(int i = 0; i < threads_count; i++) {
        if (threads[i].needproctime > 0) {
            threads[i].needproctime--;
            if (threads[i].needproctime == 0) {
                printRes( threads[i] );
            }
        } else {
            if (!requestQueue.empty()) {
                threads[i] = requestQueue.front();
                switch(threads[i].operation) {
                    OPERATION_SUM:
                        threads[i].needproctime = TIME_SUM;
                        break;
                    OPERATION_MUL:
                        threads[i].needproctime = TIME_MUL;
                        break;
                    default:
                        // Неизвестная операция. Неплохо было бы отсеять её на этапе получения...
                        throw std::exception();
                        break;
                }
                requestQueue.pop();
            }
        }
    }
}

void MultiThreadServer::printRes(Request r) {
    int res;
    char ch;
    switch(r.operation) {
        OPERATION_SUM:
            res = r.a + r.b;
            ch = '+';
            break;
        OPERATION_MUL:
            res = r.a + r.b;
            ch = 'x';
            break;
        default:
            // Неизвестная операция? как она сюда попала? ладно, может
            // наследник - раздолбай добавил новую операцию, но не перегрузил вывод
            throw std::exception();
            break;        
    }
    
    printf("%d %c %d = %d", r.a, ch, r.b, res);
}
