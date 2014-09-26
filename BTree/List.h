#ifndef LIST_H
#define	LIST_H

#include "BPlusTree.h"
#define DataType int

/*
 * List - двусвязный список для B+деревьев
 * Вставка происходит в отсортированный список (список отсортирован всегда)
 */

struct ListNode {
    ListNode *prev, *next;
    DataType index;
    BTreeNode *child;
    ListNode();
    ListNode(DataType val);
};

class List {
public:
    List();
    List(const List& orig);
    ~List();
    
    void insert(DataType val);
    void remove(DataType val);
    void find(DataType val);
    
private:
    ListNode *begin, *end;
    int length;
};

#endif	/* LIST_H */

