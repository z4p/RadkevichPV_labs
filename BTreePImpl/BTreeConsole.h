#ifndef BTREECONSOLE_H
#define	BTREECONSOLE_H

#include "BTreeBridge.h"


class BTreeConsole : public BTreeBridge {
public:
    BTreeConsole();
    BTreeConsole(const BTreeConsole& orig);
    ~BTreeConsole();
    
    virtual void draw();
private:
    
};

#endif	/* BTREECONSOLE_H */
