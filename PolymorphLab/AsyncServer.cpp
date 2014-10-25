#include "AsyncServer.h"
#include <stdio.h>

AsyncServer::AsyncServer() : Server() {}

AsyncServer::AsyncServer(const AsyncServer& orig) {}

AsyncServer::~AsyncServer() {}

void AsyncServer::tick() {
    if (!requestsEmpty()) {
        Request r = requestPop();
        switch(r.operation) {
            case OPERATION_SUM:
                resultAdd(r);
                break;
            case OPERATION_MUL:
                r.needproctime = TIME_MUL;
                heavyRequests.push_back(r);
                break;
            default:
                // Неизвестная операция. Неплохо было бы отсеять её на этапе получения...
                printf("unknown operation '%d' in tick()\n", r.operation);
                //throw std::exception();
                break;
        }
        
        for(std::list<Request>::iterator i = heavyRequests.begin(); i != heavyRequests.end(); ++i) {
            (*i).needproctime--;
            if ((*i).needproctime == 0) {
                resultAdd(*i);
            }
        }
    }
}
