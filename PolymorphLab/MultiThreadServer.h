#ifndef MULTITHREADSERVER_H
#define	MULTITHREADSERVER_H

#include "Server.h"

const int threads_count = 3;

class MultiThreadServer : public Server {
public:
    MultiThreadServer();
    MultiThreadServer(const MultiThreadServer& orig);
    virtual ~MultiThreadServer();

    virtual void tick() override;   
protected:    
    Request *threads;    
};

#endif	/* MULTITHREADSERVER_H */

