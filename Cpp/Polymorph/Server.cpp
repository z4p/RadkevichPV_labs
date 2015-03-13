#include "Server.h"


// public section

Server::Server() {}

Server::Server(const Server& orig) {}

Server::~Server() {}

void Server::addClientRequest(Request r) {
    requestQueue.push(r);
}

void Server::sendResult() {
    if (!resultQueue.empty()) {
        printRes( resultQueue.front() );
        resultQueue.pop();
    }
}


// protected section

bool Server::requestsEmpty() const {
    return requestQueue.empty();
}

Request Server::requestPop() {
    if (requestQueue.empty()) {
        throw std::exception();
    } else {
        Request r = requestQueue.front();
        requestQueue.pop();
        return r;
    }
}

void Server::resultAdd(Request r) {
    resultQueue.push(r);
}


// private section

void Server::printRes(Request r) const {
    int res;
    char ch;
    switch(r.operation) {
        case OPERATION_SUM:
            res = r.a + r.b;
            ch = '+';
            break;
        case OPERATION_MUL:
            res = r.a * r.b;
            ch = 'x';
            break;
        default:
            // Неизвестная операция? как она сюда попала? ладно, может для
            // наследника добавили новую операцию, но не перегрузили вывод
            printf("unknown operation '%d' in printRes()\n", r.operation);
            throw std::exception();
            break;
    }
    printf("%d%c%d=%d", r.a, ch, r.b, res);
}
