#ifndef ASYNCSERVER_H
#define	ASYNCSERVER_H

#include "Server.h"
#include <deque>

class AsyncServer : public Server {
public:
    AsyncServer();
    AsyncServer(const AsyncServer& orig);
    virtual ~AsyncServer();

    virtual void tick() override;
protected:
    std::deque<Request> heavyRequests;
};

#endif	/* ASYNCSERVER_H */

