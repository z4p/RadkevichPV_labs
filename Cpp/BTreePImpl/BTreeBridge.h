#ifndef BTREEBRIDGE_H
#define	BTREEBRIDGE_H

#include "BPlusTree.h"

class BTreeBridge {
private:
    BPlusTree *pimpl;
public:
    BTreeBridge();
    BTreeBridge(const BTreeBridge& orig);
    BTreeBridge(const BTreeBridge&& orig);
    BTreeBridge& operator=(const BTreeBridge& rv);
    BTreeBridge& operator=(BTreeBridge&& rv);
    ~BTreeBridge();
    
    void insert(DataType val) { pimpl->insert(val); };
    void remove(DataType val) { pimpl->remove(val); };
    bool find(DataType val) { return pimpl->find(val); };
    
    bool getCurrentNode(BTreeNode& node) {
        return pimpl->getCurrentNode(node);
    }
};

#endif	/* BTREEBRIDGE_H */
