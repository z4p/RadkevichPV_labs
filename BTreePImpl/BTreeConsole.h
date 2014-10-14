#ifndef BTREECONSOLE_H
#define	BTREECONSOLE_H

#include "BTreeBridge.h"


class BTreeConsole : public BTreeBridge {
public:
    BTreeConsole();
    BTreeConsole(const BTreeConsole& orig);
    ~BTreeConsole();
    
    void draw(std::ostream& out) const;
    
private:
    virtual void drawNode(BTreeNode* node);
};

#endif	/* BTREECONSOLE_H */
