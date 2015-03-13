#ifndef SERVER_H
#define	SERVER_H

#include <queue>
#include <stdio.h>

const int OPERATION_SUM = 1;    
const int TIME_SUM = 1;

const int OPERATION_MUL = 2;
const int TIME_MUL = 10;

struct Request {
    int operation;
    int a;
    int b;
    int needproctime;
};

class Server {
public:
    Server();
    Server(const Server& orig);
    virtual ~Server();
    
    virtual void tick() = 0;
    void addClientRequest(Request r);    
    void sendResult();

protected:
    bool requestsEmpty() const;
    Request requestPop();
    void resultAdd(Request r);
    
private:
    virtual void printRes(Request r) const;
    
    std::queue<Request> requestQueue;
    std::queue<Request> resultQueue;
};

#endif	/* SERVER_H */

