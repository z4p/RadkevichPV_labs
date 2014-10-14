#ifndef BTREEPRETTY_H
#define	BTREEPRETTY_H

#include "BTreeConsole.h"


class BTreePretty : public BTreeConsole {
public:
    BTreePretty();
    BTreePretty(const BTreePretty& orig);
    ~BTreePretty();
    
private:
    void drawNode(BTreeNode* node) override; 
};

#endif	/* BTREEPRETTY_H */
