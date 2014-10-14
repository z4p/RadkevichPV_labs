#ifndef BTREEBRIDGE_H
#define	BTREEBRIDGE_H

#include "BPlusTree.h"

class BTreeBridge {
private:
    BPlusTree *pimpl;
public:
    BTreeBridge();
    BTreeBridge(const BTreeBridge& orig);  // copy
    BTreeBridge(const BTreeBridge&& orig); // move
    BTreeBridge& operator=(const BTreeBridge& rv);
    BTreeBridge& operator=(BTreeBridge&& rv);
    ~BTreeBridge();
    
    void insert(DataType val) { pimpl->insert(val); };
    void remove(DataType val) { pimpl->remove(val); };
    ListNode* find(DataType val) { return pimpl->find(val); };
};

#endif	/* BTREEBRIDGE_H */
