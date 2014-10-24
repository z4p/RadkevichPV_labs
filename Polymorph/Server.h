#ifndef SERVER_H
#define	SERVER_H

#include <queue>

const int OPERATION_SUM = 1;
const int TIME_SUM = 1;

const int OPERATION_MUL = 2;
const int TIME_MUL = 10;

struct Request {
    int operation;
    int a;
    int b;
    int needproctime;
    Request(): a(0), b(0), operation(0), needproctime(0) {}
    Request(int op, int a, int b) {
        this->a = a;
        this->b = b;
        this->operation = op;
        needproctime = 0;
    }
};

class Server {
public:
    Server();
    Server(const Server& orig);
    virtual ~Server();
    
    virtual void tick();
    void addClientRequest(Request r) {
        requestQueue.push(r);
    }
    
private:
    virtual void printRes(Request r);

protected:
    std::queue<Request> requestQueue;
};

#endif	/* SERVER_H */

