#ifndef BTREEPRETTY_H
#define	BTREEPRETTY_H

#include "BTreeConsole.h"

class BTreePretty : public BTreeConsole {
public:
    BTreePretty();
    BTreePretty(const BTreePretty& orig);
    BTreePretty(const BTreePretty&& orig);
    BTreePretty& operator=(const BTreePretty& rv);
    BTreePretty& operator=(const BTreePretty&& rv);
    ~BTreePretty();
    
protected:
    void drawNode(BTreeNode& node, std::ostream& out) override; 
};

#endif	/* BTREEPRETTY_H */
