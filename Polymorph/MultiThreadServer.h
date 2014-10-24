/* 
 * File:   MultiThreadServer.h
 * Author: z4p
 *
 * Created on 24 Октябрь 2014 г., 18:15
 */

#ifndef MULTITHREADSERVER_H
#define	MULTITHREADSERVER_H

#include "Server.h"

const int threads_count = 3;

class MultiThreadServer : public Server {
public:
    MultiThreadServer();
    MultiThreadServer(const MultiThreadServer& orig);
    virtual ~MultiThreadServer();

    virtual void tick();
private:
    virtual void printRes(Request r);
    
protected:    
    Request *threads;    
};

#endif	/* MULTITHREADSERVER_H */

