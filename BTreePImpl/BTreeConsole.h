#ifndef BTREECONSOLE_H
#define	BTREECONSOLE_H

#include "BTreeBridge.h"


class BTreeConsole : public BTreeBridge {
public:
    BTreeConsole();
    BTreeConsole(const BTreeConsole& orig);
    BTreeConsole(const BTreeConsole&& orig);
    BTreeConsole& operator=(const BTreeConsole& orig);
    BTreeConsole& operator=(const BTreeConsole&& orig);
    ~BTreeConsole();
    
    void draw(std::ostream& out);
    
protected:
    virtual void drawNode(BTreeNode& node, std::ostream& out);
};

#endif	/* BTREECONSOLE_H */
