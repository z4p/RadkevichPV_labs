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
                printf("unknown operation '%d' in tick()\n", r.operation);
                throw std::exception();
                break;
        }
    }

    if (!heavyRequests.empty()) {
        for(std::deque<Request>::iterator i = heavyRequests.begin(); !heavyRequests.empty() && i != heavyRequests.end(); ++i) {
            if ((*i).needproctime == 0) {
                resultAdd(*i);
                std::deque<Request>::iterator t = i;
                heavyRequests.erase(t);
            } else {
                (*i).needproctime--;
            }
        }
    }
}
